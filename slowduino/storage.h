/**
 * @file storage.h
 * @brief Gerenciamento de persistência na EEPROM
 *
 * Funções para salvar e carregar configurações e tabelas
 */

#ifndef STORAGE_H
#define STORAGE_H

#include <Arduino.h>
#include "globals.h"
#include "config.h"

// ============================================================================
// FUNÇÕES PÚBLICAS
// ============================================================================

/**
 * @brief Inicializa sistema de storage
 *
 * Verifica versão da EEPROM e carrega configurações.
 * Se versão inválida ou primeira inicialização, carrega valores padrão.
 */
void storageInit();

/**
 * @brief Carrega todas as configurações da EEPROM
 *
 * Carrega tabelas VE/Ignição e config pages para RAM
 */
void loadAllConfig();

/**
 * @brief Carrega apenas config pages (rápido)
 */
void loadConfigPages();

/**
 * @brief Salva todas as configurações na EEPROM
 *
 * Salva tabelas VE/Ignição e config pages.
 * ATENÇÃO: operação demorada (~100ms)
 */
void saveAllConfig();

/**
 * @brief Salva apenas config pages (mais rápido)
 */
void saveConfigPages();

/**
 * @brief Carrega valores padrão (primeiro boot ou reset)
 *
 * Preenche todas as estruturas com valores seguros de fábrica
 */
void loadDefaults();

/**
 * @brief Reseta EEPROM para valores padrão
 *
 * Apaga tudo e recarrega defaults
 */
void resetEEPROM();

// ============================================================================
// FUNÇÕES AUXILIARES DE LEITURA/ESCRITA
// ============================================================================

/**
 * @brief Lê um byte da EEPROM
 */
uint8_t eepromReadByte(uint16_t address);

/**
 * @brief Escreve um byte na EEPROM (apenas se diferente)
 *
 * @return true se escreveu, false se valor já era igual
 */
bool eepromWriteByte(uint16_t address, uint8_t value);

/**
 * @brief Lê um uint16_t da EEPROM (little-endian)
 */
uint16_t eepromReadU16(uint16_t address);

/**
 * @brief Escreve um uint16_t na EEPROM
 */
void eepromWriteU16(uint16_t address, uint16_t value);

/**
 * @brief Lê um int8_t da EEPROM
 */
int8_t eepromReadI8(uint16_t address);

/**
 * @brief Escreve um int8_t na EEPROM
 */
void eepromWriteI8(uint16_t address, int8_t value);

#endif // STORAGE_H
