# Branch `ms1` — corte de RAM (tabelas 12×12 + config pages sem padding)

> Experimento isolado. Não deve ser mesclado na `main` sem decidir também
> a estratégia de `.ini`/protocolo (ver "Compatibilidade quebrada" abaixo).

## Motivação

Surgiu de uma pergunta sobre adaptar o Slowduino ao protocolo MS1/Extra
(que usa tabelas 12×12, contra as 16×16 do Speeduino/Slowduino). Analisando
o `.ini` do MS1, ficou claro que ir atrás do protocolo completo do MS1
*aumentaria* o uso de RAM (9 páginas de 189 bytes = 1701 B só de páginas).
Só a redução das tabelas para 12×12 é que trazia ganho real — daí este
branch: reaproveita a ideia (tabelas menores) sem adotar o protocolo MS1
inteiro.

## O que foi medido (build real, `atmega328p @16MHz`, mesmas flags do resto do projeto)

| Mudança | RAM (Data) | Δ |
|---|---:|---:|
| Baseline (`main`, tabelas 16×16) | 1464 B (71,5%) | — |
| + tabelas VE/Ignição 16×16 → 12×12 | 1216 B (59,4%) | −248 B |
| + remove `spare[]` das config pages | **1080 B (52,7%)** | **−384 B (−26,2%) no total** |

Breakdown final (`avr-nm --size-sort`):

| Item | Antes | Depois |
|---|---:|---:|
| `veTable` | 312 B | 188 B |
| `ignTable` | 312 B | 188 B |
| `configPage1` | 128 B | 52 B |
| `configPage2` | 128 B | 68 B |
| resto (status, buffers, scheduler, `Serial`, core) | 460 B | 460 B (inalterado) |

Flash caiu junto (21990 → 21768 B), sem custo extra — tabela menor é
código/dado menor dos dois lados.

## O que foi mudado

- `config.h`: `TABLE_SIZE_X`/`TABLE_SIZE_Y` de 16 para 12. `DEFAULT_VE_TABLE`,
  `DEFAULT_IGN_TABLE` e seus eixos reamostrados (interpolação bilinear) das
  tabelas 16×16 originais, mesma faixa de RPM/MAP (500-8000 / 20-170).
  `DEFAULT_AFR_TABLE` removida (não tinha nenhuma referência no código).
- `globals.h`: `spare[76]` de `ConfigPage1` e `spare[60]` de `ConfigPage2`
  removidos — só existiam para as structs baterem 128 bytes (tamanho de
  página do protocolo Speeduino). `EEPROM_DATA_VERSION` 4→5 para forçar
  reseed.
- `comms.cpp`: `SPEEDUINO_TABLE_DIM` 16→12 (e todo o resto derivado dele,
  já era parametrizado — só essa constante precisou mudar). `pageSize[]`
  das páginas 1 e 4 passou a usar `sizeof(ConfigPage1/2)` em vez de `128`
  hardcoded.
- `config.h`: offsets de EEPROM (`EEPROM_VE_TABLE`, `EEPROM_CONFIG1`, etc.)
  recalculados para os novos tamanhos — também libera ~248 bytes de EEPROM
  que antes ficavam vagos entre valores e eixos das tabelas.

## Compatibilidade quebrada (de propósito, mas registrando)

- **Páginas 2 e 3 do protocolo TunerStudio** (mapas VE/Ignição) agora têm
  168 bytes, não 288. Qualquer `.ini` que espere o layout padrão do
  Speeduino vai ler/escrever essas tabelas errado. Precisa de `.ini`
  próprio.
- **Páginas 1 e 4** (config) agora têm 52 e 68 bytes, não 128. Mesmo
  problema.
- Isso é aceitável *neste branch* porque o objetivo era medir o piso de RAM,
  não manter compatibilidade de protocolo. Se um dia isso for usado de
  verdade, o `.ini` de referência do projeto precisa ser reescrito com os
  novos `pageSize`.

## O que foi medido mas NÃO aplicado no código

Os buffers internos do `Serial` (RX/TX do core Arduino, 64+64 bytes,
componente do objeto `Serial` de 157 B) renderiam mais **96 bytes** se
reduzidos para 16/16 (`Data` cairia para 984 B, −33% do baseline original).
Medição real: recompilei o core AVR com
`-DSERIAL_TX_BUFFER_SIZE=16 -DSERIAL_RX_BUFFER_SIZE=16` e linkei contra ele.

**Por que não entrou no branch:** o Slowduino compila via Arduino IDE puro
(sem `platformio.ini`), e a IDE injeta `#include <Arduino.h>` como a
primeira linha do `.ino` automaticamente, antes de qualquer código do
projeto — não há como um `#define` dentro do repositório vencer essa
corrida e sobrescrever o tamanho do buffer antes do `HardwareSerial.h` ser
processado. Só funciona com um sistema de build que recompile o core por
projeto (ex: PlatformIO com `build_flags`), que o Slowduino não tem hoje.
Migrar para PlatformIO é uma decisão maior, fora do escopo deste corte de
RAM.

## Risco de reduzir o buffer serial (caso alguém migre para PlatformIO depois)

Buffer de RX menor (16 em vez de 64) tolera menos rajada de dados antes do
`commsProcess()` drenar no próximo `loop()`. Como `commsProcess()` roda a
cada iteração do loop (alta frequência), o risco é baixo na prática, mas
não foi validado com tráfego real do TunerStudio.
