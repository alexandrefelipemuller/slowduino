# Branch `ms1` — corte de RAM (rumo aos 512B do MS1 original)

> Experimento isolado, agressivo de propósito. Não deve ser mesclado na
> `main` sem decidir a estratégia de `.ini`/protocolo (ver "Compatibilidade
> quebrada") e sem testar em hardware real (ver "Riscos assumidos").

## Motivação

Surgiu de uma pergunta sobre adaptar o Slowduino ao protocolo MS1/Extra, que
rodava no 68HC908 GP32 (Motorola) com **512 bytes de RAM**. Análise do
`.ini` mostrou que copiar o protocolo MS1 inteiro (9 páginas de 189 bytes)
*aumentaria* a RAM. Só valia a pena reaproveitar duas ideias do MS1, sem
adotar o protocolo dele:

1. Tabelas menores (12×12 em vez de 16×16).
2. **A técnica principal, achada lendo o `.asm` real do MS1**
   (`msns-extra.asm`): o firmware original **não mantém as tabelas em RAM**.
   Cada lookup lê direto da flash (persistente), com um buffer de RAM de
   189 bytes compartilhado entre todas as 7 tabelas, usado só durante tuning
   ao vivo. Ver a macro `ve1x` em `msns-extra.asm:744` e o comentário em
   `msns-extra.asm:990-996`.

## Resultado final (build real, `atmega328p @16MHz`)

| Etapa | RAM (Data) | Δ acumulado |
|---|---:|---:|
| Baseline (`main`, tabelas 16×16, tudo em RAM) | 1464 B (71,5%) | — |
| + tabelas 16×16 → 12×12 | 1216 B (59,4%) | −248 B |
| + remove `spare[]` das config pages | 1080 B (52,7%) | −384 B |
| + valores de tabela só em EEPROM (streaming por lookup) | 796 B (38,9%) | −668 B |
| + `Serial` do core com buffers 16/16 (via PlatformIO) | ~700 B | −764 B |
| + `serialBuffer` próprio 64→24 | **660 B (32,2%)** | **−804 B (−54,9%)** |

Breakdown final (`avr-nm --size-sort`), maiores itens:

| Item | Tamanho |
|---|---:|
| `currentStatus` | 73 B |
| `configPage2` | 68 B |
| `Serial` (core, buffers 16/16) | 61 B |
| `configPage1` | 52 B |
| `veTable` / `ignTable` (só eixos+cache, sem valores) | 46 B cada |
| `triggerState` | 44 B |
| `serialBuffer` | 24 B |
| `injector1/2/3Polling` | 10 B cada |
| `ignitionSchedule1/2` | 9 B cada |
| resto (contadores, flags, timers) | ~198 B |

Flash caiu junto: 21990 → 21174 B.

## A mudança principal: tabelas VE/Ignição não moram mais em RAM

Inspirado direto no `ve1x`/`ve2x`/.../`AFR2X` do MS1. Implementado em:

- **`tables.h`**: `Table3D` perde o array `values[Y][X]` (144 B). Fica só
  com os eixos (36 B), um `uint16_t eepromValuesBase` (endereço na EEPROM) e
  o cache de última consulta (~8 B). ~46 B por tabela em vez de ~188 B.
- **`tables.cpp`**: `getTableValue()` (bilinear) lê os 4 cantos vizinhos via
  `eepromReadByte()`/`eepromReadI8()` em vez de indexar o array em RAM.
- **`storage.cpp`**: `loadVETable()`/`saveVETable()` (e Ign) não copiam mais
  valores entre RAM e EEPROM — só os eixos. `loadDefaultTables()` escreve os
  defaults direto do PROGMEM para a EEPROM, sem passar por RAM.
- **`comms.cpp`**: os handlers de página do TunerStudio (`readVeTablePageByte`,
  `writeVeTablePageByte`, etc.) leem/escrevem a célula direto na EEPROM.

### Custo: leitura é grátis, escrita não

Corrigindo uma imprecisão que passei antes: **leitura de EEPROM no AVR é
rápida** (`EEPROM.read()`, poucos ciclos de clock - nada como o "~3.3µs por
byte" que citei numa resposta anterior, que na verdade nem é a métrica
certa). O que É lento é a **escrita**: **~3.3ms por byte alterado**
(`EEPROM.write()`, ciclo de programação físico da célula). Por isso:

- **Lookups em runtime** (cálculo de combustível/ignição a cada ciclo) são
  seguros - só leem, custo desprezível perto do orçamento de tempo do
  projeto.
- **Editar uma célula pelo TunerStudio** agora custa ~3.3ms (só acontece
  durante tuning ao vivo, não no loop do motor - sem impacto no motor
  rodando).
- **Primeiro boot com EEPROM virgem**: `loadDefaultTables()` grava até
  12×12×2 = 288 bytes (VE+Ign). No pior caso (EEPROM apagada, tudo `0xFF`,
  todo valor precisa mesmo ser escrito): **~0,95s de atraso no primeiro
  boot**. Único, não repete em boots seguintes (a versão salva na EEPROM
  passa a bater com `EEPROM_DATA_VERSION`).

## Buffers de comunicação

- **`Serial` do core Arduino**: buffers de RX/TX internos (64+64 B por
  padrão) reduzidos para 16/16 via `-DSERIAL_TX_BUFFER_SIZE=16
  -DSERIAL_RX_BUFFER_SIZE=16`. **Isso exigiu adicionar `platformio.ini`
  ao projeto** (novo, só nesta branch) - a Arduino IDE injeta
  `#include <Arduino.h>` como primeira linha do `.ino` antes de qualquer
  `#define` do projeto, então não tem como isso funcionar num build só-Arduino-IDE.
  PlatformIO recompila o core por projeto, então os `build_flags` chegam a
  tempo. `pio` está instalado nesta máquina mas quebrado (incompatibilidade
  de versão do Click) - validei recompilando o core manualmente com as
  mesmas flags e linkando contra ele, não rodei `pio run` de verdade.
- **`serialBuffer`** (buffer de montagem do protocolo, em `comms.cpp`): 64→24
  bytes. Também removida uma segunda definição duplicada e idêntica de
  `SERIAL_BUFFER_SIZE` que existia em `comms.h` (risco de ficarem
  dessincronizadas).

### Risco assumido

- RX do core em 16 bytes tolera menos rajada antes do próximo
  `commsProcess()` (chamado a cada `loop()`, alta frequência - risco baixo
  na prática, não testado com tráfego real do TunerStudio).
- `serialBuffer` em 24 bytes derruba o payload máximo do protocolo moderno
  de 58 para 18 bytes (`SERIAL_BUFFER_SIZE - 6`). Mensagens maiores que isso
  são **rejeitadas de forma segura** (há um check explícito em
  `commsProcess()`, sem risco de overflow de buffer) - mas a ferramenta de
  tuning precisa enviar chunk-writes de tabela em pedaços de até 18 bytes.
  Mais um motivo pelo qual esta branch já não é compatível com nenhum `.ini`
  padrão.

## Compatibilidade quebrada (de propósito)

- Páginas 2/3 (tabelas): 168 B, não 288.
- Páginas 1/4 (config): 52/68 B, não 128.
- Chunk-writes de tabela: até 18 B por vez, não os ~256 B que o TunerStudio
  costuma usar por padrão.
- Precisa de `.ini` próprio e de configurar o tamanho de chunk na ferramenta
  de tuning. Nada disso importa para o objetivo (medir o piso de RAM), mas
  quem for usar isso de verdade precisa saber.

## O que NÃO foi tocado (e por quê)

O maior item que sobrou é `configPage1`+`configPage2` (120 B). Dava pra
aplicar a mesma técnica de streaming por EEPROM - e como leitura é barata,
seria tecnicamente viável. Não fiz porque o raio de ação é muito maior: os
campos de tabela eram acessados só por ~5 pontos centralizados
(`getTableValue`, os 4 handlers de página). Os campos de config
(`configPage1.reqFuel`, `configPage2.idleKP`, etc.) são acessados **por
nome, em dezenas de lugares** espalhados por `fuel.cpp`, `ignition.cpp`,
`sensors.cpp`, `auxiliaries.cpp`, `protections.cpp` - e o mecanismo genérico
de leitura/escrita de página do `comms.cpp`
(`readStructPageByte`/`writeStructPageByte`) depende de `configPage1`/`2`
serem structs reais em RAM (usa `sizeof()` e aritmética de ponteiro
diretamente sobre elas). Trocar isso por leitura sob demanda seria reescrever
esse mecanismo inteiro e revisar cada acesso nomeado nesses 5 arquivos - risco
real de errar um offset e não ter como validar sem bancada. Ficou de fora
desta passada; é o próximo lugar óbvio para continuar se alguém quiser
chegar mais perto ainda dos 512 B.

`triggerState`, `injector*Polling`, `ignitionSchedule*` (estado do
scheduler/decoder em tempo real) também não foram tocados - são o núcleo do
timing de ignição/injeção, e qualquer corte ali exige revisão cuidadosa do
código de agendamento, fora do orçamento desta passada.
