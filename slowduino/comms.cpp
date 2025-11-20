/**
 * @file comms.cpp
 * @brief Implementação da comunicação com TunerStudio
 */

#include "comms.h"
#include "storage.h"
#include "tables.h"

// ============================================================================
// TABELA CRC32
// ============================================================================

// Tabela lookup para CRC32 (economiza processamento)
static const uint32_t crc32_table[256] PROGMEM = {
  0x00000000, 0x77073096, 0xEE0E612C, 0x990951BA, 0x076DC419, 0x706AF48F, 0xE963A535, 0x9E6495A3,
  0x0EDB8832, 0x79DCB8A4, 0xE0D5E91E, 0x97D2D988, 0x09B64C2B, 0x7EB17CBD, 0xE7B82D07, 0x90BF1D91,
  0x1DB71064, 0x6AB020F2, 0xF3B97148, 0x84BE41DE, 0x1ADAD47D, 0x6DDDE4EB, 0xF4D4B551, 0x83D385C7,
  0x136C9856, 0x646BA8C0, 0xFD62F97A, 0x8A65C9EC, 0x14015C4F, 0x63066CD9, 0xFA0F3D63, 0x8D080DF5,
  0x3B6E20C8, 0x4C69105E, 0xD56041E4, 0xA2677172, 0x3C03E4D1, 0x4B04D447, 0xD20D85FD, 0xA50AB56B,
  0x35B5A8FA, 0x42B2986C, 0xDBBBC9D6, 0xACBCF940, 0x32D86CE3, 0x45DF5C75, 0xDCD60DCF, 0xABD13D59,
  0x26D930AC, 0x51DE003A, 0xC8D75180, 0xBFD06116, 0x21B4F4B5, 0x56B3C423, 0xCFBA9599, 0xB8BDA50F,
  0x2802B89E, 0x5F058808, 0xC60CD9B2, 0xB10BE924, 0x2F6F7C87, 0x58684C11, 0xC1611DAB, 0xB6662D3D,
  0x76DC4190, 0x01DB7106, 0x98D220BC, 0xEFD5102A, 0x71B18589, 0x06B6B51F, 0x9FBFE4A5, 0xE8B8D433,
  0x7807C9A2, 0x0F00F934, 0x9609A88E, 0xE10E9818, 0x7F6A0DBB, 0x086D3D2D, 0x91646C97, 0xE6635C01,
  0x6B6B51F4, 0x1C6C6162, 0x856530D8, 0xF262004E, 0x6C0695ED, 0x1B01A57B, 0x8208F4C1, 0xF50FC457,
  0x65B0D9C6, 0x12B7E950, 0x8BBEB8EA, 0xFCB9887C, 0x62DD1DDF, 0x15DA2D49, 0x8CD37CF3, 0xFBD44C65,
  0x4DB26158, 0x3AB551CE, 0xA3BC0074, 0xD4BB30E2, 0x4ADFA541, 0x3DD895D7, 0xA4D1C46D, 0xD3D6F4FB,
  0x4369E96A, 0x346ED9FC, 0xAD678846, 0xDA60B8D0, 0x44042D73, 0x33031DE5, 0xAA0A4C5F, 0xDD0D7CC9,
  0x5005713C, 0x270241AA, 0xBE0B1010, 0xC90C2086, 0x5768B525, 0x206F85B3, 0xB966D409, 0xCE61E49F,
  0x5EDEF90E, 0x29D9C998, 0xB0D09822, 0xC7D7A8B4, 0x59B33D17, 0x2EB40D81, 0xB7BD5C3B, 0xC0BA6CAD,
  0xEDB88320, 0x9ABFB3B6, 0x03B6E20C, 0x74B1D29A, 0xEAD54739, 0x9DD277AF, 0x04DB2615, 0x73DC1683,
  0xE3630B12, 0x94643B84, 0x0D6D6A3E, 0x7A6A5AA8, 0xE40ECF0B, 0x9309FF9D, 0x0A00AE27, 0x7D079EB1,
  0xF00F9344, 0x8708A3D2, 0x1E01F268, 0x6906C2FE, 0xF762575D, 0x806567CB, 0x196C3671, 0x6E6B06E7,
  0xFED41B76, 0x89D32BE0, 0x10DA7A5A, 0x67DD4ACC, 0xF9B9DF6F, 0x8EBEEFF9, 0x17B7BE43, 0x60B08ED5,
  0xD6D6A3E8, 0xA1D1937E, 0x38D8C2C4, 0x4FDFF252, 0xD1BB67F1, 0xA6BC5767, 0x3FB506DD, 0x48B2364B,
  0xD80D2BDA, 0xAF0A1B4C, 0x36034AF6, 0x41047A60, 0xDF60EFC3, 0xA867DF55, 0x316E8EEF, 0x4669BE79,
  0xCB61B38C, 0xBC66831A, 0x256FD2A0, 0x5268E236, 0xCC0C7795, 0xBB0B4703, 0x220216B9, 0x5505262F,
  0xC5BA3BBE, 0xB2BD0B28, 0x2BB45A92, 0x5CB36A04, 0xC2D7FFA7, 0xB5D0CF31, 0x2CD99E8B, 0x5BDEAE1D,
  0x9B64C2B0, 0xEC63F226, 0x756AA39C, 0x026D930A, 0x9C0906A9, 0xEB0E363F, 0x72076785, 0x05005713,
  0x95BF4A82, 0xE2B87A14, 0x7BB12BAE, 0x0CB61B38, 0x92D28E9B, 0xE5D5BE0D, 0x7CDCEFB7, 0x0BDBDF21,
  0x86D3D2D4, 0xF1D4E242, 0x68DDB3F8, 0x1FDA836E, 0x81BE16CD, 0xF6B9265B, 0x6FB077E1, 0x18B74777,
  0x88085AE6, 0xFF0F6A70, 0x66063BCA, 0x11010B5C, 0x8F659EFF, 0xF862AE69, 0x616BFFD3, 0x166CCF45,
  0xA00AE278, 0xD70DD2EE, 0x4E048354, 0x3903B3C2, 0xA7672661, 0xD06016F7, 0x4969474D, 0x3E6E77DB,
  0xAED16A4A, 0xD9D65ADC, 0x40DF0B66, 0x37D83BF0, 0xA9BCAE53, 0xDEBB9EC5, 0x47B2CF7F, 0x30B5FFE9,
  0xBDBDF21C, 0xCABAC28A, 0x53B39330, 0x24B4A3A6, 0xBAD03605, 0xCDD70693, 0x54DE5729, 0x23D967BF,
  0xB3667A2E, 0xC4614AB8, 0x5D681B02, 0x2A6F2B94, 0xB40BBE37, 0xC30C8EA1, 0x5A05DF1B, 0x2D02EF8D
};

// ============================================================================
// VARIÁVEIS GLOBAIS
// ============================================================================

// Tamanhos das páginas (compatibilidade Speeduino)
// IMPORTANTE: Tamanhos hardcoded para garantir compatibilidade com TunerStudio
// sizeof() pode retornar valores incorretos devido a padding do compilador
const uint16_t pageSize[PAGE_COUNT] PROGMEM = {
  0,    // Page 0: não usada
  128,  // Page 1: config VE (veSetPage)
  288,  // Page 2: VE map
  288,  // Page 3: Ign map
  128,  // Page 4: Ign config
  288,  // Page 5: AFR map
  128,  // Page 6: AFR config
  240,  // Page 7: Boost/VVT map
  384,  // Page 8: Seq fuel trims
  192,  // Page 9: CAN config
  192,  // Page10: Warmup
  288,  // Page11: Fuel map 2
  192,  // Page12: WMI / aux maps
  128,  // Page13: Programmable outputs
  288,  // Page14: Ign map 2
  256   // Page15: Boost/VVT map 2
};

static_assert(sizeof(ConfigPage1) >= 128, "ConfigPage1 precisa ter 128 bytes");
static_assert(sizeof(ConfigPage2) >= 128, "ConfigPage2 precisa ter 128 bytes");

// Buffer serial
static uint8_t serialBuffer[SERIAL_BUFFER_SIZE];
static uint8_t serialBytesReceived = 0;
static bool modernProtocol = false;
static uint16_t expectedLength = 0;

// ============================================================================
// CONSTANTES AUXILIARES PARA PÁGINAS SPEEDUINO
// ============================================================================
static constexpr uint8_t SPEEDUINO_TABLE_DIM = 16;
static constexpr uint16_t SPEEDUINO_TABLE_CELLS = SPEEDUINO_TABLE_DIM * SPEEDUINO_TABLE_DIM;  // 256
static constexpr uint16_t SPEEDUINO_TABLE_AXIS_LEN = SPEEDUINO_TABLE_DIM;                     // 16
static constexpr uint16_t SPEEDUINO_TABLE_PAGE_SIZE = SPEEDUINO_TABLE_CELLS + (2 * SPEEDUINO_TABLE_AXIS_LEN);  // 288
static_assert(SPEEDUINO_TABLE_PAGE_SIZE == 288, "Tabela Speeduino deve ter 288 bytes");
static_assert(TABLE_SIZE_X == SPEEDUINO_TABLE_DIM, "VE table deve ser 16x16 para compatibilidade Speeduino");
static_assert(TABLE_SIZE_Y == SPEEDUINO_TABLE_DIM, "VE table deve ser 16x16 para compatibilidade Speeduino");

enum PageWriteStatus : uint8_t {
  PAGE_WRITE_FAIL = 0,
  PAGE_WRITE_OK = 1,
  PAGE_WRITE_TABLE_CHANGED = 2
};

// ============================================================================
// HELPERS
// ============================================================================
static inline uint32_t crc32Update(uint32_t crc, uint8_t dataByte) {
  uint8_t index = (crc ^ dataByte) & 0xFF;
  return (crc >> 8) ^ pgm_read_dword(&crc32_table[index]);
}

static inline uint8_t clampU8(int16_t value) {
  if (value < 0) return 0;
  if (value > 255) return 255;
  return (uint8_t)value;
}

static inline uint8_t encodeIgnitionValue(int8_t advance) {
  return clampU8((int16_t)advance + 40);
}

static inline int8_t decodeIgnitionValue(uint8_t stored) {
  return (int8_t)((int16_t)stored - 40);
}

static inline uint8_t encodeRpmBin(uint16_t rpm) {
  return clampU8(rpm / 100);
}

static inline uint16_t decodeRpmBin(uint8_t stored) {
  return (uint16_t)stored * 100U;
}

static bool readPageByte(uint8_t page, uint16_t offset, uint8_t& value);
static PageWriteStatus writePageByte(uint8_t page, uint16_t offset, uint8_t value);

// ============================================================================
// INICIALIZAÇÃO
// ============================================================================

void commsInit() {
  // Serial já foi inicializado no setup()
  serialBytesReceived = 0;
  modernProtocol = false;
  expectedLength = 0;
}

// ============================================================================
// CRC32
// ============================================================================

uint32_t calculateCRC32(const uint8_t* data, uint16_t length) {
  uint32_t crc = 0xFFFFFFFF;

  for (uint16_t i = 0; i < length; i++) {
    uint8_t index = (crc ^ data[i]) & 0xFF;
    crc = (crc >> 8) ^ pgm_read_dword(&crc32_table[index]);
  }

  return ~crc;
}

// ============================================================================
// FUNÇÕES DE ENVIO
// ============================================================================

void sendU16(uint16_t value) {
  // Little-endian
  Serial.write(value & 0xFF);
  Serial.write((value >> 8) & 0xFF);
}

void sendU16BE(uint16_t value) {
  // Big-endian (para length header Modern Protocol)
  Serial.write((value >> 8) & 0xFF);
  Serial.write(value & 0xFF);
}

void sendU32BE(uint32_t value) {
  // Big-endian (para CRC32)
  Serial.write((value >> 24) & 0xFF);
  Serial.write((value >> 16) & 0xFF);
  Serial.write((value >> 8) & 0xFF);
  Serial.write(value & 0xFF);
}

// ============================================================================
// PROCESSAMENTO PRINCIPAL
// ============================================================================

void commsProcess() {
  if (!Serial.available()) {
    return;
  }

  // Lê primeiro byte para detectar protocolo
  if (serialBytesReceived == 0) {
    uint8_t firstByte = Serial.read();
    serialBuffer[0] = firstByte;
    serialBytesReceived = 1;

    // Detecta protocolo
    if (firstByte >= 'A' && firstByte <= 'z') {
      // ASCII = Legacy Protocol
      modernProtocol = false;
      // Processa imediatamente (comandos de 1 byte)
      processLegacyCommand(firstByte);
      serialBytesReceived = 0;
      return;
    } else {
      // Modern Protocol - precisa ler length header (2 bytes total)
      modernProtocol = true;
      expectedLength = 0;  // Será lido do header
    }
  }

  // Modern Protocol: continua lendo
  if (modernProtocol) {
    // Lê bytes disponíveis
    while (Serial.available() && serialBytesReceived < SERIAL_BUFFER_SIZE) {
      serialBuffer[serialBytesReceived++] = Serial.read();

      // Leu o length header completo? (2 bytes)
      if (serialBytesReceived == 2 && expectedLength == 0) {
        // Length é big-endian
        expectedLength = ((uint16_t)serialBuffer[0] << 8) | serialBuffer[1];

        // Valida tamanho
        if (expectedLength > (SERIAL_BUFFER_SIZE - 6)) {
          // Muito grande! Reset
          serialBytesReceived = 0;
          expectedLength = 0;
          modernProtocol = false;
          return;
        }
      }

      // Recebeu mensagem completa? [2-byte length] [payload] [4-byte CRC]
      if (expectedLength > 0 && serialBytesReceived >= (2 + expectedLength + 4)) {
        // Processa comando modern
        processModernCommand();

        // Reset para próximo comando
        serialBytesReceived = 0;
        expectedLength = 0;
        modernProtocol = false;
        return;
      }
    }
  }
}

// ============================================================================
// COMANDOS LEGACY PROTOCOL
// ============================================================================

void processLegacyCommand(uint8_t command) {
  switch (command) {
    case 'A':  // Realtime data
      sendRealtimeData();
      break;

    case 'I':  // Interface version (compatibilidade Speeduino)
      Serial.print(F("speeduino 202402"));
      break;

    case 'Q':  // Firmware version
      sendFirmwareVersion();
      break;

    case 'S':  // Product string
      sendProductString();
      break;

    case 'F':  // Protocol version
      sendProtocolVersion();
      break;

    case 'C':  // Test comm
      sendTestComm();  // Legacy: 0x00 0xFF direto
      break;

    case 'B':  // Burn EEPROM (legacy)
    case 'b':
      burnEEPROM();
      break;

    case 'c':  // Loops per second
      sendU16(2000);  // ~2000 loops/sec
      break;

    case 'm':  // Free RAM
      {
        extern int __heap_start, *__brkval;
        int v;
        uint16_t freeRam = (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
        sendU16(freeRam);
      }
      break;

    case 'N':  // New line
      Serial.println();
      break;

    default:
      // Comando desconhecido - ignora
      break;
  }
}

void sendRealtimeData() {
  // Legacy protocol: envia offset byte + 126 log entries = 127 bytes total
  uint8_t buffer[LOG_ENTRY_SIZE];  // 127 bytes
  buffer[0] = 0x00;  // Offset byte
  buildRealtimePacket(&buffer[1]);  // Log entries após offset
  sendBytes(buffer, LOG_ENTRY_SIZE);  // Envia 127 bytes
}

void sendFirmwareVersion() {
  //Serial.print(F("slowduino "));
  //Serial.print(F(SLOWDUINO_VERSION));
  Serial.print(F("Speeduino 202402"));
}

void sendProductString() {
  //Serial.print(F("Slowduino "));
  //Serial.print(F(SLOWDUINO_VERSION));
  Serial.print(F("Speeduino 202402"));
}

void sendProtocolVersion() {
  Serial.print(F("002"));  // Versão 002 do protocolo
}

void sendTestComm() {
  // Legacy: envia direto
  sendByte(0x00);
  sendByte(0xFF);
}

// ============================================================================
// COMANDOS MODERN PROTOCOL
// ============================================================================

void processModernCommand() {
  // Extrai payload (pula length header de 2 bytes)
  uint8_t* payload = &serialBuffer[2];
  uint16_t payloadLength = expectedLength;

  // Extrai CRC recebido (últimos 4 bytes)
  uint32_t receivedCRC = ((uint32_t)serialBuffer[2 + payloadLength] << 24) |
                         ((uint32_t)serialBuffer[2 + payloadLength + 1] << 16) |
                         ((uint32_t)serialBuffer[2 + payloadLength + 2] << 8) |
                         ((uint32_t)serialBuffer[2 + payloadLength + 3]);

  // Calcula CRC do payload
  uint32_t calculatedCRC = calculateCRC32(payload, payloadLength);

  // Valida CRC
  if (receivedCRC != calculatedCRC) {
    // CRC inválido - envia erro
    uint8_t errorByte = SERIAL_RC_CRC_ERR;
    sendU16BE(1);  // Length = 1
    sendByte(errorByte);
    sendU32BE(calculateCRC32(&errorByte, 1));
    return;
  }

  // Processa comando
  uint8_t command = payload[0];

  switch (command) {
    case 'A':  // Realtime data (modern protocol)
      {
        // Estrutura: [RC_OK] [offset_byte] [126 log entries]
        uint8_t buffer[1 + 1 + LOG_ENTRIES_COUNT];
        buffer[0] = SERIAL_RC_OK;
        buffer[1] = 0x00;  // Offset byte (compatibilidade Speeduino)
        buildRealtimePacket(&buffer[2]);  // 126 log entries começam no byte 2

        uint16_t responseLength = 1 + 1 + LOG_ENTRIES_COUNT;  // RC_OK + offset + 126 entries = 128
        sendU16BE(responseLength);
        sendBytes(buffer, responseLength);
        sendU32BE(calculateCRC32(buffer, responseLength));
      }
      break;

    case 'C':  // Test comm (modern protocol)
      {
        uint8_t testBuf[2];
        testBuf[0] = SERIAL_RC_OK;
        testBuf[1] = 0xFF;

        sendU16BE(2);  // Length = 2
        sendBytes(testBuf, 2);
        sendU32BE(calculateCRC32(testBuf, 2));
      }
      break;

    case 'f':  // Serial capability details (compatibilidade Speeduino)
      {
        uint8_t tempBuf[6];
        tempBuf[0] = SERIAL_RC_OK;
        tempBuf[1] = 2;  // Serial protocol version
        tempBuf[2] = (BLOCKING_FACTOR >> 8) & 0xFF;  // High byte
        tempBuf[3] = BLOCKING_FACTOR & 0xFF;         // Low byte
        tempBuf[4] = (TABLE_BLOCKING_FACTOR >> 8) & 0xFF;
        tempBuf[5] = TABLE_BLOCKING_FACTOR & 0xFF;

        sendU16BE(6);  // Length = 6 bytes
        sendBytes(tempBuf, 6);
        sendU32BE(calculateCRC32(tempBuf, 6));
      }
      break;

    case 'I':  // Interface version (compatibilidade Speeduino)
      {
        uint8_t tempBuf[32];
        uint8_t len = 0;

        tempBuf[len++] = SERIAL_RC_OK;

        // SEMPRE retorna "speeduino 202402" para compatibilidade
        const char* iface = "speeduino 202402";
        uint8_t ilen = strlen(iface);
        memcpy(&tempBuf[len], iface, ilen);
        len += ilen;

        sendU16BE(len);
        sendBytes(tempBuf, len);
        sendU32BE(calculateCRC32(tempBuf, len));
      }
      break;

    case 'Q':  // Firmware version
      {
        uint8_t tempBuf[32];
        uint8_t len = 0;

        tempBuf[len++] = SERIAL_RC_OK;

        //const char* ver = "slowduino " SLOWDUINO_VERSION;
        const char* ver = "speeduino 202207";
        uint8_t vlen = strlen(ver);
        memcpy(&tempBuf[len], ver, vlen);
        len += vlen;

        sendU16BE(len);
        sendBytes(tempBuf, len);
        sendU32BE(calculateCRC32(tempBuf, len));
      }
      break;

    case 'S':  // Product string
      {
        uint8_t tempBuf[32];
        uint8_t len = 0;

        tempBuf[len++] = SERIAL_RC_OK;

        //const char* prod = "Slowduino " SLOWDUINO_VERSION;
        const char* prod = "Speeduino 2024.02.4";  // Capital S for compatibility
        uint8_t plen = strlen(prod);
        memcpy(&tempBuf[len], prod, plen);
        len += plen;

        sendU16BE(len);
        sendBytes(tempBuf, len);
        sendU32BE(calculateCRC32(tempBuf, len));
      }
      break;

    case 'F':  // Protocol version
      {
        uint8_t tempBuf[4];
        tempBuf[0] = SERIAL_RC_OK;
        tempBuf[1] = '0';
        tempBuf[2] = '0';
        tempBuf[3] = '2';

        sendU16BE(4);
        sendBytes(tempBuf, 4);
        sendU32BE(calculateCRC32(tempBuf, 4));
      }
      break;

    case 'p':  // Read page
      {
        // Formato: 'p' + CAN_ID + page + offset(2) + length(2)
        // payload[0] = 'p'
        // payload[1] = CAN_ID (geralmente 0x00)
        // payload[2] = page number
        // payload[3:5] = offset (little-endian uint16)
        // payload[5:7] = length (little-endian uint16)
        if (payloadLength >= 7) {
          uint8_t page = payload[2];
          uint16_t offset = payload[3] | ((uint16_t)payload[4] << 8);  // Little-endian
          uint16_t length = payload[5] | ((uint16_t)payload[6] << 8);  // Little-endian

          sendPageValues(page, offset, length);
        } else {
          // Payload incompleto
          uint8_t err = SERIAL_RC_UKWN_ERR;
          sendU16BE(1);
          sendByte(err);
          sendU32BE(calculateCRC32(&err, 1));
        }
      }
      break;

    case 'M':  // Write page
      {
        uint8_t page = payload[2];
        uint16_t offset = payload[3] | ((uint16_t)payload[4] << 8);
        uint16_t length = payload[5] | ((uint16_t)payload[6] << 8);
        uint8_t* data = &payload[7];

        uint8_t result = writePageValues(page, offset, length, data);

        // Envia resposta
        sendU16BE(1);  // Length = 1
        sendByte(result);
        sendU32BE(calculateCRC32(&result, 1));
      }
      break;

    case 'd':  // Page CRC32
      {
        // Formato: 'd' + extra_byte + page_num (3 bytes total)
        // payload[0] = 'd'
        // payload[1] = extra byte (sempre 0x00)
        // payload[2] = page number
        if (payloadLength >= 3) {
          uint8_t page = payload[2];  // Speeduino real usa payload[2]
          sendPageCRC32(page);
        } else {
          uint8_t err = SERIAL_RC_UKWN_ERR;
          sendU16BE(1);
          sendByte(err);
          sendU32BE(calculateCRC32(&err, 1));
        }
      }
      break;

    case 'r':  // Output channels (optimized realtime)
      {
        // Formato: 'r' + CAN_ID + Subcmd + Offset(2) + Length(2)
        // payload[0] = 'r'
        // payload[1] = CAN_ID (geralmente 0x00)
        // payload[2] = subcommand (0x30 = output channels)
        // payload[3:5] = offset (little-endian uint16)
        // payload[5:7] = length (little-endian uint16)
        if (payloadLength >= 7) {
          uint8_t subcmd = payload[2];
          uint16_t offset = payload[3] | ((uint16_t)payload[4] << 8);  // Little-endian
          uint16_t length = payload[5] | ((uint16_t)payload[6] << 8);  // Little-endian

          sendOutputChannels(subcmd, offset, length);
        } else {
          uint8_t err = SERIAL_RC_UKWN_ERR;
          sendU16BE(1);
          sendByte(err);
          sendU32BE(calculateCRC32(&err, 1));
        }
      }
      break;

    case 'b':  // Burn EEPROM
    case 'B':
      {
        burnEEPROM();
        // Envia resposta
        uint8_t statusByte = SERIAL_RC_BURN_OK;
        sendU16BE(1);
        sendByte(statusByte);
        sendU32BE(calculateCRC32(&statusByte, 1));
      }
      break;

    default:
      {
        // Comando desconhecido
        uint8_t err = SERIAL_RC_UKWN_ERR;
        sendU16BE(1);
        sendByte(err);
        sendU32BE(calculateCRC32(&err, 1));
      }
      break;
  }
}

// ============================================================================
// FUNÇÕES DE PÁGINA
// ============================================================================

uint16_t getPageSize(uint8_t page) {
  if (page >= PAGE_COUNT) return 0;
  return pgm_read_word(&pageSize[page]);
}

static bool readStructPageByte(const uint8_t* base, uint16_t size, uint16_t offset, uint8_t& value) {
  if (offset >= size) return false;
  value = base[offset];
  return true;
}

static PageWriteStatus writeStructPageByte(uint8_t* base, uint16_t size, uint16_t offset, uint8_t value) {
  if (offset >= size) return PAGE_WRITE_FAIL;
  base[offset] = value;
  return PAGE_WRITE_OK;
}

static bool readStubPageByte(uint8_t page, uint16_t offset, uint8_t& value) {
  uint16_t size = getPageSize(page);
  if (offset >= size) return false;
  value = 0;
  return true;
}

static bool readVeTablePageByte(uint16_t offset, uint8_t& value) {
  if (offset >= SPEEDUINO_TABLE_PAGE_SIZE) return false;

  if (offset < SPEEDUINO_TABLE_CELLS) {
    uint8_t x = offset % SPEEDUINO_TABLE_DIM;
    uint8_t y = offset / SPEEDUINO_TABLE_DIM;
    value = veTable.values[y][x];
    return true;
  }

  if (offset < SPEEDUINO_TABLE_CELLS + SPEEDUINO_TABLE_AXIS_LEN) {
    uint8_t idx = offset - SPEEDUINO_TABLE_CELLS;
    value = encodeRpmBin(veTable.axisX[idx]);
    return true;
  }

  uint8_t idx = offset - (SPEEDUINO_TABLE_CELLS + SPEEDUINO_TABLE_AXIS_LEN);
  value = veTable.axisY[idx];
  return true;
}

static PageWriteStatus writeVeTablePageByte(uint16_t offset, uint8_t value) {
  if (offset >= SPEEDUINO_TABLE_PAGE_SIZE) return PAGE_WRITE_FAIL;

  if (offset < SPEEDUINO_TABLE_CELLS) {
    uint8_t x = offset % SPEEDUINO_TABLE_DIM;
    uint8_t y = offset / SPEEDUINO_TABLE_DIM;
    veTable.values[y][x] = value;
    return PAGE_WRITE_TABLE_CHANGED;
  }

  if (offset < SPEEDUINO_TABLE_CELLS + SPEEDUINO_TABLE_AXIS_LEN) {
    uint8_t idx = offset - SPEEDUINO_TABLE_CELLS;
    veTable.axisX[idx] = decodeRpmBin(value);
    return PAGE_WRITE_TABLE_CHANGED;
  }

  uint8_t idx = offset - (SPEEDUINO_TABLE_CELLS + SPEEDUINO_TABLE_AXIS_LEN);
  veTable.axisY[idx] = value;
  return PAGE_WRITE_TABLE_CHANGED;
}

static bool readIgnTablePageByte(uint16_t offset, uint8_t& value) {
  if (offset >= SPEEDUINO_TABLE_PAGE_SIZE) return false;

  if (offset < SPEEDUINO_TABLE_CELLS) {
    uint8_t x = offset % SPEEDUINO_TABLE_DIM;
    uint8_t y = offset / SPEEDUINO_TABLE_DIM;
    value = encodeIgnitionValue(ignTable.valuesI[y][x]);
    return true;
  }

  if (offset < SPEEDUINO_TABLE_CELLS + SPEEDUINO_TABLE_AXIS_LEN) {
    uint8_t idx = offset - SPEEDUINO_TABLE_CELLS;
    value = encodeRpmBin(ignTable.axisX[idx]);
    return true;
  }

  uint8_t idx = offset - (SPEEDUINO_TABLE_CELLS + SPEEDUINO_TABLE_AXIS_LEN);
  value = ignTable.axisY[idx];
  return true;
}

static PageWriteStatus writeIgnTablePageByte(uint16_t offset, uint8_t value) {
  if (offset >= SPEEDUINO_TABLE_PAGE_SIZE) return PAGE_WRITE_FAIL;

  if (offset < SPEEDUINO_TABLE_CELLS) {
    uint8_t x = offset % SPEEDUINO_TABLE_DIM;
    uint8_t y = offset / SPEEDUINO_TABLE_DIM;
    ignTable.valuesI[y][x] = decodeIgnitionValue(value);
    return PAGE_WRITE_TABLE_CHANGED;
  }

  if (offset < SPEEDUINO_TABLE_CELLS + SPEEDUINO_TABLE_AXIS_LEN) {
    uint8_t idx = offset - SPEEDUINO_TABLE_CELLS;
    ignTable.axisX[idx] = decodeRpmBin(value);
    return PAGE_WRITE_TABLE_CHANGED;
  }

  uint8_t idx = offset - (SPEEDUINO_TABLE_CELLS + SPEEDUINO_TABLE_AXIS_LEN);
  ignTable.axisY[idx] = value;
  return PAGE_WRITE_TABLE_CHANGED;
}

static bool readPageByte(uint8_t page, uint16_t offset, uint8_t& value) {
  switch (page) {
    case 1:
      return readStructPageByte((uint8_t*)&configPage1, sizeof(ConfigPage1), offset, value);
    case 2:
      return readVeTablePageByte(offset, value);
    case 3:
      return readIgnTablePageByte(offset, value);
    case 4:
      return readStructPageByte((uint8_t*)&configPage2, sizeof(ConfigPage2), offset, value);
    default:
      return readStubPageByte(page, offset, value);
  }
}

static PageWriteStatus writePageByte(uint8_t page, uint16_t offset, uint8_t value) {
  switch (page) {
    case 1:
      return writeStructPageByte((uint8_t*)&configPage1, sizeof(ConfigPage1), offset, value);
    case 2:
      return writeVeTablePageByte(offset, value);
    case 3:
      return writeIgnTablePageByte(offset, value);
    case 4:
      return writeStructPageByte((uint8_t*)&configPage2, sizeof(ConfigPage2), offset, value);
    default:
      {
        uint16_t pageSz = getPageSize(page);
        if (pageSz == 0 || offset >= pageSz) {
          return PAGE_WRITE_FAIL;
        }
        return PAGE_WRITE_OK;
      }
  }
}

void sendPageValues(uint8_t page, uint16_t offset, uint16_t length) {
  uint16_t pageSz = getPageSize(page);

  if (pageSz == 0) {
    uint8_t err = SERIAL_RC_RANGE_ERR;
    sendU16BE(1);
    sendByte(err);
    sendU32BE(calculateCRC32(&err, 1));
    return;
  }

  uint16_t available = (offset < pageSz) ? (pageSz - offset) : 0;
  uint16_t actualLength = (length < available) ? length : available;
  uint16_t responseLength = 1 + actualLength;

  sendU16BE(responseLength);

  uint8_t tempBuf[32];
  uint32_t crc = 0xFFFFFFFF;

  // Status byte
  sendByte(SERIAL_RC_OK);
  crc = crc32Update(crc, SERIAL_RC_OK);

  uint16_t remaining = actualLength;
  uint16_t pos = 0;

  while (remaining > 0) {
    uint16_t blockSize = (remaining < sizeof(tempBuf)) ? remaining : sizeof(tempBuf);
    for (uint16_t i = 0; i < blockSize; i++) {
      uint8_t byteValue = 0;
      if (!readPageByte(page, offset + pos + i, byteValue)) {
        byteValue = 0;
      }
      tempBuf[i] = byteValue;
    }

    sendBytes(tempBuf, blockSize);

    for (uint16_t i = 0; i < blockSize; i++) {
      crc = crc32Update(crc, tempBuf[i]);
    }

    pos += blockSize;
    remaining -= blockSize;
  }

  crc = ~crc;
  sendU32BE(crc);
}

uint8_t writePageValues(uint8_t page, uint16_t offset, uint16_t length, const uint8_t* data) {
  uint16_t pageSz = getPageSize(page);

  if (pageSz == 0 || (offset + length) > pageSz) {
    return SERIAL_RC_RANGE_ERR;
  }

  bool tableChanged = false;
  for (uint16_t i = 0; i < length; i++) {
    PageWriteStatus status = writePageByte(page, offset + i, data[i]);
    if (status == PAGE_WRITE_FAIL) {
      return SERIAL_RC_RANGE_ERR;
    }
    if (status == PAGE_WRITE_TABLE_CHANGED) {
      tableChanged = true;
    }
  }

  if (tableChanged) {
    clearTableCaches();
  }

  return SERIAL_RC_OK;
}

void sendPageCRC32(uint8_t page) {
  uint16_t pageSz = getPageSize(page);

  if (pageSz == 0) {
    uint8_t err = SERIAL_RC_RANGE_ERR;
    sendU16BE(1);
    sendByte(err);
    sendU32BE(calculateCRC32(&err, 1));
    return;
  }

  uint32_t crc = 0xFFFFFFFF;
  for (uint16_t i = 0; i < pageSz; i++) {
    uint8_t byteValue = 0;
    if (!readPageByte(page, i, byteValue)) {
      byteValue = 0;
    }
    crc = crc32Update(crc, byteValue);
  }

  uint32_t pageCRC = ~crc;

  uint32_t reversedCRC = ((pageCRC & 0xFF) << 24) |
                         ((pageCRC & 0xFF00) << 8) |
                         ((pageCRC & 0xFF0000) >> 8) |
                         ((pageCRC & 0xFF000000) >> 24);

  uint8_t response[5];
  response[0] = SERIAL_RC_OK;
  response[1] = reversedCRC & 0xFF;
  response[2] = (reversedCRC >> 8) & 0xFF;
  response[3] = (reversedCRC >> 16) & 0xFF;
  response[4] = (reversedCRC >> 24) & 0xFF;

  sendU16BE(5);
  sendBytes(response, 5);
  sendU32BE(calculateCRC32(response, 5));
}

void sendOutputChannels(uint8_t subcmd, uint16_t offset, uint16_t length) {
  if (subcmd == 0x30) {  // Output channels
    // *** CRÍTICO: Speeduino envia offset byte 0x00 ANTES dos dados do log! ***
    // Estrutura: [RC_OK] [offset_byte=0x00] [log_entry_0] [log_entry_1] ... [log_entry_125]
    // Total: 128 bytes (1 RC_OK + 1 offset + 126 log entries)
    //
    // Quando TunerStudio remove o RC_OK, sobram 127 bytes:
    //   data[0] = offset byte (0x00)
    //   data[1] = getTSLogEntry(0) = secl
    //   data[15] = getTSLogEntry(14) = RPM low
    //   data[16] = getTSLogEntry(15) = RPM high

    uint8_t fullBuffer[1 + LOG_ENTRIES_COUNT];  // offset byte + 126 log entries
    fullBuffer[0] = 0x00;  // Offset byte (compatibilidade Speeduino)
    buildRealtimePacket(&fullBuffer[1]);  // 126 log entries começam no índice 1

    // Ajusta offset e length para incluir o offset byte
    // TunerStudio pede offset=0, length=127
    // Devemos retornar: [RC_OK] + fullBuffer[0:127]
    uint16_t fullBufferSize = 1 + LOG_ENTRIES_COUNT;  // 127 bytes total
    if (offset >= fullBufferSize) {
      offset = 0;
      length = 0;
    }
    if (offset + length > fullBufferSize) {
      length = fullBufferSize - offset;
    }

    // Monta resposta: [length] [RC_OK] [dados] [CRC]
    uint16_t responseLength = 1 + length;  // RC_OK + dados
    sendU16BE(responseLength);

    // Envia RC_OK
    sendByte(SERIAL_RC_OK);

    // Envia dados (offset byte + log entries)
    sendBytes(fullBuffer + offset, length);

    // Calcula CRC (RC_OK + dados)
    uint32_t crc = 0xFFFFFFFF;

    // Passo 1: CRC do status byte
    uint8_t statusByte = SERIAL_RC_OK;
    uint8_t index = (crc ^ statusByte) & 0xFF;
    crc = (crc >> 8) ^ pgm_read_dword(&crc32_table[index]);

    // Passo 2: CRC dos dados
    for (uint16_t i = 0; i < length; i++) {
      index = (crc ^ fullBuffer[offset + i]) & 0xFF;
      crc = (crc >> 8) ^ pgm_read_dword(&crc32_table[index]);
    }

    crc = ~crc;
    sendU32BE(crc);
  } else {
    // Subcomando desconhecido
    uint8_t err = SERIAL_RC_UKWN_ERR;
    sendU16BE(1);
    sendByte(err);
    sendU32BE(calculateCRC32(&err, 1));
  }
}

void burnEEPROM() {
  saveAllConfig();
}

// ============================================================================
// REALTIME DATA PACKET (126 bytes de log entries)
// ============================================================================
//
// Speeduino usa getTSLogEntry(n) onde n = 0..125 (126 entries)
// Não inclui o offset byte 0x00 - isso é adicionado pela camada de protocolo
//
void buildRealtimePacket(uint8_t* buffer) {
  // Zera buffer (126 bytes)
  memset(buffer, 0, LOG_ENTRIES_COUNT);

  // Offset 0: secl
  buffer[0] = currentStatus.secl & 0xFF;

  // Offset 1: status1
  buffer[1] = 0;
  if (currentStatus.RPM > 0) buffer[1] |= 0x01;  // Engine running

  // Offset 2: engine
  buffer[2] = currentStatus.engineStatus;

  // Offset 3: syncLoss (sempre 0 se tiver sync)
  buffer[3] = currentStatus.hasSync ? 0 : 1;

  // Offset 4-5: MAP (uint16, little-endian)
  uint16_t map16 = currentStatus.MAP * 10;  // kPa * 10
  buffer[4] = map16 & 0xFF;
  buffer[5] = (map16 >> 8) & 0xFF;

  // Offset 6: IAT (temperatura + 40)
  buffer[6] = currentStatus.IAT + 40;

  // Offset 7: coolant (temperatura + 40)
  buffer[7] = currentStatus.coolant + 40;

  // Offset 8: batCorrection
  buffer[8] = currentStatus.batCorrection;

  // Offset 9: battery10
  buffer[9] = currentStatus.battery10;

  // Offset 10: O2
  buffer[10] = currentStatus.O2;

  // Offset 11: egoCorrection
  buffer[11] = 100;  // Sem correção O2 ainda

  // Offset 12: iatCorrection
  buffer[12] = 100;

  // Offset 13: wueCorrection
  buffer[13] = currentStatus.wueCorrection;

  // Offset 14-15: RPM (uint16, little-endian)
  buffer[14] = currentStatus.RPM & 0xFF;
  buffer[15] = (currentStatus.RPM >> 8) & 0xFF;

  // Offset 24: advance
  buffer[24] = (currentStatus.advance + 40);  // Offset para permitir negativos

  // Offset 25: TPS
  buffer[25] = currentStatus.TPS;

  // Offset 26-27: loopsPerSec (uint16)
  uint16_t loops = 2000;
  buffer[26] = loops & 0xFF;
  buffer[27] = (loops >> 8) & 0xFF;

  // Offset 28-29: freeRAM
  extern int __heap_start, *__brkval;
  int v;
  uint16_t freeRam = (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
  buffer[28] = freeRam & 0xFF;
  buffer[29] = (freeRam >> 8) & 0xFF;

  // Offset 32: spark (bitfield)
  buffer[32] = currentStatus.hasSync ? 0x01 : 0x00;

  // Offset 35: ethanolPct
  buffer[35] = 0;  // Sem flex fuel

  // Offset 41: baro
  buffer[41] = 100;  // 100 kPa (atmosférico)

  // Offset 76-77: PW1 (microsegundos, uint16, little-endian)
  buffer[76] = currentStatus.PW1 & 0xFF;
  buffer[77] = (currentStatus.PW1 >> 8) & 0xFF;

  // Offset 78-79: PW2 (little-endian)
  buffer[78] = currentStatus.PW2 & 0xFF;
  buffer[79] = (currentStatus.PW2 >> 8) & 0xFF;

  // Offset 80-81: PW3 (little-endian)
  buffer[80] = currentStatus.PW3 & 0xFF;
  buffer[81] = (currentStatus.PW3 >> 8) & 0xFF;

  // Offset 82-83: PW4 (0 - não temos 4º canal)
  buffer[82] = 0;
  buffer[83] = 0;

  // Offset 102: VE
  buffer[102] = currentStatus.VE;

  // Offset 104-105: VSS (km/h, uint16)
  buffer[104] = 0;
  buffer[105] = 0;

  // Resto: zeros (já foi feito com memset)
}
