# Contexto: Slowduino rumo a 512 bytes de RAM (inspirado no MS1)

> Documento de retomada. Escrito para continuar a tarefa depois, sem precisar
> re-investigar o que já foi descoberto. Cobre: o que é o MS1, o que foi
> aprendido lendo o firmware real dele, o que já foi feito na branch `ms1`
> do Slowduino, os números reais medidos em cada etapa, e o que falta pra
> chegar em 512 bytes.

## Estado atual (o que importa saber primeiro)

- **Branch:** `ms1`, no repositório `~/Projects/slowduino`, criada a partir da
  `main` (commit `92f3c77`).
- **RAM atual: 620 bytes de 2048 (30,3%).** Início era 1464 bytes (main,
  71,5%). Redução de 57,7%.
- **Faltam 108 bytes para chegar em 512.**
- Achados de uma análise diferencial (MS1 asm vs Slowduino C, rotina por
  rotina) renderam 6 bytes já aplicados (Etapa 7, abaixo) - não fecham a
  conta. O único item grande o bastante para fechar é reescrever
  `configPage1`/`configPage2` com a mesma técnica de streaming por EEPROM já
  aplicada nas tabelas, e **isso ainda não foi feito** (ver "Próximo passo
  obrigatório" no fim).
- Doc irmão com o detalhe técnico de cada commit:
  `documents/BRANCH_MS1_REDUCAO_RAM.md` (mesmo repositório).

---

## Parte 1: O que é o MS1 e o que foi descoberto nele

### Origem

MS1/Extra (também "MSnS-Extra"), por James Murray e Phil Ringwood. Roda no
**Motorola/Freescale 68HC908 GP32** - um micro de 8 bits com **512 bytes de
RAM**. Arquivos em `/home/alexandre/Downloads/029y4a/`:

- `src/msns-extra.asm` - fonte assembly principal (~507 KB, ~30 mil linhas)
- `src/msns-extra.h`, `src/*.inc` - constantes e tabelas de fator
- `src/mem_map.txt` - mapa de endereços de RAM documentado pelos autores
  (de `0x0040` até pelo menos `0x011A`)
- `msns-extra.ini` (na raiz, não em `src/`) - definição de protocolo/página
  para MegaTune/TunerStudio
- `msns-extra.s19` (na raiz) - **o firmware já compilado**, formato Motorola
  S-record. Não precisa rodar o assembler para ter esse arquivo - ele já
  existe pronto.
- `src/CASM08Z.EXE`, `src/DOWNLOAD.EXE` - assembler e uploader. São `.exe`
  do Windows de verdade (PE32, não DOS puro). Neste sistema o clique duplo
  abre errado com o gerenciador "Arqiver" porque
  `xdg-mime query default application/x-ms-dos-executable` aponta para
  `arqiver.desktop` e não existe `wine.desktop` registrado - não é problema
  do arquivo. Pra abrir de verdade: `wine CASM08Z.EXE` num terminal (não
  clique duplo). É um app gráfico - só abre numa sessão com tela de verdade
  (tentei aqui num shell headless e travou sem abrir nada).
- Não há desmontador de 68HC08/68HC11 disponível no binutils desta máquina
  (`objdump -i` só lista alvos x86/genéricos) - então não dá pra desmontar
  o `.s19` automaticamente. A análise de rotinas foi feita lendo o `.asm`
  fonte na mão.

### O `.ini` do MS1 (protocolo/páginas)

- **9 páginas de 189 bytes cada** (pode chegar a 13 em modo debug/dev,
  `#if MEMPAGES`). `PAGESIZE equ 189` no fonte.
- Tabelas **12×12** (não 16×16 como Speeduino/Slowduino tradicional).
- Layout por página: página 1 = VE table 1, página 2 = VE table 2 (modo DT),
  página 3 = tabela de ignição + trigger + idle advance, página 4 = um
  grab-bag enorme de configuração geral (EDIS, HEI, launch control, boost,
  knock, saídas programáveis com ~30 fontes cada - muito além do que o
  Slowduino precisa), páginas 5-8 = AFR target e boost controller, página 9
  = idle control + curva de warmup (10 pontos) + curva de PW de partida (10
  pontos) + correção de IAT + rev limiter + tabela de ignição split (6×6,
  motor rotativo - irrelevante pro Slowduino).
- **Reproduzir o protocolo MS1 inteiro pioraria a RAM do Slowduino**, não
  ajudaria: 9 páginas × 189 B = 1701 B só de páginas, mais que os ~880 B que
  tabelas+config ocupavam no Slowduino original. Foi por isso que a decisão
  foi "pegar as ideias, não o protocolo".

### A técnica principal (achada lendo o `.asm` de verdade)

**As tabelas do MS1 não moram em RAM.** Cada leitura de tabela passa por uma
macro que decide, em tempo de execução, se lê de um buffer de RAM (só
quando aquela página está sendo editada ao vivo pelo tuning software) ou
direto da flash (sempre, durante a operação normal do motor):

```asm
; msns-extra.asm:744-825 - uma macro dessas pra cada tabela
; (VE1, VE2, VE3, Spark1, Spark2, AFR1, AFR2 - 7 no total)
$MACRO ve1x
        lda     page
        cmp     #01T
        bne     ve1xf
        lda     VE_r,x      ; página 1 está "carregada" -> lê da RAM
        bra     ve1xc
ve1xf:  lda     VE_f1,x     ; senão, lê direto da FLASH
ve1xc:
$MACROEND
```

`VE_r` é **um único buffer de 189 bytes** (`PAGESIZE`) compartilhado pelas 7
tabelas - não uma cópia por tabela. No boot (`msns-extra.asm:990-996`), o
firmware seta `page = $ff` (inválido) de propósito, com o comentário:

> *"For multi table work we always operate from flash unless directed to
> copy the data into RAM for tuning... the initial release will use all
> other variables from flash ONLY."*

Ou seja: rodando o motor, **nenhuma tabela mora em RAM**. Essa foi a
inspiração direta para a mudança mais importante feita na branch `ms1` (ver
Parte 2, Etapa 3).

### Outras técnicas de economia de RAM encontradas

- **Overlay manual de variáveis não relacionadas no mesmo endereço.**
  Changelog do próprio código, `msns-extra.asm:531`: *"Save ram by combining
  stHp, avgtoothh and low bytes."* - três variáveis de contextos diferentes
  dividem o endereço `0x00F3` porque nunca estão "vivas" ao mesmo tempo.
- **Pool de scratch compartilhado.** `tmp1`...`tmp22` (~22 bytes,
  `0x94`-`0xA9`) reutilizados por dezenas de sub-rotinas não relacionadas
  para cálculo temporário, em vez de cada rotina ter suas próprias globais.
- **Rotinas fundidas para economizar RAM, de propósito.** `WUE_CALC`
  (`msns-extra.asm:2309-2447`) calcula Warmup **e** ASE (After-Start
  Enrichment) na mesma rotina, comentário explícito no fonte
  (`msns-extra.asm:2277-2278`): *"Now we do all the WUE, TAE and EGO in
  sequence rather than subroutines (ram saving?)"*. Isso significa que **não
  dá pra separar "RAM do Warmup" de "RAM do ASE" no MS1** - é uma
  característica da arquitetura, não um detalhe de implementação.

### Números reais medidos (análise diferencial, rotina por rotina)

Comparação feita contando instruções reais no `.asm` (excluindo comentários/
labels) e medindo o binário real do Slowduino (`avr-nm --size-sort`, branch
`main` sem nenhuma otimização de RAM):

**Warmup + ASE:**

| | MS1 (`WUE_CALC`, os dois juntos) | Slowduino `main` (separados) |
|---|---|---|
| Instruções / flash | 96 instruções | `correctionWUE()` 162 B + `correctionASE()`+`startASE()` 58 B |
| RAM **dedicada** | 2 bytes (`ASEcount` + `warmcor`) | 4 bytes (`aseCounter`+`aseValue`, ambos `uint16_t`) |
| Resto tocado | `tmp31`, `tmp1/3/4/5/6`, `coolant`, bits de `engine` - **compartilhado** com dezenas de outras rotinas | `currentStatus.coolant`, `configPage1.wueBins/Values` - também compartilhado |

Achado: `aseCounter`/`aseValue` guardam valores 0-255 mas são `uint16_t` -
poderiam ser `uint8_t` (-2 bytes, ver "pequenos ganhos" abaixo).

Achado bônus (bug, não RAM): **`decrementASE()` existe, é chamada em lugar
nenhum** (`grep` confirma: só declarada em `fuel.h` e definida em `fuel.cpp`,
zero chamadas). O ASE provavelmente nunca decai com o tempo como a
documentação sugere - fica travado no valor inicial. Ainda presente na
`main`, não corrigido.

**Fuel Calc / VE Lookup:**

| | MS1 (`CalcPWs`→`No_VE3`, VE1+VE3) | Slowduino `main` |
|---|---|---|
| Instruções / flash | 133 instruções (as duas rotas juntas; só uma roda por vez) | `getTableValue()` 722 B + `findTableXIndices()` 200 B + `findTableYIndices()` 166 B + `getVE()` 38 B + `calculateInjection()` 212 B = **1338 B** |
| RAM dedicada à lógica | ~4 bytes (`vecurr`, `vecurr2`, `kpa_n`, `VE3Timer`) | 0 (só variáveis locais de pilha) |
| Onde mora a tabela | **Flash** (`VE1_f`, `VE3_f`) | **RAM**, 312 B (`veTable`, 16×16, antes de qualquer otimização) |

Conclusão: em ambos os lados, a lógica de cálculo em si não é o problema de
RAM - é quase toda variável de pilha (Slowduino) ou scratch compartilhado
(MS1). **Toda a RAM do "Fuel Calc" está concentrada no armazenamento da
própria tabela.** Essa análise, feita do zero, confirma que mover as
tabelas para a EEPROM (Etapa 3, abaixo) foi a intervenção de maior impacto
possível - bate com o resultado medido (essa etapa sozinha cortou 668 B de
1080 B, o maior corte de toda a sequência).

Achado bônus (flash, não RAM): 722 bytes para uma interpolação bilinear é
grande - provavelmente por causa da aritmética em `int32_t` com divisão
dentro de `interpolate()`, e por duplicar o caminho `isSigned`/`!isSigned`
dentro da mesma função. Não investigado a fundo.

**Total do firmware MS1 (do `.s19`, sem precisar rodar assembler):**
27.832 bytes de código real, endereços `0x8128`-`0xFFFF`. **Mais flash que
o Slowduino `main` usa (~22 KB)**, apesar de ter 4x menos RAM - o MS1 troca
flash por RAM agressivamente (mais código pra economizar bytes); o
Slowduino faz o oposto hoje.

---

## Parte 2: O que já foi feito na branch `ms1` (com números reais)

Todas as medições: `atmega328p @16MHz`, compilado manualmente com
`avr-g++`/`avr-gcc` (não a Arduino IDE nem `pio` - `pio` está instalado
nesta máquina mas quebrado, incompatibilidade de versão do Click:
`pio --version` quebra com `AttributeError`).

| Etapa | RAM (`Data`) | Δ acumulado |
|---|---:|---:|
| Baseline (`main`) | 1464 B (71,5%) | - |
| 1. Tabelas 16×16 → 12×12 | 1216 B (59,4%) | -248 B |
| 2. Remove `spare[]` das config pages | 1080 B (52,7%) | -384 B |
| 3. Valores de tabela só em EEPROM (streaming por lookup) | 796 B (38,9%) | -668 B |
| 4. `Serial` do core com buffers 16/16 (via PlatformIO) | ~700 B | -764 B |
| 5. `serialBuffer` próprio 64→24 | 660 B (32,2%) | -804 B |
| 6. Campos mortos removidos (varredura) | 626 B (30,6%) | -838 B |
| 7. Tipos estreitados (`aseCounter`/`aseValue`/`expectedLength`/`idleIntegral`) | **620 B (30,3%)** | **-844 B (-57,7%)** |

Flash: 21990 → 21036 B (também caiu, sem custo extra em nenhuma etapa).

### Etapa 1 - Tabelas 16×16 → 12×12

- `config.h`: `TABLE_SIZE_X`/`TABLE_SIZE_Y` de 16 para 12.
- `DEFAULT_VE_TABLE`/`DEFAULT_IGN_TABLE` e eixos reamostrados (interpolação
  bilinear) das tabelas 16×16 originais, mesma faixa de RPM/MAP
  (500-8000/20-170).
- `DEFAULT_AFR_TABLE` removida inteira (zero referências em qualquer lugar
  do código - já estava morta antes desta branch).

### Etapa 2 - Remove `spare[]` das config pages

- `spare[76]` (`ConfigPage1`) e `spare[60]` (`ConfigPage2`) existiam só para
  as structs baterem 128 bytes (tamanho de página do protocolo Speeduino).
  Removidos.
- `static_assert` atualizados em `globals.h`/`comms.cpp`; `pageSize[]` em
  `comms.cpp` (páginas 1 e 4) passou a usar `sizeof(ConfigPage1/2)` em vez
  de `128` fixo; offsets de EEPROM recalculados em `config.h`.
- `EEPROM_DATA_VERSION` 4→5.

### Etapa 3 - Tabelas sem cópia em RAM (streaming por EEPROM) - A MUDANÇA PRINCIPAL

Inspirada direto nas macros `ve1x`/`ve2x`/.../`AFR2X` do MS1.

- `tables.h`: `Table3D` perde o array `values[Y][X]` (144 B). Fica só com
  os eixos (36 B), um `uint16_t eepromValuesBase` (endereço na EEPROM) e o
  cache de última consulta (~8 B). **~46 B por tabela** (era ~188 B).
- `tables.cpp`: `getTableValue()` (bilinear) lê os 4 cantos vizinhos via
  `eepromReadByte()`/`eepromReadI8()` em vez de indexar array em RAM.
- `storage.cpp`: `loadVETable()`/`saveVETable()` (e Ign) não copiam mais
  valores entre RAM e EEPROM - só os eixos. `loadDefaultTables()` escreve
  os defaults direto do PROGMEM para a EEPROM, sem passar por RAM.
- `comms.cpp`: handlers de página do TunerStudio leem/escrevem a célula
  direto na EEPROM.

**Correção importante feita durante o trabalho:** inicialmente achei que
leitura de EEPROM custava ~3,3µs/byte e arriscaria o timing do motor -
**errado**. Leitura de EEPROM no AVR é rápida (poucos ciclos, sem espera).
Só a **escrita** é lenta (~3,3ms/byte, bloqueante - `EEPROM.write()` já tem
otimização de "só escreve se mudou" em `eepromWriteByte()`). Consequência
real:
- **Lookups em runtime são de graça** (leitura), sem risco pro timing do
  motor.
- **Editar uma célula pelo TunerStudio agora custa ~3,3ms** por byte
  alterado (antes: instantâneo em RAM, só persistia na EEPROM ao apertar
  "Burn"). Só acontece durante tuning ao vivo, não com o motor rodando -
  mas muda a sensação de arrastar uma célula no editor de tabela.
- **Primeiro boot com EEPROM virgem**: grava até 288 bytes (12×12×2
  tabelas) - até **~0,95 s de atraso**, uma vez só.

### Etapa 4 - `Serial` do core Arduino, buffers 16/16

- Objeto `Serial` do core tinha buffers RX/TX internos de 64+64 bytes por
  padrão. Reduzidos para 16/16 via
  `-DSERIAL_TX_BUFFER_SIZE=16 -DSERIAL_RX_BUFFER_SIZE=16`.
- **Exigiu criar `platformio.ini`** (não existia antes, só nesta branch) -
  a Arduino IDE injeta `#include <Arduino.h>` como a primeira linha do
  `.ino` automaticamente, antes de qualquer `#define` do projeto; não tem
  como um `#define` do repositório vencer essa corrida. PlatformIO
  recompila o core por projeto, então os `build_flags` chegam a tempo.
- Validado recompilando o core AVR manualmente com as mesmas flags e
  linkando contra ele (não rodei `pio run` de verdade, já que `pio` está
  quebrado nesta máquina).
- `board_config.h`: corrigido de brinde - `#define BOARD_SLOWDUINO`
  incondicional virou `#ifndef BOARD_SPEEDUINO_V04 #define BOARD_SLOWDUINO
  #endif`, pra `-DBOARD_SPEEDUINO_V04` do `platformio.ini` funcionar sem
  deixar as duas placas definidas ao mesmo tempo.

### Etapa 5 - `serialBuffer` próprio (comms.cpp) 64→24 bytes

- Buffer de montagem do protocolo (diferente do buffer interno do `Serial`
  acima). Também removida uma segunda definição duplicada e idêntica de
  `SERIAL_BUFFER_SIZE` que existia em `comms.h`.
- Tradeoff: payload máximo do protocolo moderno cai de 58 para 18 bytes
  (`SERIAL_BUFFER_SIZE - 6`). Mensagens maiores são rejeitadas com segurança
  (há checagem explícita em `commsProcess()`, sem risco de overflow), mas a
  ferramenta de tuning precisa enviar chunk-writes de tabela em pedaços de
  até 18 bytes.

### Etapa 6 - Varredura de campos mortos

Script Python: para cada campo de `currentStatus`/`ConfigPage1`/
`ConfigPage2`, verifica se **toda** ocorrência no projeto é uma atribuição
simples (`campo = valor;` ou `campo++`) - se sim, o campo nunca é lido por
nenhum cálculo.

**Cuidado que quase deu errado:** a primeira versão do script só olhava
`*.cpp`/`*.h`, ignorando o `.ino` - quase apagou `primePulse`, que É usado
de verdade em `slowduino.ino:236-237`. Corrigido antes de remover qualquer
coisa. Também precisei tratar o padrão `campo++` (incremento), não só `=`.

Removidos (todos confirmados manualmente, não só pelo script):

- **`currentStatus`** (-12 B): `RPMdiv100` (escrito 5x em `decoders.cpp`,
  nunca lido - comentário dizia "para economia de cálculo" mas a economia
  nunca era consumida), `loopCount` (zero leituras), `ignitionCount` (só
  incrementado), `aseCorrection`/`aeCorrection`/`cltCorrection` (escritos em
  `fuel.cpp`, nunca lidos - diferente de `wueCorrection`/`batCorrection`,
  que ficaram porque `comms.cpp` os envia no datalog), `egoCorrection`
  (zero usos).
- **`ConfigPage1`** (-18 B): `injectorLayout`, `divider`, `mapSample`,
  `aeTime`, `stoich`, e o cluster inteiro `egoType`..`egoHysteresis` (13
  campos). **Achado maior que RAM: o closed-loop de O2 (EGO) não tem
  nenhuma linha de código implementada** (`grep -i ego fuel.cpp
  sensors.cpp` não acha nada), apesar de `docs/specifications.md` descrever
  "Simple EGO algorithm". Presente também na `main`, não corrigido lá.
- **`ConfigPage2`** (-4 B): `triggerAngle` (nunca lido pelo decoder),
  `idleAdvance`/`idleRPM` (legado, já sabido morto desde a reescrita do
  idle advance), `engineProtectCutType` (`protectionRPMActive()`/
  `protectionOilActive()`, que o leriam, nunca são chamadas por ninguém).
- De brinde: dois blocos de `loadDefaults()` estavam **duplicados
  exatamente** (EGO+proteção de óleo, proteção do motor) - removida a
  duplicata (comportamento idempotente, sem mudança funcional).

`sizeof(ConfigPage1)` 52→34, `sizeof(ConfigPage2)` 68→64. `static_assert`
atualizados, offsets de EEPROM recalculados, `EEPROM_DATA_VERSION` 5→6.

### Etapa 7 - Tipos estreitados (achados da análise diferencial)

Três variáveis guardavam menos informação do que o tipo declarado permitia -
achado ao comparar com o MS1, que usa `ASEcount` de 8 bits pro mesmo
propósito que o Slowduino usava `uint16_t`. Cada uma exigiu cuidado
diferente pra não introduzir bug de truncamento:

- **`aseCounter`/`aseValue`** (`fuel.cpp`): `uint16_t`→`uint8_t`. Seguro
  direto - só espelham `configPage1.aseCount`/`asePct`, que já são
  `uint8_t`. **-2 B**.
- **`expectedLength`** (`comms.cpp`): `uint16_t`→`uint8_t`. **Não é só trocar
  o tipo** - o parse do header (`(serialBuffer[0]<<8)|serialBuffer[1]`)
  pode gerar um valor de até 65535 se alguém mandar lixo pela serial, e
  gravar isso direto numa variável de 8 bits trunca ANTES da checagem de
  tamanho (`> SERIAL_BUFFER_SIZE-6`) rodar - um valor grande demais podia
  truncar pra algo pequeno e passar pela validação por engano. Corrigido
  fazendo o parse num `uint16_t` local (`parsedLength`), validando esse
  valor largo, e só depois gravando em `expectedLength` (já garantido
  menor que o buffer). **-1 B**.
- **`idleIntegral`** (`auxiliaries.cpp`): `int32_t`→`int16_t`. Risco maior
  ainda - o valor final clampado (`IDLE_INTEGRAL_LIMIT=25600`) cabe
  tranquilo em `int16_t` (±32767), mas o passo de soma
  `idleKI(até 255) * err10(até ~800)` sozinho pode passar de 200000 **antes**
  do clamp - se a soma fosse feita direto num `int16_t`, estouraria no
  meio da conta, não só no armazenamento final. Corrigido calculando a soma
  num `int32_t` local (`idleIntegralWide`) dentro de `idleControl()`,
  clampando esse valor largo, e só gravando o resultado (já dentro do
  limite) de volta no acumulador de 16 bits. **-2 B**.

Medido: 626 → 620 B (a soma exata das reduções de tipo dá 5 B; o resultado
medido foi 6 B, provavelmente alinhamento/padding - não investigado a
fundo, mas o número real é o medido).

**Aplicável na `main`?** Sim, os três - nenhum depende de nada específico
da `ms1`:
- `aseCounter`/`aseValue` são `static` locais de `fuel.cpp`, não fazem parte
  de nenhuma struct exposta por protocolo - zero risco de compatibilidade.
- `expectedLength` é seguro em qualquer tamanho de `SERIAL_BUFFER_SIZE`
  (inclusive o `64` da `main`, já que `64-6=58` cabe em `uint8_t` do mesmo
  jeito) - a lógica de parse-antes-de-truncar é o que importa, não o
  tamanho do buffer.
- `idleIntegral` é código do controle de marcha lenta que já existia na
  `main` antes desta branch existir (mesmo arquivo, mesma lógica) - a
  mesma análise de faixa de valores se aplica igual.

Nenhum desses três muda tamanho de página do protocolo, offset de EEPROM,
ou qualquer coisa que a `main` precise preservar. São correções de
"tipo largo demais pro que a variável guarda", isoladas, sem efeito
colateral em outro lugar do código.

---

## Parte 3: Estado detalhado da RAM hoje (620 B)

Via `avr-nm --size-sort -td`, maiores itens:

| Item | Tamanho |
|---|---:|
| `configPage2` | 64 B |
| `Serial` (core, buffers 16/16) | 61 B |
| `currentStatus` | 61 B |
| `veTable` / `ignTable` (só eixos+cache) | 46 B cada (92 B) |
| `triggerState` | 44 B |
| `configPage1` | 34 B |
| `serialBuffer` | 24 B |
| `injector1/2/3Polling` | 10 B cada (30 B) |
| `ignitionSchedule1/2` | 9 B cada (18 B) |
| resto (contadores, flags, timers do core) | ~180 B |

---

## Próximo passo obrigatório (o que fecha os 108 bytes que faltam)

Os pequenos ganhos de tipo (Etapa 7 acima) já foram aplicados. Não sobrou
mais nenhum candidato de estreitamento de tipo óbvio identificado até agora
- o resto do "resto" (~180 B) é majoritariamente timestamps de `millis()`
(`uint32_t`, genuinamente precisam de 32 bits) e variáveis do próprio core
Arduino (`timer0_millis`, `timer0_overflow_count`), fora de alcance sem
mexer no core.

### O item grande que falta: `configPage1`+`configPage2` via streaming de EEPROM (98 B)

Mesma técnica da Etapa 3, mas para as config pages. Tecnicamente viável -
leitura de EEPROM é barata - mas o raio de ação é muito maior:

- Os campos de tabela eram acessados só por ~5 pontos centralizados
  (`getTableValue`, os 4 handlers de página em `comms.cpp`).
- Os campos de config (`configPage1.reqFuel`, `configPage2.idleKP`, etc.)
  são acessados **por nome, em dezenas de lugares** espalhados por
  `fuel.cpp`, `ignition.cpp`, `sensors.cpp`, `auxiliaries.cpp`,
  `protections.cpp`.
- O mecanismo genérico de leitura/escrita de página do `comms.cpp`
  (`readStructPageByte`/`writeStructPageByte`) depende de `configPage1`/`2`
  serem structs reais em RAM (usa `sizeof()` e aritmética de ponteiro
  diretamente sobre elas) - precisaria ser reescrito também.
- Risco real de errar um offset em algum dos campos e não ter como validar
  sem bancada de hardware (nada disso foi testado em motor real até agora -
  só compilação/link/medição de símbolos).

**Mesmo aplicando isso inteiro, ainda não fecha sozinho:**
`620 - 98 (config streaming) = 522 B` - ainda 10 B acima de 512. Precisaria
combinar com mais alguma coisa, ex:
- `Serial` 16/16 → 8/8: não testado se a lógica de wrap do ring buffer do
  core aceita esse tamanho; se aceitar, algo como -16 B (não medido).
- Mais corte no `serialBuffer` (24→16?): aperta ainda mais o payload
  máximo do protocolo (já em 18 B).

### Itens revisados e NÃO tocados (por quê)

- `triggerState` (44 B) - estado de decoder tocado por ISR em tempo real
  (timestamps `uint32_t` de `micros()`, contadores de dente, gaps). Todos
  os campos pareceram genuinamente necessários na inspeção feita; não achei
  candidato óbvio de estreitamento sem revisão mais profunda do decoder.
- `injector1/2/3Polling`, `ignitionSchedule1/2` (48 B) - estado do
  scheduler de tempo real; não auditado a fundo por risco.

---

## Compatibilidade quebrada nesta branch (de propósito, documentar sempre que for usar)

- Páginas 2/3 do protocolo TunerStudio (tabelas): 168 B, não 288.
- Páginas 1/4 (config): 34/64 B, não 128.
- Chunk-writes de tabela: até 18 B por vez, não os ~256 B que o TunerStudio
  costuma usar por padrão.
- Precisa de `.ini` próprio (o Slowduino não versiona nenhum `.ini` no
  repositório, então isso é "só" um risco de quem já tenha um customizado
  fora do repo) e de configurar o tamanho de chunk na ferramenta de tuning.
- **Nada disso foi validado em hardware real** - só compilação, link e
  inspeção de símbolos (`avr-nm`/`avr-size`). Antes de considerar isso pra
  qualquer uso sério, precisa testar num motor/bancada de verdade,
  especialmente o comportamento de tuning ao vivo com a escrita de EEPROM
  mais lenta (~3,3ms/byte).

## O que NÃO deve ir para a `main` (decisão já tomada, ver conversa anterior)

- Tabelas 16×16→12×12 e o streaming de tabelas por EEPROM: tied à meta de
  RAM desta branch, reduz precisão de tuning e/ou muda a sensação de
  edição ao vivo. Não é para a `main`.
- `spare[]` removido, buffers de `Serial`/`serialBuffer` reduzidos,
  `platformio.ini`: idem, específico do aperto de RAM.
- **Já levado para a `main`** (commit `0007e43`, "Corrige seleção de placa
  por build flag e remove código morto"): fix do `board_config.h`, os 3
  tipos estreitados da Etapa 7, e a varredura de campos mortos de
  `currentStatus`+`ConfigPage1`/`2` - esta última mantendo `ConfigPage1`/`2`
  em exatamente 128/128 bytes (`spare[76]→94`, `spare[60]→64`) em vez de
  encolher a struct como na `ms1`. Resultado real medido na `main`:
  **1464B → 1446B de RAM (-18B)**, flash 21992B → 21740B (-252B).
  `EEPROM_DATA_VERSION` 4→5.
- **Ainda pendente, não levado:**
  - Decidir: apagar o scaffolding morto do EGO/proteção de motor (já feito,
    a remoção) ou **implementar de verdade** o que eles prometiam
    (closed-loop de O2 e fuel/spark-cut seletivo) como um passo separado -
    não presumido, é escolha de produto.
  - O bug do `decrementASE()` nunca chamado (ASE não decai) - ainda não
    investigado/corrigido na `main`.
    troca de tipo.

---

## Como continuar (próxima sessão)

1. Decidir se vale a pena aplicar os ~5 bytes de ganho pequeno primeiro
   (rápido, baixo risco) antes de decidir sobre o item grande.
2. Se for tentar fechar os 512 B: a única rota realista é reescrever o
   acesso a `configPage1`/`configPage2` para streaming por EEPROM, igual
   foi feito com as tabelas - aceitar o raio de ação maior (dezenas de
   pontos de acesso em 5 arquivos) e o risco de não conseguir validar sem
   bancada.
3. Se quiser continuar a análise diferencial MS1×Slowduino em vez de ir
   direto pra reescrita: próximas rotinas óbvias a comparar são Ignição
   (avanço) e Idle - a metodologia usada (contar instruções reais no
   `.asm`, separar RAM "dedicada" de "compartilhada", medir o Slowduino via
   `avr-nm --size-sort -td`) já está validada nas duas rotinas feitas
   (Warmup/ASE e Fuel Calc).
4. Se algum dia conseguir rodar o `CASM08Z.EXE` de verdade (via `wine` num
   terminal, numa sessão gráfica real): gerar um `.map`/listagem com
   endereços por rotina permitiria confirmar os números contados à mão e
   ir além (achar mais candidatos de "RAM dedicada vs compartilhada" com
   precisão de binário em vez de leitura manual do fonte).
