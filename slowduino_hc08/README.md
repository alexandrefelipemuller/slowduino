# Slowduino - port HC08 (MC68HC908GP32)

Port experimental do Slowduino para o núcleo original da MegaSquirt MS1
(Freescale/Motorola MC68HC908GP32), compilado com SDCC (`-mhc08`), em C puro
(SDCC não compila C++).

## ACHADO CRITICO: `--stack-auto` é obrigatório

Sem essa flag, o SDCC aloca parâmetros e variáveis locais de CADA função
como armazenamento fixo permanente (não pilha real) por padrão no backend
hc08 - só 11 bytes conseguem ser reaproveitados via overlay (`OSEG`).
Medido nesta sessão, mesmo código (globals+timebase+scheduler+decoders+
main): **501 bytes de RAM sem `--stack-auto` vs 303 bytes com**. Custo:
~793 bytes a mais de Flash (frame de pilha real por chamada). Essa é
exatamente a "desvantagem do compilador no meio do caminho" antecipada no
início desta investigação - agora com número real. O `Makefile` deste
diretório já usa `--stack-auto` como padrão.

## Estado atual - PORT COMPLETO DA LÓGICA DE ENGINE MANAGEMENT

Todos os módulos de cálculo/decodificação/protocolo da branch `tiny` estão
portados e compilando/linkando de ponta a ponta:

- `mc68hc908gp32_sfr.h` - registradores de hardware, conferidos linha a
  linha contra o datasheet oficial (NXP, Rev. 10) **e** contra o
  `Gp32.equ` da firmware MS1 original
  (`/home/alexandre/Downloads/029y4a/src/Gp32.equ`) - ambas as fontes
  batem exatamente. Numeração de interrupção `__interrupt(N)` verificada
  empiricamente (fórmula: `endereço = 0xFFFE - 2*N`).
- `config.h` - constantes compartilhadas (cresce junto com o port).
- `globals.h`/`globals.c` - structs `Statuses`/`ConfigPage1`/`ConfigPage2`.
- `timebase.h`/`timebase.c` - `micros()` próprio sobre overflow do TIM2.
- `scheduler.h`/`scheduler.c` - `IgnitionSchedule` (TIM1 canal 0/1, sem
  simplificar para "um timer por canal" - reversibilidade com o AVR
  preservada) + `InjectorPollingState`/polling de injeção.
- `decoders.h`/`decoders.c` - trigger Missing Tooth + Basic Distributor,
  `calculateRPM`, `checkSyncLoss`, agendamento direto na ISR. O pino `IRQ`
  dedicado do GP32 só detecta borda de **descida** - RISING/CHANGE não são
  suportados nesse pino (ver ressalva grande no arquivo).
- `storage.h`/`storage.c` - **PLACEHOLDER, não é storage real**. O GP32
  não tem EEPROM (só Flash, apagada em páginas de 128 bytes via `FLCR`).
  Retorna valores fixos só para não travar `tables.c`/`comms.c` até um
  design real de persistência ser decidido.
- `tables.h`/`tables.c` - interpolação bilinear (sem cache), lê célula via
  `storage.h`.
- `fuel.h`/`fuel.c` - `calculateInjection()`, WUE/ASE/AE/CLT/battery. 2
  avisos de sign-compare (`fuel.c:84,93`, `coolant` `int8_t` vs `wueBins[]`
  `uint8_t`) - **pré-existentes no AVR original**, não corrigidos aqui.
- `ignition.h`/`ignition.c` - avanço (tabela + correções CLT/idle/rev
  limiter) e dwell.
- `serial_hc08.h`/`serial_hc08.c` - camada de I/O sobre a SCI (polling,
  não interrupção - ver ressalva no arquivo), equivalente ao
  `HardwareSerial` do Arduino core.
- `comms.h`/`comms.c` - protocolo Speeduino completo (Legacy ASCII +
  Modern CRC32), idêntico em lógica ao AVR. CRC32 lido direto da tabela em
  Flash (sem `pgm_read_dword` - HC08 tem memória unificada, não precisa da
  distinção Harvard do AVR). `getFreeRam()` é placeholder (retorna 0) -
  não existe equivalente verificado a `__heap_start`/`__brkval` pra
  SDCC/HC08 ainda.
- `main.c` - boot completo: trigger → scheduler → fuel → ignition →
  tables → comms, com a mesma proteção de escrita atômica
  (`noInterrupts()`/`interrupts()`) que o AVR usa entre o cálculo de
  PW/advance/dwell no loop e a leitura desses campos dentro da ISR.

**RAM: 451 bytes** (todos os módulos acima, exceto storage real). Ainda
dentro dos 512 bytes do MS1 original, com ~61 bytes de margem. Flash:
~21,4 KB de ~32 KB disponíveis.

## Pendências abertas (não resolvidas por adivinhação - ver comentários inline)

1. **`MS0A`/`ELS0A` do TIM ("software compare only")** - configurado em
   `scheduler.c` a partir da Table 17-3 do datasheet, mas a leitura da
   tabela teve uma ambiguidade real. **Precisa validar no simulador** que a
   interrupção de compare de fato dispara antes de confiar nisso.
2. **Clock de barramento assumido em 8MHz** (`timebase.c`, `scheduler.h`,
   `serial_hc08.c`) - placeholder, ajustar quando o clock real da placa
   for definido (afeta também o baud rate da SCI, hoje `SCBR=0x00`).
3. **Pinos das bobinas/injetores** (`PTA0/PTA1`, `PTB0-2` em `scheduler.c`)
   - placeholder, sem mapeamento de pinagem real definido ainda.
4. **RISING/CHANGE no pino IRQ** - não suportado pelo hardware dedicado
   (só FALLING). Alternativa seria o módulo KBI (Port A) - não investigado.
5. **Storage real** - o placeholder de `storage.c` precisa virar um design
   de verdade em Flash (shadow em RAM + flush periódico é o candidato mais
   provável) antes de qualquer teste com dados de tabela reais.
6. **`getFreeRam()` placeholder** - retorna 0, sem mecanismo real de
   introspecção de heap pra SDCC/HC08 (não adivinhado).
7. **Camada serial por polling, não interrupção** - `serial_hc08.c` bloqueia
   em `sciWriteByte()` até o registrador de TX ficar livre. Funcional, mas
   diferente do `HardwareSerial` orientado a ISR do AVR - pode virar
   ISR-driven depois se a latência de bloqueio for um problema.
8. **Avisos de sign-compare em `fuel.c`** (linhas 84/93) - pré-existentes
   no AVR original, não corrigidos aqui (precisa decisão de quem entende
   a intenção do `wueBins[]` ser `uint8_t` vs `coolant` ser `int8_t`).

## Build

```sh
make
```

Ver `Makefile` - já embute o workaround do bug de empacotamento do sdcc
(Ubuntu 4.2.0: a chamada automática do assembler quebra, "sdas6808 ll
-plosgffw ..." com um "ll" espúrio) e a flag `--stack-auto` obrigatória.

## Validação

Ainda não rodado de ponta a ponta em simulador (o fork do ucsim do autor,
https://github.com/alexandrefelipemuller/ucsim, já builda limpo com suporte
a `m68hc08` incluindo periféricos de ADC/SCI calibrados pro GP32 - próximo
passo natural de validação, adiado por ora a pedido do autor).
