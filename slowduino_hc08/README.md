# Slowduino - port HC08 (MC68HC908GP32)

Port experimental do Slowduino para o núcleo original da MegaSquirt MS1
(Freescale/Motorola MC68HC908GP32), compilado com SDCC (`-mhc08`), em C puro
(SDCC não compila C++).

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
- `main.c` - boot mínimo, agenda pulsos de ignição de teste a cada ~20ms.

**RAM do esqueleto atual: 288 bytes** (`DSEG+OSEG+XSEG+XISEG` do linker).
Ainda não inclui decoders/fuel/comms/storage - não é o número final.

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
4. **Reentrância** - funções chamadas tanto do loop principal quanto de ISR
   ainda não passaram por auditoria (SDCC usa parâmetros como variável
   global fixa por padrão, não pilha - ver discussão na sessão).
5. **Ainda faltam**: decoders (trigger), fuel, tables (sem EEPROM - GP32 só
   tem Flash, ver ressalva de storage), comms (protocolo Speeduino via SCI).

## Build

```sh
# workaround do bug de empacotamento do sdcc (Ubuntu 4.2.0): a chamada
# automática do assembler quebra ("sdas6808 ll -plosgffw ..."), roda-se
# o pipeline em 3 passos manualmente:
for f in globals timebase scheduler main; do
  sdcc -mhc08 --std-c99 -Wall -S $f.c
  sdas6808 -plosgffw $f.rel $f.asm
done
sdcc -mhc08 --std-c99 globals.rel timebase.rel scheduler.rel main.rel -o slowduino_hc08.ihx
```

## Validação

Ainda não rodado de ponta a ponta em simulador (o fork do ucsim do autor,
https://github.com/alexandrefelipemuller/ucsim, já builda limpo com suporte
a `m68hc08` incluindo periféricos de ADC/SCI calibrados pro GP32 - próximo
passo natural de validação, adiado por ora).
