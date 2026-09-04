/**
 * @file comms.c
 * @brief Implementacao da comunicacao com TunerStudio - port de comms.cpp
 *
 * Logica de protocolo 1:1 com a branch tiny. Diferencas sao so de
 * hardware/toolchain:
 *   - Serial.available()/read()/write() -> sciXxx() (serial_hc08.h,
 *     polling sobre a SCI - ver ressalva de design la).
 *   - pgm_read_dword(&crc32_table[i]) -> crc32_table[i] direto: o HC08
 *     tem memoria unificada (Flash mapeada no mesmo espaco de enderecos
 *     que RAM), NAO existe a distincao Harvard do AVR que exige
 *     instrucao LPM/pgm_read_* para ler dado "do programa". Simplificacao
 *     real, nao gambiarra.
 *   - uint8_t& value (referencia C++) -> uint8_t* value (ponteiro C).
 *   - enum ... : uint8_t (C++) -> enum comum (C nao tem underlying type).
 *   - __heap_start/__brkval (introspeccao de heap do avr-libc) -> NAO
 *     existe equivalente verificado para SDCC/HC08 ainda. getFreeRam()
 *     fica placeholder retornando 0 - nao adivinhado.
 */

#include "comms.h"
#include "globals.h"
#include "config.h"
#include "storage.h"
#include "tables.h"
#include "serial_hc08.h"
#include <string.h>

/* ==========================================================================
 * TABELA CRC32 - memoria unificada, sem PROGMEM/pgm_read (ver nota acima)
 * ========================================================================== */
static const uint32_t crc32_table[256] = {
  0x00000000UL, 0x77073096UL, 0xEE0E612CUL, 0x990951BAUL, 0x076DC419UL, 0x706AF48FUL, 0xE963A535UL, 0x9E6495A3UL,
  0x0EDB8832UL, 0x79DCB8A4UL, 0xE0D5E91EUL, 0x97D2D988UL, 0x09B64C2BUL, 0x7EB17CBDUL, 0xE7B82D07UL, 0x90BF1D91UL,
  0x1DB71064UL, 0x6AB020F2UL, 0xF3B97148UL, 0x84BE41DEUL, 0x1ADAD47DUL, 0x6DDDE4EBUL, 0xF4D4B551UL, 0x83D385C7UL,
  0x136C9856UL, 0x646BA8C0UL, 0xFD62F97AUL, 0x8A65C9ECUL, 0x14015C4FUL, 0x63066CD9UL, 0xFA0F3D63UL, 0x8D080DF5UL,
  0x3B6E20C8UL, 0x4C69105EUL, 0xD56041E4UL, 0xA2677172UL, 0x3C03E4D1UL, 0x4B04D447UL, 0xD20D85FDUL, 0xA50AB56BUL,
  0x35B5A8FAUL, 0x42B2986CUL, 0xDBBBC9D6UL, 0xACBCF940UL, 0x32D86CE3UL, 0x45DF5C75UL, 0xDCD60DCFUL, 0xABD13D59UL,
  0x26D930ACUL, 0x51DE003AUL, 0xC8D75180UL, 0xBFD06116UL, 0x21B4F4B5UL, 0x56B3C423UL, 0xCFBA9599UL, 0xB8BDA50FUL,
  0x2802B89EUL, 0x5F058808UL, 0xC60CD9B2UL, 0xB10BE924UL, 0x2F6F7C87UL, 0x58684C11UL, 0xC1611DABUL, 0xB6662D3DUL,
  0x76DC4190UL, 0x01DB7106UL, 0x98D220BCUL, 0xEFD5102AUL, 0x71B18589UL, 0x06B6B51FUL, 0x9FBFE4A5UL, 0xE8B8D433UL,
  0x7807C9A2UL, 0x0F00F934UL, 0x9609A88EUL, 0xE10E9818UL, 0x7F6A0DBBUL, 0x086D3D2DUL, 0x91646C97UL, 0xE6635C01UL,
  0x6B6B51F4UL, 0x1C6C6162UL, 0x856530D8UL, 0xF262004EUL, 0x6C0695EDUL, 0x1B01A57BUL, 0x8208F4C1UL, 0xF50FC457UL,
  0x65B0D9C6UL, 0x12B7E950UL, 0x8BBEB8EAUL, 0xFCB9887CUL, 0x62DD1DDFUL, 0x15DA2D49UL, 0x8CD37CF3UL, 0xFBD44C65UL,
  0x4DB26158UL, 0x3AB551CEUL, 0xA3BC0074UL, 0xD4BB30E2UL, 0x4ADFA541UL, 0x3DD895D7UL, 0xA4D1C46DUL, 0xD3D6F4FBUL,
  0x4369E96AUL, 0x346ED9FCUL, 0xAD678846UL, 0xDA60B8D0UL, 0x44042D73UL, 0x33031DE5UL, 0xAA0A4C5FUL, 0xDD0D7CC9UL,
  0x5005713CUL, 0x270241AAUL, 0xBE0B1010UL, 0xC90C2086UL, 0x5768B525UL, 0x206F85B3UL, 0xB966D409UL, 0xCE61E49FUL,
  0x5EDEF90EUL, 0x29D9C998UL, 0xB0D09822UL, 0xC7D7A8B4UL, 0x59B33D17UL, 0x2EB40D81UL, 0xB7BD5C3BUL, 0xC0BA6CADUL,
  0xEDB88320UL, 0x9ABFB3B6UL, 0x03B6E20CUL, 0x74B1D29AUL, 0xEAD54739UL, 0x9DD277AFUL, 0x04DB2615UL, 0x73DC1683UL,
  0xE3630B12UL, 0x94643B84UL, 0x0D6D6A3EUL, 0x7A6A5AA8UL, 0xE40ECF0BUL, 0x9309FF9DUL, 0x0A00AE27UL, 0x7D079EB1UL,
  0xF00F9344UL, 0x8708A3D2UL, 0x1E01F268UL, 0x6906C2FEUL, 0xF762575DUL, 0x806567CBUL, 0x196C3671UL, 0x6E6B06E7UL,
  0xFED41B76UL, 0x89D32BE0UL, 0x10DA7A5AUL, 0x67DD4ACCUL, 0xF9B9DF6FUL, 0x8EBEEFF9UL, 0x17B7BE43UL, 0x60B08ED5UL,
  0xD6D6A3E8UL, 0xA1D1937EUL, 0x38D8C2C4UL, 0x4FDFF252UL, 0xD1BB67F1UL, 0xA6BC5767UL, 0x3FB506DDUL, 0x48B2364BUL,
  0xD80D2BDAUL, 0xAF0A1B4CUL, 0x36034AF6UL, 0x41047A60UL, 0xDF60EFC3UL, 0xA867DF55UL, 0x316E8EEFUL, 0x4669BE79UL,
  0xCB61B38CUL, 0xBC66831AUL, 0x256FD2A0UL, 0x5268E236UL, 0xCC0C7795UL, 0xBB0B4703UL, 0x220216B9UL, 0x5505262FUL,
  0xC5BA3BBEUL, 0xB2BD0B28UL, 0x2BB45A92UL, 0x5CB36A04UL, 0xC2D7FFA7UL, 0xB5D0CF31UL, 0x2CD99E8BUL, 0x5BDEAE1DUL,
  0x9B64C2B0UL, 0xEC63F226UL, 0x756AA39CUL, 0x026D930AUL, 0x9C0906A9UL, 0xEB0E363FUL, 0x72076785UL, 0x05005713UL,
  0x95BF4A82UL, 0xE2B87A14UL, 0x7BB12BAEUL, 0x0CB61B38UL, 0x92D28E9BUL, 0xE5D5BE0DUL, 0x7CDCEFB7UL, 0x0BDBDF21UL,
  0x86D3D2D4UL, 0xF1D4E242UL, 0x68DDB3F8UL, 0x1FDA836EUL, 0x81BE16CDUL, 0xF6B9265BUL, 0x6FB077E1UL, 0x18B74777UL,
  0x88085AE6UL, 0xFF0F6A70UL, 0x66063BCAUL, 0x11010B5CUL, 0x8F659EFFUL, 0xF862AE69UL, 0x616BFFD3UL, 0x166CCF45UL,
  0xA00AE278UL, 0xD70DD2EEUL, 0x4E048354UL, 0x3903B3C2UL, 0xA7672661UL, 0xD06016F7UL, 0x4969474DUL, 0x3E6E77DBUL,
  0xAED16A4AUL, 0xD9D65ADCUL, 0x40DF0B66UL, 0x37D83BF0UL, 0xA9BCAE53UL, 0xDEBB9EC5UL, 0x47B2CF7FUL, 0x30B5FFE9UL,
  0xBDBDF21CUL, 0xCABAC28AUL, 0x53B39330UL, 0x24B4A3A6UL, 0xBAD03605UL, 0xCDD70693UL, 0x54DE5729UL, 0x23D967BFUL,
  0xB3667A2EUL, 0xC4614AB8UL, 0x5D681B02UL, 0x2A6F2B94UL, 0xB40BBE37UL, 0xC30C8EA1UL, 0x5A05DF1BUL, 0x2D02EF8DUL
};

#define SPEEDUINO_TABLE_DIM       12
#define SPEEDUINO_TABLE_CELLS     (SPEEDUINO_TABLE_DIM * SPEEDUINO_TABLE_DIM)
#define SPEEDUINO_TABLE_AXIS_LEN  SPEEDUINO_TABLE_DIM
#define SPEEDUINO_TABLE_PAGE_SIZE (SPEEDUINO_TABLE_CELLS + (2 * SPEEDUINO_TABLE_AXIS_LEN))

const uint16_t pageSize[PAGE_COUNT] = {
  0,
  sizeof(struct ConfigPage1),
  SPEEDUINO_TABLE_PAGE_SIZE,
  SPEEDUINO_TABLE_PAGE_SIZE,
  sizeof(struct ConfigPage2),
  288, 128, 240, 384, 192, 192, 288, 192, 128, 288, 256
};

static uint8_t serialBuffer[SERIAL_BUFFER_SIZE];
static uint8_t serialBytesReceived = 0;
static bool    modernProtocol = false;
static uint8_t expectedLength = 0;

typedef enum {
  PAGE_WRITE_FAIL = 0,
  PAGE_WRITE_OK = 1,
  PAGE_WRITE_TABLE_CHANGED = 2
} PageWriteStatus;

/* ==========================================================================
 * HELPERS
 * ========================================================================== */
static uint32_t crc32Update(uint32_t crc, uint8_t dataByte) {
  uint8_t index = (uint8_t)((crc ^ dataByte) & 0xFF);
  return (crc >> 8) ^ crc32_table[index];
}

static uint8_t clampU8(int16_t value) {
  if (value < 0) return 0;
  if (value > 255) return 255;
  return (uint8_t)value;
}

static uint8_t encodeIgnitionValue(int8_t advance) {
  return clampU8((int16_t)advance + 40);
}

static int8_t decodeIgnitionValue(uint8_t stored) {
  return (int8_t)((int16_t)stored - 40);
}

static uint8_t encodeRpmBin(uint16_t rpm) {
  return clampU8((int16_t)(rpm / 100));
}

static uint16_t decodeRpmBin(uint8_t stored) {
  return (uint16_t)stored * 100U;
}

/* PLACEHOLDER: nao ha equivalente verificado a __heap_start/__brkval do
 * avr-libc para SDCC/HC08 - retorna 0 em vez de adivinhar um mecanismo de
 * introspeccao de heap nao confirmado. */
static uint16_t getFreeRam(void) {
  return 0;
}

static bool readPageByte(uint8_t page, uint16_t offset, uint8_t *value);
static PageWriteStatus writePageByte(uint8_t page, uint16_t offset, uint8_t value);

/* ==========================================================================
 * INICIALIZACAO
 * ========================================================================== */
void commsInit(void) {
  sciInit();
  serialBytesReceived = 0;
  modernProtocol = false;
  expectedLength = 0;
}

/* ==========================================================================
 * CRC32 / ENVIO
 * ========================================================================== */
uint32_t calculateCRC32(const uint8_t *data, uint16_t length) {
  uint32_t crc = 0xFFFFFFFFUL;
  uint16_t i;
  for (i = 0; i < length; i++) {
    crc = crc32Update(crc, data[i]);
  }
  return ~crc;
}

void sendByte(uint8_t data) {
  sciWriteByte(data);
}

void sendBytes(const uint8_t *data, uint16_t length) {
  sciWriteBytes(data, length);
}

void sendU16(uint16_t value) {
  sciWriteByte((uint8_t)(value & 0xFF));
  sciWriteByte((uint8_t)((value >> 8) & 0xFF));
}

void sendU16BE(uint16_t value) {
  sciWriteByte((uint8_t)((value >> 8) & 0xFF));
  sciWriteByte((uint8_t)(value & 0xFF));
}

void sendU32BE(uint32_t value) {
  sciWriteByte((uint8_t)((value >> 24) & 0xFF));
  sciWriteByte((uint8_t)((value >> 16) & 0xFF));
  sciWriteByte((uint8_t)((value >> 8) & 0xFF));
  sciWriteByte((uint8_t)(value & 0xFF));
}

/* ==========================================================================
 * PROCESSAMENTO PRINCIPAL
 * ========================================================================== */
void commsProcess(void) {
  if (!sciAvailable()) {
    return;
  }

  if (serialBytesReceived == 0) {
    uint8_t firstByte = sciReadByte();
    serialBuffer[0] = firstByte;
    serialBytesReceived = 1;

    if (firstByte >= 'A' && firstByte <= 'z') {
      modernProtocol = false;
      processLegacyCommand(firstByte);
      serialBytesReceived = 0;
      return;
    } else {
      modernProtocol = true;
      expectedLength = 0;
    }
  }

  if (modernProtocol) {
    while (sciAvailable() && serialBytesReceived < SERIAL_BUFFER_SIZE) {
      serialBuffer[serialBytesReceived++] = sciReadByte();

      if (serialBytesReceived == 2 && expectedLength == 0) {
        uint16_t parsedLength = ((uint16_t)serialBuffer[0] << 8) | serialBuffer[1];

        if (parsedLength > (SERIAL_BUFFER_SIZE - 6)) {
          serialBytesReceived = 0;
          expectedLength = 0;
          modernProtocol = false;
          return;
        }

        expectedLength = (uint8_t)parsedLength;
      }

      if (expectedLength > 0 && serialBytesReceived >= (2 + expectedLength + 4)) {
        processModernCommand();
        serialBytesReceived = 0;
        expectedLength = 0;
        modernProtocol = false;
        return;
      }
    }
  }
}

/* ==========================================================================
 * COMANDOS LEGACY
 * ========================================================================== */
void processLegacyCommand(uint8_t command) {
  switch (command) {
    case 'A': sendRealtimeData(); break;
    case 'I': sciPrintString("speeduino 202402"); break;
    case 'Q': sendFirmwareVersion(); break;
    case 'S': sendProductString(); break;
    case 'F': sendProtocolVersion(); break;
    case 'C': sendTestComm(); break;
    case 'B':
    case 'b': burnEEPROM(); break;
    case 'c': sendU16(2000); break;
    case 'm': sendU16(getFreeRam()); break;
    case 'N': sciPrintString("\r\n"); break;
    default: break;
  }
}

void sendRealtimeData(void) {
  uint8_t buffer[LOG_ENTRY_SIZE];
  buffer[0] = 0x00;
  buildRealtimePacket(&buffer[1]);
  sendBytes(buffer, LOG_ENTRY_SIZE);
}

void sendFirmwareVersion(void) { sciPrintString("Speeduino 202402"); }
void sendProductString(void)   { sciPrintString("Speeduino 202402"); }
void sendProtocolVersion(void) { sciPrintString("002"); }

void sendTestComm(void) {
  sendByte(0x00);
  sendByte(0xFF);
}

/* ==========================================================================
 * COMANDOS MODERN
 * ========================================================================== */
void processModernCommand(void) {
  uint8_t *payload = &serialBuffer[2];
  uint16_t payloadLength = expectedLength;
  uint32_t receivedCRC, calculatedCRC;
  uint8_t command;

  receivedCRC = ((uint32_t)serialBuffer[2 + payloadLength] << 24) |
                ((uint32_t)serialBuffer[2 + payloadLength + 1] << 16) |
                ((uint32_t)serialBuffer[2 + payloadLength + 2] << 8) |
                ((uint32_t)serialBuffer[2 + payloadLength + 3]);

  calculatedCRC = calculateCRC32(payload, payloadLength);

  if (receivedCRC != calculatedCRC) {
    uint8_t errorByte = SERIAL_RC_CRC_ERR;
    sendU16BE(1);
    sendByte(errorByte);
    sendU32BE(calculateCRC32(&errorByte, 1));
    return;
  }

  command = payload[0];

  switch (command) {
    case 'A': {
      uint8_t buffer[1 + 1 + LOG_ENTRIES_COUNT];
      uint16_t responseLength = 1 + 1 + LOG_ENTRIES_COUNT;
      buffer[0] = SERIAL_RC_OK;
      buffer[1] = 0x00;
      buildRealtimePacket(&buffer[2]);

      sendU16BE(responseLength);
      sendBytes(buffer, responseLength);
      sendU32BE(calculateCRC32(buffer, responseLength));
      break;
    }

    case 'C': {
      uint8_t testBuf[2];
      testBuf[0] = SERIAL_RC_OK;
      testBuf[1] = 0xFF;
      sendU16BE(2);
      sendBytes(testBuf, 2);
      sendU32BE(calculateCRC32(testBuf, 2));
      break;
    }

    case 'f': {
      uint8_t tempBuf[6];
      tempBuf[0] = SERIAL_RC_OK;
      tempBuf[1] = 2;
      tempBuf[2] = (BLOCKING_FACTOR >> 8) & 0xFF;
      tempBuf[3] = BLOCKING_FACTOR & 0xFF;
      tempBuf[4] = (TABLE_BLOCKING_FACTOR >> 8) & 0xFF;
      tempBuf[5] = TABLE_BLOCKING_FACTOR & 0xFF;
      sendU16BE(6);
      sendBytes(tempBuf, 6);
      sendU32BE(calculateCRC32(tempBuf, 6));
      break;
    }

    case 'I': {
      uint8_t tempBuf[32];
      uint8_t len = 0;
      const char *iface = "speeduino 202402";
      uint8_t ilen = (uint8_t)strlen(iface);
      tempBuf[len++] = SERIAL_RC_OK;
      memcpy(&tempBuf[len], iface, ilen);
      len = (uint8_t)(len + ilen);
      sendU16BE(len);
      sendBytes(tempBuf, len);
      sendU32BE(calculateCRC32(tempBuf, len));
      break;
    }

    case 'Q': {
      uint8_t tempBuf[32];
      uint8_t len = 0;
      const char *ver = "speeduino 202207";
      uint8_t vlen = (uint8_t)strlen(ver);
      tempBuf[len++] = SERIAL_RC_OK;
      memcpy(&tempBuf[len], ver, vlen);
      len = (uint8_t)(len + vlen);
      sendU16BE(len);
      sendBytes(tempBuf, len);
      sendU32BE(calculateCRC32(tempBuf, len));
      break;
    }

    case 'S': {
      uint8_t tempBuf[32];
      uint8_t len = 0;
      const char *prod = "Speeduino 2024.02.4";
      uint8_t plen = (uint8_t)strlen(prod);
      tempBuf[len++] = SERIAL_RC_OK;
      memcpy(&tempBuf[len], prod, plen);
      len = (uint8_t)(len + plen);
      sendU16BE(len);
      sendBytes(tempBuf, len);
      sendU32BE(calculateCRC32(tempBuf, len));
      break;
    }

    case 'F': {
      uint8_t tempBuf[4];
      tempBuf[0] = SERIAL_RC_OK;
      tempBuf[1] = '0';
      tempBuf[2] = '0';
      tempBuf[3] = '2';
      sendU16BE(4);
      sendBytes(tempBuf, 4);
      sendU32BE(calculateCRC32(tempBuf, 4));
      break;
    }

    case 'p': {
      if (payloadLength >= 7) {
        uint8_t page = payload[2];
        uint16_t offset = payload[3] | ((uint16_t)payload[4] << 8);
        uint16_t length = payload[5] | ((uint16_t)payload[6] << 8);
        sendPageValues(page, offset, length);
      } else {
        uint8_t err = SERIAL_RC_UKWN_ERR;
        sendU16BE(1);
        sendByte(err);
        sendU32BE(calculateCRC32(&err, 1));
      }
      break;
    }

    case 'M': {
      uint8_t page = payload[2];
      uint16_t offset = payload[3] | ((uint16_t)payload[4] << 8);
      uint16_t length = payload[5] | ((uint16_t)payload[6] << 8);
      uint8_t *data = &payload[7];
      uint8_t result = writePageValues(page, offset, length, data);

      sendU16BE(1);
      sendByte(result);
      sendU32BE(calculateCRC32(&result, 1));
      break;
    }

    case 'd': {
      if (payloadLength >= 3) {
        uint8_t page = payload[2];
        sendPageCRC32(page);
      } else {
        uint8_t err = SERIAL_RC_UKWN_ERR;
        sendU16BE(1);
        sendByte(err);
        sendU32BE(calculateCRC32(&err, 1));
      }
      break;
    }

    case 'r': {
      if (payloadLength >= 7) {
        uint8_t subcmd = payload[2];
        uint16_t offset = payload[3] | ((uint16_t)payload[4] << 8);
        uint16_t length = payload[5] | ((uint16_t)payload[6] << 8);
        sendOutputChannels(subcmd, offset, length);
      } else {
        uint8_t err = SERIAL_RC_UKWN_ERR;
        sendU16BE(1);
        sendByte(err);
        sendU32BE(calculateCRC32(&err, 1));
      }
      break;
    }

    case 'b':
    case 'B': {
      uint8_t statusByte = SERIAL_RC_BURN_OK;
      burnEEPROM();
      sendU16BE(1);
      sendByte(statusByte);
      sendU32BE(calculateCRC32(&statusByte, 1));
      break;
    }

    default: {
      uint8_t err = SERIAL_RC_UKWN_ERR;
      sendU16BE(1);
      sendByte(err);
      sendU32BE(calculateCRC32(&err, 1));
      break;
    }
  }
}

/* ==========================================================================
 * FUNCOES DE PAGINA
 * ========================================================================== */
uint16_t getPageSize(uint8_t page) {
  if (page >= PAGE_COUNT) return 0;
  return pageSize[page];
}

static bool readStructPageByte(const uint8_t *base, uint16_t size, uint16_t offset, uint8_t *value) {
  if (offset >= size) return false;
  *value = base[offset];
  return true;
}

static PageWriteStatus writeStructPageByte(uint8_t *base, uint16_t size, uint16_t offset, uint8_t value) {
  if (offset >= size) return PAGE_WRITE_FAIL;
  base[offset] = value;
  return PAGE_WRITE_OK;
}

static bool readStubPageByte(uint8_t page, uint16_t offset, uint8_t *value) {
  uint16_t size = getPageSize(page);
  if (offset >= size) return false;
  *value = 0;
  return true;
}

static bool readVeTablePageByte(uint16_t offset, uint8_t *value) {
  if (offset >= SPEEDUINO_TABLE_PAGE_SIZE) return false;

  if (offset < SPEEDUINO_TABLE_CELLS) {
    *value = eepromReadByte(veTable.eepromValuesBase + offset);
    return true;
  }
  if (offset < SPEEDUINO_TABLE_CELLS + SPEEDUINO_TABLE_AXIS_LEN) {
    uint8_t idx = (uint8_t)(offset - SPEEDUINO_TABLE_CELLS);
    *value = encodeRpmBin(veTable.axisX[idx]);
    return true;
  }
  {
    uint8_t idx = (uint8_t)(offset - (SPEEDUINO_TABLE_CELLS + SPEEDUINO_TABLE_AXIS_LEN));
    *value = veTable.axisY[idx];
    return true;
  }
}

static PageWriteStatus writeVeTablePageByte(uint16_t offset, uint8_t value) {
  if (offset >= SPEEDUINO_TABLE_PAGE_SIZE) return PAGE_WRITE_FAIL;

  if (offset < SPEEDUINO_TABLE_CELLS) {
    eepromWriteByte(veTable.eepromValuesBase + offset, value);
    return PAGE_WRITE_TABLE_CHANGED;
  }
  if (offset < SPEEDUINO_TABLE_CELLS + SPEEDUINO_TABLE_AXIS_LEN) {
    uint8_t idx = (uint8_t)(offset - SPEEDUINO_TABLE_CELLS);
    veTable.axisX[idx] = decodeRpmBin(value);
    return PAGE_WRITE_TABLE_CHANGED;
  }
  {
    uint8_t idx = (uint8_t)(offset - (SPEEDUINO_TABLE_CELLS + SPEEDUINO_TABLE_AXIS_LEN));
    veTable.axisY[idx] = value;
    return PAGE_WRITE_TABLE_CHANGED;
  }
}

static bool readIgnTablePageByte(uint16_t offset, uint8_t *value) {
  if (offset >= SPEEDUINO_TABLE_PAGE_SIZE) return false;

  if (offset < SPEEDUINO_TABLE_CELLS) {
    int8_t cellValue = eepromReadI8(ignTable.eepromValuesBase + offset);
    *value = encodeIgnitionValue(cellValue);
    return true;
  }
  if (offset < SPEEDUINO_TABLE_CELLS + SPEEDUINO_TABLE_AXIS_LEN) {
    uint8_t idx = (uint8_t)(offset - SPEEDUINO_TABLE_CELLS);
    *value = encodeRpmBin(ignTable.axisX[idx]);
    return true;
  }
  {
    uint8_t idx = (uint8_t)(offset - (SPEEDUINO_TABLE_CELLS + SPEEDUINO_TABLE_AXIS_LEN));
    *value = ignTable.axisY[idx];
    return true;
  }
}

static PageWriteStatus writeIgnTablePageByte(uint16_t offset, uint8_t value) {
  if (offset >= SPEEDUINO_TABLE_PAGE_SIZE) return PAGE_WRITE_FAIL;

  if (offset < SPEEDUINO_TABLE_CELLS) {
    eepromWriteI8(ignTable.eepromValuesBase + offset, decodeIgnitionValue(value));
    return PAGE_WRITE_TABLE_CHANGED;
  }
  if (offset < SPEEDUINO_TABLE_CELLS + SPEEDUINO_TABLE_AXIS_LEN) {
    uint8_t idx = (uint8_t)(offset - SPEEDUINO_TABLE_CELLS);
    ignTable.axisX[idx] = decodeRpmBin(value);
    return PAGE_WRITE_TABLE_CHANGED;
  }
  {
    uint8_t idx = (uint8_t)(offset - (SPEEDUINO_TABLE_CELLS + SPEEDUINO_TABLE_AXIS_LEN));
    ignTable.axisY[idx] = value;
    return PAGE_WRITE_TABLE_CHANGED;
  }
}

static bool readPageByte(uint8_t page, uint16_t offset, uint8_t *value) {
  switch (page) {
    case 1: return readStructPageByte((uint8_t *)&configPage1, sizeof(struct ConfigPage1), offset, value);
    case 2: return readVeTablePageByte(offset, value);
    case 3: return readIgnTablePageByte(offset, value);
    case 4: return readStructPageByte((uint8_t *)&configPage2, sizeof(struct ConfigPage2), offset, value);
    default: return readStubPageByte(page, offset, value);
  }
}

static PageWriteStatus writePageByte(uint8_t page, uint16_t offset, uint8_t value) {
  switch (page) {
    case 1: return writeStructPageByte((uint8_t *)&configPage1, sizeof(struct ConfigPage1), offset, value);
    case 2: return writeVeTablePageByte(offset, value);
    case 3: return writeIgnTablePageByte(offset, value);
    case 4: return writeStructPageByte((uint8_t *)&configPage2, sizeof(struct ConfigPage2), offset, value);
    default: {
      uint16_t pageSz = getPageSize(page);
      if (pageSz == 0 || offset >= pageSz) return PAGE_WRITE_FAIL;
      return PAGE_WRITE_OK;
    }
  }
}

void sendPageValues(uint8_t page, uint16_t offset, uint16_t length) {
  uint16_t pageSz = getPageSize(page);
  uint16_t available, actualLength, responseLength, remaining, pos;
  uint8_t tempBuf[32];
  uint32_t crc = 0xFFFFFFFFUL;

  if (pageSz == 0) {
    uint8_t err = SERIAL_RC_RANGE_ERR;
    sendU16BE(1);
    sendByte(err);
    sendU32BE(calculateCRC32(&err, 1));
    return;
  }

  available = (offset < pageSz) ? (uint16_t)(pageSz - offset) : 0;
  actualLength = (length < available) ? length : available;
  responseLength = (uint16_t)(1 + actualLength);

  sendU16BE(responseLength);

  sendByte(SERIAL_RC_OK);
  crc = crc32Update(crc, SERIAL_RC_OK);

  remaining = actualLength;
  pos = 0;

  while (remaining > 0) {
    uint16_t blockSize = (remaining < sizeof(tempBuf)) ? remaining : (uint16_t)sizeof(tempBuf);
    uint16_t i;

    for (i = 0; i < blockSize; i++) {
      uint8_t byteValue = 0;
      if (!readPageByte(page, (uint16_t)(offset + pos + i), &byteValue)) {
        byteValue = 0;
      }
      tempBuf[i] = byteValue;
    }

    sendBytes(tempBuf, blockSize);

    for (i = 0; i < blockSize; i++) {
      crc = crc32Update(crc, tempBuf[i]);
    }

    pos = (uint16_t)(pos + blockSize);
    remaining = (uint16_t)(remaining - blockSize);
  }

  crc = ~crc;
  sendU32BE(crc);
}

uint8_t writePageValues(uint8_t page, uint16_t offset, uint16_t length, const uint8_t *data) {
  uint16_t pageSz = getPageSize(page);
  uint16_t i;

  if (pageSz == 0 || (offset + length) > pageSz) {
    return SERIAL_RC_RANGE_ERR;
  }

  for (i = 0; i < length; i++) {
    PageWriteStatus status = writePageByte(page, (uint16_t)(offset + i), data[i]);
    if (status == PAGE_WRITE_FAIL) {
      return SERIAL_RC_RANGE_ERR;
    }
  }

  return SERIAL_RC_OK;
}

void sendPageCRC32(uint8_t page) {
  uint16_t pageSz = getPageSize(page);
  uint32_t crc = 0xFFFFFFFFUL, pageCRC, reversedCRC;
  uint16_t i;
  uint8_t response[5];

  if (pageSz == 0) {
    uint8_t err = SERIAL_RC_RANGE_ERR;
    sendU16BE(1);
    sendByte(err);
    sendU32BE(calculateCRC32(&err, 1));
    return;
  }

  for (i = 0; i < pageSz; i++) {
    uint8_t byteValue = 0;
    if (!readPageByte(page, i, &byteValue)) {
      byteValue = 0;
    }
    crc = crc32Update(crc, byteValue);
  }

  pageCRC = ~crc;
  reversedCRC = ((pageCRC & 0xFFUL) << 24) | ((pageCRC & 0xFF00UL) << 8) |
                ((pageCRC & 0xFF0000UL) >> 8) | ((pageCRC & 0xFF000000UL) >> 24);

  response[0] = SERIAL_RC_OK;
  response[1] = (uint8_t)(reversedCRC & 0xFF);
  response[2] = (uint8_t)((reversedCRC >> 8) & 0xFF);
  response[3] = (uint8_t)((reversedCRC >> 16) & 0xFF);
  response[4] = (uint8_t)((reversedCRC >> 24) & 0xFF);

  sendU16BE(5);
  sendBytes(response, 5);
  sendU32BE(calculateCRC32(response, 5));
}

void sendOutputChannels(uint8_t subcmd, uint16_t offset, uint16_t length) {
  if (subcmd == 0x30) {
    uint8_t fullBuffer[1 + LOG_ENTRIES_COUNT];
    uint16_t fullBufferSize = 1 + LOG_ENTRIES_COUNT;
    uint32_t crc = 0xFFFFFFFFUL;
    uint16_t responseLength, i;

    fullBuffer[0] = 0x00;
    buildRealtimePacket(&fullBuffer[1]);

    if (offset >= fullBufferSize) {
      offset = 0;
      length = 0;
    }
    if ((uint16_t)(offset + length) > fullBufferSize) {
      length = (uint16_t)(fullBufferSize - offset);
    }

    responseLength = (uint16_t)(1 + length);
    sendU16BE(responseLength);
    sendByte(SERIAL_RC_OK);
    sendBytes(fullBuffer + offset, length);

    crc = crc32Update(crc, SERIAL_RC_OK);
    for (i = 0; i < length; i++) {
      crc = crc32Update(crc, fullBuffer[offset + i]);
    }
    crc = ~crc;
    sendU32BE(crc);
  } else {
    uint8_t err = SERIAL_RC_UKWN_ERR;
    sendU16BE(1);
    sendByte(err);
    sendU32BE(calculateCRC32(&err, 1));
  }
}

void burnEEPROM(void) {
  saveAllConfig();
}

/* ==========================================================================
 * REALTIME DATA PACKET (126 bytes de log entries)
 * ========================================================================== */
void buildRealtimePacket(uint8_t *buffer) {
  uint16_t map16, freeRam, loops;

  memset(buffer, 0, LOG_ENTRIES_COUNT);

  buffer[0] = (uint8_t)(currentStatus.secl & 0xFF);

  buffer[1] = 0;
  if (currentStatus.RPM > 0) buffer[1] |= 0x01;

  buffer[2] = currentStatus.engineStatus;
  buffer[3] = currentStatus.hasSync ? 0 : 1;

  map16 = (uint16_t)(currentStatus.MAP * 10);
  buffer[4] = (uint8_t)(map16 & 0xFF);
  buffer[5] = (uint8_t)((map16 >> 8) & 0xFF);

  buffer[6] = (uint8_t)(currentStatus.IAT + 40);
  buffer[7] = (uint8_t)(currentStatus.coolant + 40);
  buffer[8] = currentStatus.batCorrection;
  buffer[9] = currentStatus.battery10;
  buffer[10] = currentStatus.O2;
  buffer[11] = 100;
  buffer[12] = 100;
  buffer[13] = currentStatus.wueCorrection;

  buffer[14] = (uint8_t)(currentStatus.RPM & 0xFF);
  buffer[15] = (uint8_t)((currentStatus.RPM >> 8) & 0xFF);

  buffer[24] = (uint8_t)(currentStatus.advance + 40);
  buffer[25] = currentStatus.TPS;

  loops = 2000;
  buffer[26] = (uint8_t)(loops & 0xFF);
  buffer[27] = (uint8_t)((loops >> 8) & 0xFF);

  freeRam = getFreeRam();
  buffer[28] = (uint8_t)(freeRam & 0xFF);
  buffer[29] = (uint8_t)((freeRam >> 8) & 0xFF);

  buffer[32] = currentStatus.hasSync ? 0x01 : 0x00;
  buffer[35] = 0;
  buffer[38] = currentStatus.idleValveDuty;
  buffer[41] = 100;

  buffer[76] = (uint8_t)(currentStatus.PW1 & 0xFF);
  buffer[77] = (uint8_t)((currentStatus.PW1 >> 8) & 0xFF);
  buffer[78] = (uint8_t)(currentStatus.PW2 & 0xFF);
  buffer[79] = (uint8_t)((currentStatus.PW2 >> 8) & 0xFF);
  buffer[80] = (uint8_t)(currentStatus.PW3 & 0xFF);
  buffer[81] = (uint8_t)((currentStatus.PW3 >> 8) & 0xFF);
  buffer[82] = 0;
  buffer[83] = 0;

  buffer[92] = (uint8_t)(currentStatus.CLIdleTarget / 10U);
  buffer[102] = currentStatus.VE;
  buffer[104] = 0;
  buffer[105] = 0;
}
