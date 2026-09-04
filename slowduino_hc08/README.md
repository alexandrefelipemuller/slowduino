# Slowduino - port HC08 (MC68HC908GP32)

Port experimental do Slowduino para o núcleo original da MegaSquirt MS1
(Freescale/Motorola MC68HC908GP32), compilado com SDCC (`-mhc08`), em C puro
(SDCC não compila C++).

## ACHADO CRITICO: `--stack-auto` e obrigatorio

Sem essa flag, o SDCC aloca parametros e variaveis locais de CADA funcao
como armazenamento fixo permanente (nao pilha real) por padrao no backend
hc08 - so 11 bytes conseguem ser reaproveitados via overlay (`OSEG`).
Medido nesta sessao, mesmo codigo (globals+timebase+scheduler+decoders+
main): **501 bytes de RAM sem `--stack-auto` vs 303 bytes com**. Custo:
~793 bytes a mais de Flash (frame de pilha real por chamada). Essa e
exatamente a "desvantagem do compilador no meio do caminho" antecipada no
inicio desta investigacao - agora com numero real. O `Makefile` deste
diretorio ja usa `--stack-auto` como padrao.

## Estado atual

Esqueleto compila e linka de ponta a ponta (`sdcc -mhc08` + `sdas6808` +
`sdcc` linkando os `.rel`), gerando um `.ihx` válido:

- `mc68hc908gp32_sfr.h` - registradores de hardware, conferidos linha a linha
  contra o datasheet oficial (NXP, Rev. 10) **e** contra o `Gp32.equ` da
  firmware MS1 original (`/home/alexandre/Downloads/029y4a/src/Gp32.equ`) -
  ambas as fontes batem exatamente.
- `globals.h`/`globals.c` - port direto das structs `Statuses`/`ConfigPage1`/
  `ConfigPage2` da branch `tiny` (sem `__attribute__((packed))` - HC08 não
  precisa, núcleo 8-bit sem alinhamento).
- `timebase.h`/`timebase.c` - equivalente a `micros()` do Arduino core,
  construído sobre overflow do TIM2 (TIM1 fica dedicado à ignição).
- `scheduler.h`/`scheduler.c` - port 1:1 da lógica de `IgnitionSchedule`/
  `armIgnitionCompare`/`handleIgnitionChannel`/`setIgnitionSchedule` do AVR,
  **sem simplificar para "um timer por canal"** (mantido genérico de
  propósito, para reversibilidade entre as duas arquiteturas) - usa TIM1
  canal 0/1 (equivalente a OCR1A/OCR1B), deixando TIM2 livre (igual ao
  Timer2 do AVR, reservado pra IAC).
- `decoders.h`/`decoders.c` - port 1:1 de `triggerPri_MissingTooth`/
  `triggerPri_BasicDistributor`/`calculateRPM`/`checkSyncLoss` (com
  agendamento direto de injeção/ignição na ISR, igual ao AVR). Diferença
  real de hardware: o pino dedicado `IRQ` do GP32 só detecta borda de
  **descida** - não existe RISING nem CHANGE (ambas as bordas) nesse pino,
  ao contrário do `attachInterrupt` do AVR. Ver ressalva grande no topo do
  arquivo.
- `config.h` - constantes compartilhadas (cresce junto com o port).
- `storage.h`/`storage.c` - **PLACEHOLDER, não é storage real**. O GP32
  não tem EEPROM (só Flash, apagada em páginas de 128 bytes com bomba de
  carga via `FLCR` - ver cap. 2.6 do datasheet). Isso exige um redesign
  de verdade (provável shadow em RAM sincronizado com Flash), ainda não
  decidido. Por ora `eepromReadByte()`/`eepromReadI8()` retornam valor
  fixo, só para não travar `tables.c`/`fuel.c`.
- `tables.h`/`tables.c` - port 1:1 de `getTableValue()`/interpolação
  bilinear (branch tiny, sem cache). Lê célula via `storage.h` (hoje
  placeholder).
- `fuel.h`/`fuel.c` - port 1:1 de `calculateInjection()`/`calculateCorrections()`/
  WUE/ASE/AE/CLT/battery. 2 avisos do compilador (`fuel.c:84,93`) sobre
  comparação signed/unsigned entre `coolant` (`int8_t`) e `wueBins[]`
  (`uint8_t`) - **pré-existente no AVR original**, não introduzido pelo
  port; o SDCC só é mais rigoroso que o avr-gcc nesse aviso. Não corrigido
  aqui - precisa decisão de quem entende a intenção original.
- `main.c` - boot com trigger + fuel + tables conectados (falta `ignition.c`:
  `currentStatus.advance`/`dwell` ainda ficam zerados de boot).

**RAM: 412 bytes** (`globals+timebase+scheduler+decoders+storage+tables+
fuel+main`). Ainda dentro dos 512B mesmo com a cadeia trigger→ISR→
scheduler→fuel→tabela completa. Faltam `ignition.c`, `comms` (protocolo
Speeduino via SCI) e o storage real.

## Numeração de interrupção do SDCC (`__interrupt(N)`)

Verificada empiricamente (compilando ISRs com N conhecidos e inspecionando
o `.asm` gerado), não adivinhada. Fórmula: `endereço = 0xFFFE - 2*N`.
Tabela completa em `mc68hc908gp32_sfr.h`.

## Pendências abertas (não resolvidas por adivinhação - ver comentários inline)

1. **`MS0A`/`ELS0A` do TIM ("software compare only")** - configurado em
   `scheduler.c` a partir da Table 17-3 do datasheet, mas a leitura da
   tabela teve uma ambiguidade real. **Precisa validar no simulador** que a
   interrupção de compare de fato dispara antes de confiar nisso.
2. **Clock de barramento assumido em 8MHz** (`timebase.c`, `US_TO_TIMER1` em
   `scheduler.h`) - placeholder, ajustar para o clock real da placa.
3. **Pinos das bobinas** (`PTA0`/`PTA1` em `scheduler.c`) - placeholder, sem
   mapeamento de pinagem real definido ainda.
4. **Reentrância** - com `--stack-auto`, funções normais já usam pilha real
   (resolve a maior parte da preocupação original). Falta confirmar como
   isso interage com `__interrupt` especificamente (ex: `triggerPri_*` são
   chamadas de dentro de `isr_irq()` E fazem chamadas profundas - validar
   que o SDCC não precisa de `__reentrant` explícito adicional nelas).
5. **RISING/CHANGE no pino IRQ** - não suportado pelo hardware dedicado
   (só FALLING). Alternativa seria o módulo KBI (Port A) - não investigado.
6. **Storage real** - o placeholder de `storage.c` precisa virar um design
   de verdade em Flash antes de qualquer teste com dados de tabela reais.
7. **Ainda faltam**: `ignition.c` (avanço/dwell - hoje zerados), `comms`
   (protocolo Speeduino via SCI).
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
passo natural de validação, adiado por ora).
