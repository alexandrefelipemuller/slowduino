; Interrupt vector table for the MC68HC908GP32.
;
; SDCC's hc08 backend only auto-generates the RESET vector at 0xFFFE
; (emitted into main.asm's own "CODEIVT (ABS)" area, pointing at its
; startup code) - it does NOT wire up any other vector just because a
; function is declared __interrupt(N). Every other vector below is
; unprogrammed (left as whatever the flash image's default is) unless
; something explicitly places the handler's address there, which is
; what this file does.
;
; Vector address formula (see mc68hc908gp32_sfr.h / the README):
;   address = 0xFFFE - 2*N, where N is the __interrupt(N) argument.
;
; Only vectors with an actual handler defined in this port are filled
; in; anything else stays unprogrammed since we never enable those
; interrupt sources.

	.area CODEIVT (ABS)

	.org 0xFFEC		; N=9: TIM2 overflow (timebase.c)
	.dw _isr_tim2_overflow

	.org 0xFFF4		; N=5: TIM1 channel 1 (scheduler.c)
	.dw _isr_tim1_ch1

	.org 0xFFF6		; N=4: TIM1 channel 0 (scheduler.c)
	.dw _isr_tim1_ch0

	.org 0xFFFA		; N=2: IRQ pin, crank trigger (decoders.c)
	.dw _isr_irq

; End of vectors.s
