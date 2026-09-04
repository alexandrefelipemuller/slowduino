/**
 * @file mc68hc908gp32_sfr.h
 * @brief Registradores de hardware (SFR) do Freescale/NXP MC68HC908GP32
 *
 * Fonte: MC68HC908GP32 Data Sheet, Rev. 10, 01/2008 (Freescale/NXP,
 * documento MC68HC908GP32/D). Enderecos conferidos linha a linha contra:
 *   - Figure 2-2 "Control, Status, and Data Registers" (Sheets 1-6,
 *     paginas 31-36) - todos os registradores de $0000-$003E e $FE00-$FFFF.
 *   - Table 2-1 "Vector Addresses" (pagina 37) - vetores de interrupcao.
 *   - Figure 2-1 "Memory Map" (pagina 30) - confirma RAM = $0040-$023F
 *     (512 bytes exatos - o mesmo teto que a branch tiny do Slowduino
 *     persegue no ATmega328p).
 *
 * NAO baseado em memoria/suposicao: o datasheet foi buscado e lido
 * diretamente de nxp.com antes de escrever este arquivo, especificamente
 * para evitar endereco errado silencioso (o tipo de bug que nao aparece
 * em tempo de compilacao, so em hardware real).
 *
 * Estilo: usa o padrao "#define REG (*(volatile uint8_t*)ADDR)" testado
 * de verdade com SDCC -mhc08 (compilado e linkado com sucesso nesta
 * sessao), em vez do truque de bitfield-via-struct-cast que o header
 * mc68hc908gp32.h do proprio pacote SDCC usa - aquele estilo depende de
 * uma suposicao sobre ordem de bits em bitfields que NAO foi verificada
 * aqui. As posicoes de bit abaixo sao numeros simples (0-7), pensados
 * para uso com as macros BIT_SET/BIT_CLEAR/BIT_CHECK ja existentes em
 * globals.h - mesma convencao do projeto no AVR.
 *
 * NUMERACAO DE INTERRUPCAO DO SDCC (__interrupt(N)) - RESOLVIDO:
 * Verificado empiricamente compilando ISRs com N=0,1,2,3,16,17 e inspecionando
 * o vetor gerado no .asm. Formula confirmada: endereco_do_vetor = 0xFFFE - 2*N.
 * N=0 e reservado (colide com reset, tratado pelo startup, nao usar em ISR
 * de usuario). Tabela completa (endereco vem de Table 2-1 do datasheet,
 * N vem da formula acima - ambos conferidos):
 *   N=1  -> $FFFC SWI          N=7  -> $FFF0 TIM2 canal 0
 *   N=2  -> $FFFA IRQ          N=8  -> $FFEE TIM2 canal 1
 *   N=3  -> $FFF8 PLL          N=9  -> $FFEC TIM2 overflow
 *   N=4  -> $FFF6 TIM1 canal 0 N=10 -> $FFEA SPI recepcao
 *   N=5  -> $FFF4 TIM1 canal 1 N=11 -> $FFE8 SPI transmissao
 *   N=6  -> $FFF2 TIM1 overflow N=12 -> $FFE6 SCI erro
 *   N=13 -> $FFE4 SCI recepcao  N=15 -> $FFE0 teclado
 *   N=14 -> $FFE2 SCI transmissao N=16 -> $FFDE ADC   N=17 -> $FFDC timebase
 *
 * PENDENTE DE VALIDACAO (nao coberto por este header):
 *   - CONFIG1/CONFIG2 sao registradores Flash one-time-writable (setados
 *     uma unica vez, tipicamente no boot) - os bits estao documentados
 *     abaixo mas o codigo de inicializacao precisa ser escrito com
 *     cuidado (escrita dupla ou fora de ordem pode ser ignorada pelo
 *     hardware).
 */

#ifndef MC68HC908GP32_SFR_H
#define MC68HC908GP32_SFR_H

#include <stdint.h>

/* ==========================================================================
 * PAGINA ZERO - I/O REGISTERS ($0000-$003F)
 * Fonte: Figure 2-2, Sheets 1-4 (paginas 31-34)
 * ========================================================================== */

/* --- Portas digitais e direcao ($0000-$000F) --- */
#define PTA     (*(volatile uint8_t *)0x0000)  /* Port A Data Register */
#define PTB     (*(volatile uint8_t *)0x0001)  /* Port B Data Register */
#define PTC     (*(volatile uint8_t *)0x0002)  /* Port C Data Register */
#define PTD     (*(volatile uint8_t *)0x0003)  /* Port D Data Register */
#define DDRA    (*(volatile uint8_t *)0x0004)  /* Data Direction Register A */
#define DDRB    (*(volatile uint8_t *)0x0005)  /* Data Direction Register B */
#define DDRC    (*(volatile uint8_t *)0x0006)  /* Data Direction Register C */
#define DDRD    (*(volatile uint8_t *)0x0007)  /* Data Direction Register D */
#define PTE     (*(volatile uint8_t *)0x0008)  /* Port E Data Register (so PTE0/PTE1 existem) */
/* $0009-$000B: unimplemented (nao acessar) */
#define DDRE    (*(volatile uint8_t *)0x000C)  /* Data Direction Register E */
#define PTAPUE  (*(volatile uint8_t *)0x000D)  /* Port A Input Pullup Enable */
#define PTCPUE  (*(volatile uint8_t *)0x000E)  /* Port C Input Pullup Enable (bit7 nao existe) */
#define PTDPUE  (*(volatile uint8_t *)0x000F)  /* Port D Input Pullup Enable */

/* --- SPI ($0010-$0012) --- */
#define SPCR    (*(volatile uint8_t *)0x0010)  /* SPI Control Register */
#define SPCR_SPRIE   7
#define SPCR_SPMSTR  5
#define SPCR_CPOL    4
#define SPCR_CPHA    3
#define SPCR_SPWOM   2
#define SPCR_SPE     1
#define SPCR_SPTIE   0

#define SPSCR   (*(volatile uint8_t *)0x0011)  /* SPI Status and Control Register */
#define SPSCR_SPRF   7
#define SPSCR_ERRIE  6
#define SPSCR_OVRF   5
#define SPSCR_MODF   4
#define SPSCR_SPTE   3
#define SPSCR_MODFEN 2
#define SPSCR_SPR1   1
#define SPSCR_SPR0   0

#define SPDR    (*(volatile uint8_t *)0x0012)  /* SPI Data Register */

/* --- SCI ($0013-$0019) - usada p/ o protocolo Speeduino/TunerStudio --- */
#define SCC1    (*(volatile uint8_t *)0x0013)  /* SCI Control Register 1 */
#define SCC1_LOOPS   7
#define SCC1_ENSCI   6
#define SCC1_TXINV   5
#define SCC1_M       4
#define SCC1_WAKE    3
#define SCC1_ILTY    2
#define SCC1_PEN     1
#define SCC1_PTY     0

#define SCC2    (*(volatile uint8_t *)0x0014)  /* SCI Control Register 2 */
#define SCC2_SCTIE   7
#define SCC2_TCIE    6
#define SCC2_SCRIE   5
#define SCC2_ILIE    4
#define SCC2_TE      3
#define SCC2_RE      2
#define SCC2_RWU     1
#define SCC2_SBK     0

#define SCC3    (*(volatile uint8_t *)0x0015)  /* SCI Control Register 3 */
#define SCC3_R8      7
#define SCC3_ORIE    3
#define SCC3_NEIE    2
#define SCC3_FEIE    1
#define SCC3_PEIE    0

#define SCS1    (*(volatile uint8_t *)0x0016)  /* SCI Status Register 1 */
#define SCS1_SCTE    7  /* transmit data register empty */
#define SCS1_TC      6  /* transmit complete */
#define SCS1_SCRF    5  /* receive data register full */
#define SCS1_IDLE    4
#define SCS1_OR      3  /* overrun */
#define SCS1_NF      2  /* noise flag */
#define SCS1_FE      1  /* framing error */
#define SCS1_PE      0  /* parity error */

#define SCS2    (*(volatile uint8_t *)0x0017)  /* SCI Status Register 2 */
#define SCS2_BKF     1
#define SCS2_RPF     0

#define SCDR    (*(volatile uint8_t *)0x0018)  /* SCI Data Register */

#define SCBR    (*(volatile uint8_t *)0x0019)  /* SCI Baud Rate Register */
#define SCBR_SCP1    5
#define SCBR_SCP0    4
#define SCBR_SCR2    2
#define SCBR_SCR1    1
#define SCBR_SCR0    0

/* --- Keyboard interrupt ($001A-$001B) --- */
#define INTKBSCR   (*(volatile uint8_t *)0x001A)
#define INTKBSCR_KEYF    3
#define INTKBSCR_ACKK    2
#define INTKBSCR_IMASKK  1
#define INTKBSCR_MODEK   0

#define INTKBIER   (*(volatile uint8_t *)0x001B)  /* bits KBIE7..KBIE0 = bit N */

/* --- Time Base Module ($001C) --- */
#define TBCR    (*(volatile uint8_t *)0x001C)
#define TBCR_TBIF    7
#define TBCR_TBR2    6
#define TBCR_TBR1    5
#define TBCR_TBR0    4
#define TBCR_TACK    3
#define TBCR_TBIE    2
#define TBCR_TBON    1

/* --- IRQ status/control ($001D) --- */
#define INTSCR  (*(volatile uint8_t *)0x001D)
#define INTSCR_IRQF   3
#define INTSCR_ACK    2
#define INTSCR_IMASK  1
#define INTSCR_MODE   0

/* --- Configuracao ($001E-$001F) - Flash one-time-writable --- */
#define CONFIG2 (*(volatile uint8_t *)0x001E)
#define CONFIG2_OSCSTOPENB  1
#define CONFIG2_SCIBDSRC    0

#define CONFIG1 (*(volatile uint8_t *)0x001F)
#define CONFIG1_COPRS    7
#define CONFIG1_LVISTOP  6
#define CONFIG1_LVIRSTD  5
#define CONFIG1_LVIPWRD  4
#define CONFIG1_LVI5OR3  3
#define CONFIG1_SSREC    2
#define CONFIG1_STOP     1
#define CONFIG1_COPD     0

/* --- TIM1 ($0020-$002A) - equivalente ao Timer1 usado no scheduler AVR ---
 * O GP32 tem DOIS timers de 16 bits independentes (TIM1 e TIM2), cada um
 * com 2 canais de compare/capture - encaixa melhor no scheduler atual do
 * que o AVR (que tem só 1 Timer1 de 16 bits com Compare A/B). No AVR,
 * canal 1+3 dividem OCR1A; aqui cada canal de ignicao poderia ganhar seu
 * proprio timer inteiro (TIM1 = ignicao 1, TIM2 = ignicao 2), por exemplo.
 */
#define T1SC    (*(volatile uint8_t *)0x0020)  /* TIM1 Status and Control */
#define T1SC_TOF     7
#define T1SC_TOIE    6
#define T1SC_TSTOP   5
#define T1SC_TRST    4
#define T1SC_PS2     2
#define T1SC_PS1     1
#define T1SC_PS0     0

#define T1CNTH  (*(volatile uint8_t *)0x0021)  /* TIM1 Counter High */
#define T1CNTL  (*(volatile uint8_t *)0x0022)  /* TIM1 Counter Low */
#define T1MODH  (*(volatile uint8_t *)0x0023)  /* TIM1 Counter Modulo High */
#define T1MODL  (*(volatile uint8_t *)0x0024)  /* TIM1 Counter Modulo Low */

#define T1SC0   (*(volatile uint8_t *)0x0025)  /* TIM1 Channel 0 Status/Control */
#define T1SC1   (*(volatile uint8_t *)0x0028)  /* TIM1 Channel 1 Status/Control */
/* Bits de T1SCx (ambos os canais usam o mesmo layout): */
#define TxSCx_CHxF    7
#define TxSCx_CHxIE   6
#define TxSCx_MSxB    5  /* so existe no canal 0 (MS0B); canal 1 nao tem MS1B */
#define TxSCx_MSxA    4
#define TxSCx_ELSxB   3
#define TxSCx_ELSxA   2
#define TxSCx_TOVx    1
#define TxSCx_CHxMAX  0

#define T1CH0H  (*(volatile uint16_t *)0x0026) /* usar como uint16_t direto (H:L contiguos) */
#define T1CH1H  (*(volatile uint16_t *)0x0029)

/* --- TIM2 ($002B-$0035) - layout identico ao TIM1 --- */
#define T2SC    (*(volatile uint8_t *)0x002B)
#define T2CNTH  (*(volatile uint8_t *)0x002C)
#define T2CNTL  (*(volatile uint8_t *)0x002D)
#define T2MODH  (*(volatile uint8_t *)0x002E)
#define T2MODL  (*(volatile uint8_t *)0x002F)
#define T2SC0   (*(volatile uint8_t *)0x0030)
#define T2CH0H  (*(volatile uint16_t *)0x0031)
#define T2SC1   (*(volatile uint8_t *)0x0033)
#define T2CH1H  (*(volatile uint16_t *)0x0034)
/* Bits de T2SC identicos aos de T1SC (TOF/TOIE/TSTOP/TRST/PS2..PS0) */
#define T2SC_TOF     7
#define T2SC_TOIE    6
#define T2SC_TSTOP   5
#define T2SC_TRST    4
#define T2SC_PS2     2
#define T2SC_PS1     1
#define T2SC_PS0     0
/* Bits de T2SCx identicos aos de TxSCx acima */

/* --- PLL / gerador de clock ($0036-$003B) --- */
#define PCTL    (*(volatile uint8_t *)0x0036)  /* PLL Control Register */
#define PCTL_PLLIE   7
#define PCTL_PLLF    6
#define PCTL_PLLON   5
#define PCTL_BCS     4
#define PCTL_PRE1    3
#define PCTL_PRE0    2
#define PCTL_VPR1    1
#define PCTL_VPR0    0

#define PBWC    (*(volatile uint8_t *)0x0037)  /* PLL Bandwidth Control */
#define PBWC_AUTO    7
#define PBWC_LOCK    6
#define PBWC_ACQ     5

#define PMSH    (*(volatile uint8_t *)0x0038)  /* PLL Multiplier Select High (bits 3-0) */
#define PMSL    (*(volatile uint8_t *)0x0039)  /* PLL Multiplier Select Low */
#define PMRS    (*(volatile uint8_t *)0x003A)  /* PLL VCO Range Select */
#define PMDS    (*(volatile uint8_t *)0x003B)  /* PLL Reference Divider Select (bits 3-0) */

/* --- ADC ($003C-$003E) --- */
#define ADSCR   (*(volatile uint8_t *)0x003C)  /* ADC Status and Control */
#define ADSCR_COCO   7  /* conversion complete (somente leitura) */
#define ADSCR_AIEN   6  /* interrupt enable */
#define ADSCR_ADCO   5  /* continuous conversion */
#define ADSCR_ADCH4  4  /* ADCH4..ADCH0: canal selecionado (0-31, 5 bits) */
#define ADSCR_ADCH3  3
#define ADSCR_ADCH2  2
#define ADSCR_ADCH1  1
#define ADSCR_ADCH0  0

#define ADR     (*(volatile uint8_t *)0x003D)  /* ADC Data Register (8 bits, nao 10!) */

#define ADCLK   (*(volatile uint8_t *)0x003E)  /* ADC Clock */
#define ADCLK_ADIV2   7
#define ADCLK_ADIV1   6
#define ADCLK_ADIV0   5
#define ADCLK_ADICLK  4

/* ==========================================================================
 * REGISTRADORES ESTENDIDOS ($FE00-$FFFF)
 * Fonte: Figure 2-2, Sheets 5-6 (paginas 35-36)
 * ========================================================================== */

#define SBSR    (*(volatile uint8_t *)0xFE00)  /* SIM Break Status Register */
#define SBSR_SBSW    1

#define SRSR    (*(volatile uint8_t *)0xFE01)  /* SIM Reset Status Register (causa do ultimo reset) */
#define SRSR_POR     7
#define SRSR_PIN     6
#define SRSR_COP     5
#define SRSR_ILOP    4
#define SRSR_ILAD    3
#define SRSR_MODRST  2
#define SRSR_LVI     1

/* $FE02 SUBAR: reservado (nao usar) */

#define SBFCR   (*(volatile uint8_t *)0xFE03)  /* SIM Break Flag Control */
#define SBFCR_BCFE   7

#define INT1    (*(volatile uint8_t *)0xFE04)  /* Interrupt Status Register 1 */
#define INT2    (*(volatile uint8_t *)0xFE05)  /* Interrupt Status Register 2 */
#define INT3    (*(volatile uint8_t *)0xFE06)  /* Interrupt Status Register 3 */
/* $FE07: reservado no datasheet publico - NAO usar (alguns headers de
 * terceiros chamam isso de "FLCTR"/teste de fabrica; o datasheet oficial
 * MC68HC908GP32/D Rev.10 marca como Reserved) */

#define FLCR    (*(volatile uint8_t *)0xFE08)  /* FLASH Control Register */
#define FLCR_HVEN    3
#define FLCR_MASS    2
#define FLCR_ERASE   1
#define FLCR_PGM     0

#define BRKH    (*(volatile uint8_t *)0xFE09)  /* Break Address High */
#define BRKL    (*(volatile uint8_t *)0xFE0A)  /* Break Address Low */

#define BRKSCR  (*(volatile uint8_t *)0xFE0B)  /* Break Status/Control */
#define BRKSCR_BRKE  7
#define BRKSCR_BRKA  6

#define LVISR   (*(volatile uint8_t *)0xFE0C)  /* LVI Status Register */
#define LVISR_LVIOUT 7

#define FLBPR   (*(volatile uint8_t *)0xFF7E)  /* FLASH Block Protect Register (nao-volatil) */

#define COPCTL  (*(volatile uint8_t *)0xFFFF)  /* COP Control (write-only, qq escrita reseta o watchdog) */

/* ==========================================================================
 * VETORES DE INTERRUPCAO (Table 2-1, pagina 37) - enderecos de hardware.
 *
 * Cada vetor ocupa 2 bytes (high, low) terminando no endereco listado + 1.
 * Estes sao os enderecos REAIS onde o hardware busca o ponteiro da ISR
 * apos reset ou interrupcao - nao confundir com o parametro N de
 * "__interrupt(N)" do SDCC, que e uma convencao do COMPILADOR ainda nao
 * verificada (ver aviso no topo do arquivo).
 * ========================================================================== */
#define VECTOR_TIMEBASE_HI   0xFFDC
#define VECTOR_ADC_HI        0xFFDE
#define VECTOR_KEYBOARD_HI   0xFFE0
#define VECTOR_SCI_TX_HI     0xFFE2
#define VECTOR_SCI_RX_HI     0xFFE4
#define VECTOR_SCI_ERR_HI    0xFFE6
#define VECTOR_SPI_TX_HI     0xFFE8
#define VECTOR_SPI_RX_HI     0xFFEA
#define VECTOR_TIM2_OV_HI    0xFFEC
#define VECTOR_TIM2_CH1_HI   0xFFEE
#define VECTOR_TIM2_CH0_HI   0xFFF0
#define VECTOR_TIM1_OV_HI    0xFFF2
#define VECTOR_TIM1_CH1_HI   0xFFF4
#define VECTOR_TIM1_CH0_HI   0xFFF6
#define VECTOR_PLL_HI        0xFFF8
#define VECTOR_IRQ_HI        0xFFFA
#define VECTOR_SWI_HI        0xFFFC
#define VECTOR_RESET_HI      0xFFFE

#endif /* MC68HC908GP32_SFR_H */
