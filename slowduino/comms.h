/**
 * @file comms.h
 * @brief Comunicação serial com TunerStudio
 *
 * Implementa protocolo Speeduino compatível com TunerStudio
 * Suporta Legacy Protocol (ASCII) e Modern Protocol (CRC32)
 */

#ifndef COMMS_H
#define COMMS_H

#include <Arduino.h>
#include "globals.h"
#include "config.h"

// ============================================================================
// RESPONSE CODES
// ============================================================================
#define SERIAL_RC_OK        0x00  // Sucesso
#define SERIAL_RC_BURN_OK   0x04  // EEPROM burn OK
#define SERIAL_RC_RANGE_ERR 0x80  // Erro de range/offset
#define SERIAL_RC_CRC_ERR   0x82  // Erro de CRC
#define SERIAL_RC_UKWN_ERR  0x83  // Comando desconhecido

// ============================================================================
// TAMANHOS
// ============================================================================
#define LOG_ENTRY_SIZE      127   // Tamanho TOTAL do pacote (offset byte + 126 log entries)
#define LOG_ENTRIES_COUNT   126   // Quantidade de log entries (getTSLogEntry)
#define SERIAL_BUFFER_SIZE  64    // Buffer de recepção
#define PAGE_COUNT          16    // Speeduino usa páginas 0-15

// ============================================================================
// SERIAL CAPABILITY (compatibilidade Speeduino)
// ============================================================================
#define BLOCKING_FACTOR       121   // Para AVR (ATmega328p)
#define TABLE_BLOCKING_FACTOR 64    // Para AVR

// ============================================================================
// ESTRUTURA DE PÁGINAS
// ============================================================================
extern const uint16_t pageSize[PAGE_COUNT];

// ============================================================================
// FUNÇÕES PÚBLICAS
// ============================================================================

/**
 * @brief Inicializa sistema de comunicação
 */
void commsInit();

/**
 * @brief Processa comunicação serial
 *
 * Deve ser chamada no loop principal.
 * Detecta automaticamente protocolo Legacy ou Modern.
 */
void commsProcess();

/**
 * @brief Envia byte único
 */
inline void sendByte(uint8_t data) {
  Serial.write(data);
}

/**
 * @brief Envia array de bytes
 */
inline void sendBytes(const uint8_t* data, uint16_t length) {
  Serial.write(data, length);
}

/**
 * @brief Envia uint16_t em little-endian
 */
void sendU16(uint16_t value);

/**
 * @brief Envia uint16_t em big-endian (para length header Modern Protocol)
 */
void sendU16BE(uint16_t value);

/**
 * @brief Envia uint32_t em big-endian (para CRC)
 */
void sendU32BE(uint32_t value);

/**
 * @brief Calcula CRC32 de um buffer
 *
 * Usa algoritmo padrão CRC32 (mesmo que FastCRC32 da Speeduino)
 * @param data Ponteiro para dados
 * @param length Tamanho dos dados
 * @return CRC32 calculado
 */
uint32_t calculateCRC32(const uint8_t* data, uint16_t length);

// ============================================================================
// COMANDOS LEGACY PROTOCOL
// ============================================================================

/**
 * @brief Processa comando legacy (ASCII single-byte)
 */
void processLegacyCommand(uint8_t command);

/**
 * @brief Envia realtime data (127 bytes)
 *
 * Comando 'A' - envia struct de dados ao vivo
 */
void sendRealtimeData();

/**
 * @brief Envia serial capability details (compatibilidade Speeduino)
 *
 * Comando 'f' - retorna protocol version, blocking factors
 */
void sendSerialCapability();

/**
 * @brief Envia interface version (compatibilidade Speeduino)
 *
 * Comando 'I' - retorna "speeduino 202402" para TunerStudio aceitar
 */
void sendInterfaceVersion();

/**
 * @brief Envia versão do firmware
 *
 * Comando 'Q'
 */
void sendFirmwareVersion();

/**
 * @brief Envia product string
 *
 * Comando 'S'
 */
void sendProductString();

/**
 * @brief Envia versão do protocolo
 *
 * Comando 'F'
 */
void sendProtocolVersion();

/**
 * @brief Test communications
 *
 * Comando 'C'
 */
void sendTestComm();

// ============================================================================
// COMANDOS MODERN PROTOCOL
// ============================================================================

/**
 * @brief Processa comando modern (CRC32-based)
 */
void processModernCommand();

/**
 * @brief Lê página de configuração
 *
 * Comando 'p' - lê valores de uma página
 * @param page Número da página
 * @param offset Offset inicial
 * @param length Quantidade de bytes
 */
void sendPageValues(uint8_t page, uint16_t offset, uint16_t length);

/**
 * @brief Escreve página de configuração
 *
 * Comando 'M' - escreve valores em uma página
 * @param page Número da página
 * @param offset Offset inicial
 * @param length Quantidade de bytes
 * @param data Ponteiro para novos dados
 */
uint8_t writePageValues(uint8_t page, uint16_t offset, uint16_t length, const uint8_t* data);

/**
 * @brief Envia CRC32 de uma página
 *
 * Comando 'd'
 * @param page Número da página
 */
void sendPageCRC32(uint8_t page);

/**
 * @brief Envia output channels (realtime optimized)
 *
 * Comando 'r' - envia dados ao vivo a partir de offset
 * @param subcmd Subcomando (0x30 = output channels)
 * @param offset Offset inicial
 * @param length Quantidade de bytes
 */
void sendOutputChannels(uint8_t subcmd, uint16_t offset, uint16_t length);

/**
 * @brief Burn EEPROM
 *
 * Comando 'b' ou 'B'
 */
void burnEEPROM();

// ============================================================================
// HELPER FUNCTIONS
// ============================================================================

/**
 * @brief Obtém ponteiro para página de configuração
 */
uint8_t* getPagePointer(uint8_t page);

/**
 * @brief Obtém tamanho de uma página
 */
uint16_t getPageSize(uint8_t page);

/**
 * @brief Monta pacote de realtime data (126 bytes de log entries)
 *
 * Preenche buffer com dados do currentStatus.
 * NÃO inclui o offset byte inicial (0x00) - isso é adicionado pela camada de protocolo.
 *
 * @param buffer Buffer de saída (mínimo 126 bytes)
 */
void buildRealtimePacket(uint8_t* buffer);

#endif // COMMS_H
