# Build do port Slowduino-HC08 (MC68HC908GP32) via SDCC.
#
# --stack-auto e OBRIGATORIO aqui, nao opcional: sem ele, o SDCC aloca
# parametros e variaveis locais de CADA funcao como armazenamento fixo
# permanente (nao pilha real) por padrao no backend hc08. Medido nesta
# sessao: 501B de RAM sem --stack-auto vs 303B com --stack-auto, para o
# mesmo codigo (globals+timebase+scheduler+decoders+main) - custo de
# ~793B extras de flash pelo push/pop de frame real. Sem essa flag, cada
# arquivo novo que a gente portar (fuel, comms) vai inflar RAM de forma
# desproporcional ao tamanho real dos dados.
#
# Workaround manual do bug de empacotamento do sdcc 4.2.0 (Ubuntu): a
# chamada automatica do assembler quebra ("sdas6808 ll -plosgffw ..." -
# "ll" espurio antes das flags). Por isso o build roda em 3 passos.

CC      = sdcc
AS      = sdas6808
MCU     = -mhc08
CFLAGS  = $(MCU) --std-c99 --stack-auto -Wall
SRCS    = globals timebase scheduler decoders storage tables fuel ignition serial_hc08 comms main
TARGET  = slowduino_hc08

.PHONY: all clean

all: $(TARGET).s19

# vectors.rel must come after main.rel: SDCC only auto-generates the
# RESET vector (via main.asm's own "CODEIVT (ABS)" area), never the
# other interrupt vectors just because a function is __interrupt(N) -
# see vectors.s for why and which ones.
#
# Output as .s19, not .ihx: SDCC's hc08 backend always emits Motorola
# S-record regardless of the output filename's extension, but ucsim
# picks its loader purely from that extension (content is never
# sniffed) - naming it .ihx made it get fed through the Intel HEX
# parser instead, silently producing garbage (including a wrong reset
# vector, seen as a wild jump into unlinked memory almost immediately).
$(TARGET).s19: $(SRCS:%=%.rel) vectors.rel
	$(CC) $(CFLAGS) $^ -o $@

%.rel: %.c
	$(CC) $(CFLAGS) -S $<
	$(AS) -plosgffw $@ $*.asm

vectors.rel: vectors.s
	$(AS) -plosgffw $@ $<

clean:
	rm -f *.rel *.asm *.ihx *.map *.sym *.lst *.rst *.lk *.adb
