# Tabela de substituição: do Speeduino (GPL) para um núcleo MIT

> Documento de planejamento. **Não é parecer jurídico**: a classificação de
> cada peça abaixo é uma estimativa feita lendo headers e estrutura, e precisa
> ser confirmada pela auditoria (ver "Como auditar").

## Objetivo

Evoluir para um núcleo comum com interfaces estáveis, em que cada peça do
Speeduino/speeduinoMinus (GPL) possa ser trocada por uma implementação própria
(MIT). Quando uma build não incluir nenhuma peça GPL, ela pode incluir módulos
proprietários. Enquanto incluir, o binário inteiro é GPL.

## Regras

1. Um binário que liga qualquer módulo GPL é distribuído sob GPL, com fonte.
2. Módulos proprietários só entram em builds com **zero** peças GPL.
3. O núcleo e as interfaces são escritos do zero, sem copiar estrutura de
   arquivos do Speeduino.
4. Repositórios separados: núcleo (MIT), Slowduino (MIT), adaptador/Minus (GPL),
   módulos proprietários.

## Legenda de estado

| Estado | Significado |
|---|---|
| **A auditar** | Escrita pelo autor do Slowduino, mas não foi verificada contra o código do Speeduino |
| **Suspeita** | Tem indício de derivação (formato, tabela ou arquivo que segue o Speeduino) |
| **Não existe** | Slowduino não tem equivalente; a peça GPL seria a única opção hoje |
| **GPL** | Peça do Speeduino/Minus, fora do alvo MIT |

Nenhuma peça está marcada como "limpa" ainda: isso só acontece depois da
auditoria. O `LICENSE` do Slowduino é MIT (2025), mas os arquivos-fonte não
têm cabeçalho de licença e vários mencionam "Speeduino"
(`auxiliaries.h`, `board_config.h`, `comms.*`, `globals.h`, `config.h`,
`storage.cpp`, `slowduino.ino`).

## Tabela por camada

### Camada 1: folhas (sem dependência entre si, fáceis de testar)

| Peça | Hoje no Speeduino/Minus | Equivalente no Slowduino | Estado | Observações |
|---|---|---|---|---|
| Board (pinos, init, reset, RAM livre) | `boards/board_*`, `board_definition.h` | `src/boards/` (`board.h` + um header por placa + `.cpp` por arquitetura) | A auditar | Camada separada em 2026-11-12; interface nova no núcleo; pinagem da Speeduino v0.4 é fato de hardware, mas o arquivo atual cita o Speeduino |
| Sensores (ADC, filtros, calibração) | `engine/sensors.cpp` | `sensors.cpp/.h` (IIR) | A auditar | Tabelas de calibração CLT/IAT: conferir origem |
| Ventoinha e bomba | `engine/auxiliaries.cpp` | `auxiliaries.cpp` | A auditar | Lógica simples (histerese, priming) |
| Controle de marcha lenta (IAC) | `engine/idle.cpp` | `auxiliaries.cpp` (PWM em software, PID inteiro) | A auditar | PID e taper escritos para o Slowduino; conferir contra o fluxo do `idle.cpp` |
| Proteções (RPM, óleo) | `modules/engine_protection` | `protections.cpp` | A auditar | |
| Storage (EEPROM, páginas, CRC de página) | `storage/*` | `storage.cpp` | Suspeita | `storage.cpp` cita Speeduino; layout de páginas segue o dele |

### Camada 2: base de cálculo

| Peça | Hoje no Speeduino/Minus | Equivalente no Slowduino | Estado | Observações |
|---|---|---|---|---|
| Tabela 3D e interpolação | `support/table3d*` | `tables.cpp/.h` (16×16 na `main`) | A auditar | Alvo: `Table3D<N>`. 16×16 já cabe no Uno na `main` (RAM ~71%); tamanho menor só para a build `tiny` (meta 512 bytes) |
| Tabela 2D / curvas | `support/table2d*` | `tables.cpp` | A auditar | |
| Matemática inteira (utilitários) | `support/maths.*`, `utilities.*` | `globals.h` (`fastMap`, macros) | A auditar | |

### Camada 3: protocolo e ferramentas do tuner

| Peça | Hoje no Speeduino/Minus | Equivalente no Slowduino | Estado | Observações |
|---|---|---|---|---|
| Servidor de protocolo (legado e moderno) | `comms/*` | `comms.cpp/.h` | Suspeita | Comandos, framing e CRC32 padrão são interface funcional; revisar tabela CRC e estrutura de código |
| Mapa de log entries (realtime) | `data/statuses.h`, `logger.*` | `comms.cpp` (`buildRealtimePacket`) | Suspeita | Offsets seguem o Speeduino por compatibilidade com TunerStudio; decidir se manter compatível ou definir mapa próprio |
| Arquivo `.ini` do TunerStudio | `speeduino.ini`, `tools/generate_ini.py` | `tunerstudio/slowduino_202402.ini` | Suspeita | Provável derivado do `speeduino.ini`; alvo: gerar o `.ini` a partir de uma descrição própria de páginas |
| Tamanhos e numeração de páginas | `storage/pages.h` | `comms.cpp` (`getPageSize`) | Suspeita | Pode ser herdado só por compatibilidade |

### Camada 4: timing (núcleo crítico)

| Peça | Hoje no Speeduino/Minus | Equivalente no Slowduino | Estado | Observações |
|---|---|---|---|---|
| Decoders: missing tooth, distribuidor básico | `engine/decoders.cpp`, `decoder_t.h` | `decoders.cpp` | A auditar | Interface nova do núcleo; ordem de implementação a decidir |
| Decoders: demais padrões de roda | idem | não existe | Não existe | Dezenas de padrões no Speeduino; escrever só os que forem necessários |
| Scheduler (ignição e injeção) | `scheduler.h`, `engine/scheduledIO_*` | `scheduler.cpp/.h` | A auditar | Slowduino: Timer1, 2 compares, injeção por polling. Interface comum com 2 implementações |
| Cálculo de ângulos e tempos | `crankMaths.*`, `orchestration/schedule_*` | `decoders.cpp` (`angleToTime`, etc.) | A auditar | |

### Camada 5: injeção e ignição

| Peça | Hoje no Speeduino/Minus | Equivalente no Slowduino | Estado | Observações |
|---|---|---|---|---|
| Cálculo de PW (VE, speed-density, alpha-N) | `engine/fuel_calcs.cpp` | `fuel.cpp` | A auditar | |
| Correções (WUE, ASE, bateria, CLT, IAT) | `engine/corrections.cpp` | `fuel.cpp` | A auditar | Forma das curvas padrão pode vir do Speeduino |
| Enriquecimento de aceleração | `engine/accel_enrichment.cpp` | `fuel.cpp` | A auditar | |
| Avanço e dwell | `engine/dwell.cpp`, `ignition_runtime.*` | `ignition.cpp` | A auditar | |
| Mapas de fábrica (VE, ignição) | `data/fuel_factory_defaults.*` | `config.h` (`PROGMEM`) | Suspeita | Conferir se os valores padrão foram copiados |
| Injeção/ignição sequencial | `orchestration/*`, decoders | não existe | Não existe | Fora do escopo do Uno |

### Camada 6: módulos opcionais

| Módulo | Estado | Observações |
|---|---|---|
| logging, SD logging | GPL / Não existe | Slowduino só faz log via TunerStudio |
| secondary serial, comms extended, CAN | GPL / Não existe | |
| table switching | GPL / Não existe | |
| boost, VVT, WMI, nitro | GPL / Não existe | Slowduino tem um canal auxiliar de injeção (D7) sem lógica |
| knock | GPL / Não existe | |
| launch, flat shift | GPL / Não existe | |
| fan / A/C | GPL | O Slowduino já tem ventoinha; A/C não |
| programmable I/O | GPL / Não existe | |

Para essas peças a decisão é: reescrever só as que forem usadas, ou manter o
adaptador GPL como opção separada para quem as quiser.

## Ordem sugerida

1. Auditoria do Slowduino atual (abaixo) e definição das interfaces do núcleo
   (board, módulo, decoder, scheduler, storage).
2. Camada 1: board, sensores, auxiliares, proteções.
3. Camada 2: `Table3D<N>`, com testes numéricos.
4. Camada 3: protocolo e `.ini` gerado de uma descrição própria.
5. Camada 4 e 5: só com testes de sincronismo e de banco antes de trocar.
6. Camada 6, conforme necessidade.

## Como auditar uma peça

Para cada linha acima, registrar em um arquivo à parte:

- Quem escreveu e quando (histórico do git).
- O que foi consultado como referência (código do Speeduino, `speeduino.ini`,
  documentação, datasheet).
- Se há trechos que coincidem estruturalmente com o Speeduino (nomes de
  funções, ordem de operações, constantes, tabelas).
- Decisão: manter como está, reescrever a partir de especificação, ou marcar
  como derivada.

Ao reescrever uma peça marcada como derivada, escrever primeiro uma
especificação de comportamento e testes, e implementar a partir deles, sem
consultar o código GPL.

## Perguntas em aberto

- Manter compatibilidade com o `speeduino.ini` e com os offsets de realtime
  do Speeduino, ou definir um protocolo próprio com um `.ini` próprio?
- Quais módulos da camada 6 entram no escopo MIT?
- Nome e organização do repositório do núcleo (já existe um `ecu-core` em
  Kotlin em `~/Projects/ecu-core`).
