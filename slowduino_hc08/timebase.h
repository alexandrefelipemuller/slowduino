/**
 * @file timebase.h
 * @brief Equivalente a micros() do Arduino core, construido sobre TIM2
 *
 * TIM2 roda livre (modo normal, sem reset no compare) contando overflow
 * de 16 bits; a ISR de overflow soma no contador de 32 bits, igual ao
 * padrao timer0_overflow_count do core AVR (mesma tecnica, timer
 * diferente). TIM1 fica dedicado ao scheduler de ignicao (scheduler.h),
 * TIM2 fica livre para isso + futuro PWM da IAC, no mesmo papel que tem
 * hoje no AVR (Timer2 = IAC).
 *
 * PLACEHOLDER DE CLOCK: os calculos de prescaler abaixo assumem clock de
 * barramento de 8MHz (comum em boards MS1 com cristal de 32MHz/PLL x4,
 * ver CGM no datasheet cap. 5) - AJUSTAR conforme o clock real da placa
 * antes de usar em hardware. Isso NAO foi validado contra um board real.
 */

#ifndef TIMEBASE_H
#define TIMEBASE_H

#include <stdint.h>

void timebaseInit(void);

/* Tempo decorrido desde o boot, em microsegundos (32 bits, dá a volta em
 * ~71 minutos - mesmo comportamento do micros() do Arduino core). */
uint32_t micros(void);

#endif /* TIMEBASE_H */
