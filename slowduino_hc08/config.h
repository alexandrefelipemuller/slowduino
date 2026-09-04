/**
 * @file config.h
 * @brief Constantes compartilhadas - port C/HC08 da branch tiny (config.h)
 *
 * So as constantes efetivamente usadas pelos modulos ja portados. Cresce
 * junto com o port (nao e um port completo do config.h do AVR, que tem
 * bem mais coisa de EEPROM/protocolo ainda nao portada).
 */

#ifndef CONFIG_H
#define CONFIG_H

#define TABLE_SIZE_X 12
#define TABLE_SIZE_Y 12

#define SYNC_TIMEOUT  1000UL
#define INJ_MIN_PW    500
#define INJ_MAX_PW    20000
#define DWELL_MIN     1000
#define DWELL_MAX     8000
#define CORR_MIN      50
#define CORR_MAX      200

#define AE_MODE_TPS   0
#define AE_MODE_MAP   1

#define TRIGGER_MISSING_TOOTH  0
#define TRIGGER_BASIC_DIST     1
#define TRIGGER_EDGE_RISING    0
#define TRIGGER_EDGE_FALLING   1
#define TRIGGER_EDGE_BOTH      2

#endif /* CONFIG_H */
