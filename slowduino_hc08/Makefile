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

all: $(TARGET).ihx

$(TARGET).ihx: $(SRCS:%=%.rel)
	$(CC) $(CFLAGS) $^ -o $@

%.rel: %.c
	$(CC) $(CFLAGS) -S $<
	$(AS) -plosgffw $@ $*.asm

clean:
	rm -f *.rel *.asm *.ihx *.map *.sym *.lst *.rst *.lk *.adb
