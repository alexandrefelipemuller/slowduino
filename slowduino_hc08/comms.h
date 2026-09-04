/**
 * @file comms.h
 * @brief Comunicacao serial com TunerStudio - port C/HC08 de comms.h
 *
 * Mesmo protocolo Speeduino (Legacy ASCII + Modern CRC32) da branch tiny,
 * so trocando Serial (HardwareSerial) por sciXxx() (ver serial_hc08.h,
 * polling sobre a SCI do GP32 em vez de ring buffer por interrupcao).
 */

#ifndef COMMS_H
#define COMMS_H

#include <stdint.h>
#include <stdbool.h>

#define SERIAL_RC_OK        0x00
#define SERIAL_RC_BURN_OK   0x04
#define SERIAL_RC_RANGE_ERR 0x80
#define SERIAL_RC_CRC_ERR   0x82
#define SERIAL_RC_UKWN_ERR  0x83

#define LOG_ENTRY_SIZE      127
#define LOG_ENTRIES_COUNT   126
#define PAGE_COUNT          16

#define BLOCKING_FACTOR       121
#define TABLE_BLOCKING_FACTOR 64

extern const uint16_t pageSize[PAGE_COUNT];

void commsInit(void);
void commsProcess(void);

void sendByte(uint8_t data);
void sendBytes(const uint8_t *data, uint16_t length);
void sendU16(uint16_t value);
void sendU16BE(uint16_t value);
void sendU32BE(uint32_t value);
uint32_t calculateCRC32(const uint8_t *data, uint16_t length);

void processLegacyCommand(uint8_t command);
void sendRealtimeData(void);
void sendFirmwareVersion(void);
void sendProductString(void);
void sendProtocolVersion(void);
void sendTestComm(void);

void processModernCommand(void);
void sendPageValues(uint8_t page, uint16_t offset, uint16_t length);
uint8_t writePageValues(uint8_t page, uint16_t offset, uint16_t length, const uint8_t *data);
void sendPageCRC32(uint8_t page);
void sendOutputChannels(uint8_t subcmd, uint16_t offset, uint16_t length);
void burnEEPROM(void);

uint16_t getPageSize(uint8_t page);
void buildRealtimePacket(uint8_t *buffer);

#endif /* COMMS_H */
