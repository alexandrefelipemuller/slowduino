# Auditoria de licença: `.ini` e `comms.cpp`

> Não é parecer jurídico. É um levantamento técnico de evidências para
> subsidiar a decisão e uma eventual revisão por advogado.
> Data: 2026-11-12. Referência comparada: `~/Projects/speeduino` (GPL).

## Método

1. Comparação de linhas normalizadas (espaços colapsados, sem comentários,
   mais de 20-25 caracteres) contra todo o `speeduino/*.cpp|*.h` e contra
   `speeduino.ini`.
2. Leitura dos pontos onde o código declara ter consultado o Speeduino.
3. Histórico do git dos dois arquivos.

Limite do método: linhas idênticas medem cópia literal. Não medem derivação
estrutural (mesma ordem de operações, mesmos nomes de campos) nem leitura do
código-fonte como referência.

## Resultado geral (cópia literal de linhas)

| Arquivo | Linhas comparadas | Idênticas | % |
|---|---|---|---|
| `comms.cpp` | 444 | 1 (`extern int __heap_start, *__brkval;`, idioma padrão do avr-libc) | 0,2% |
| `comms.h` | 33 | 0 | 0% |
| `fuel.cpp`, `ignition.cpp`, `tables.cpp`, `protections.cpp`, `config.h`, `globals.h` | — | 0 | 0% |
| `storage.cpp` | 224 | 1 (`EEPROM.write(address, value);`) | 0,4% |
| `scheduler.cpp` | 158 | 2 (includes) | 1,3% |
| `sensors.cpp`, `auxiliaries.cpp` | — | 2 cada (atribuições triviais, includes) | <2% |
| `decoders.cpp` | 189 | 11 (includes, `currentStatus.RPM = 0;`, `hasSync = false;`) | 5,8% |
| `slowduino_202402.ini` (versão atual) | 232 | 16 | 6,9% |
| `slowduino_202402.ini` (primeira versão, `ee1b131`) | 252 | 7 | 2,8% |

Leitura: **não há cópia literal relevante em nenhum arquivo de código.** As
coincidências são includes, atribuições triviais e idiomas padrão.

## `.ini`

### O que coincide literalmente (16 linhas)

- `pageSize = 128, 288, 288, ...` (lista de 15 tamanhos de página).
- `pageIdentifier`, `pageReadCommand`, `pageValueWrite`, `pageChunkWrite`,
  `crc32CheckCommand`, `burnCommand`: formato imposto pelo TunerStudio.
- 5 linhas `entry = ...` do `[Datalog]` (`time`, `secl`, `rpm`, `tps`,
  `coolant`) e 4 linhas curtas de eixos/rótulos.

Quase tudo isso é sintaxe exigida pelo TunerStudio ou nome de canal genérico
(`rpm`, `tps`, `coolant`). O risco real não está nas linhas idênticas.

### Evidências de derivação

- O commit `ee1b131` descreve o arquivo como "projeto TunerStudio **adaptado**".
- `[OutputChannels]`: usa os mesmos nomes de canal do Speeduino (`secl`,
  `status1`, `engine`, `egoCorrection`, `iatCorrection`, `wueCorrection`,
  `loopsPerSec`, `freeRAM`, `veCurr`, `CLIdleTarget`...) e os mesmos
  offsets (0, 7, 14, 24, 25, 38, 76, 92, 102...). Formatação, unidades e
  escalas não são idênticas linha a linha.
- Os 15 tamanhos de página repetem a lista do Speeduino, incluindo páginas
  que o firmware não implementa (stubs).
- A lista de seções e a ordem seguem o formato padrão do TunerStudio.

### Inconsistência encontrada (não é de licença, mas importa)

O cabeçalho do `.ini` diz que o firmware se identifica como
`slowduino 202402` "para nunca ser confundido com o Speeduino". Mas o
`signature` do próprio `.ini` e as respostas `Q/S/I` do firmware
(`comms.cpp` linhas 286, 339, 343, 442, 460, 478) são todas
`"speeduino 202402(s)"`. O comentário em `comms.cpp:441` ("Assinatura própria
do Slowduino, não colide") também está desatualizado. O commit `8b035e0`
parece ter revertido a assinatura própria.

### Classificação

**Suspeita, risco médio.** Não há cópia literal de conteúdo. Mas o arquivo foi
construído a partir do `speeduino.ini` (nomes de canal, offsets, tamanhos de
página). Esses itens são em grande parte **interface de compatibilidade**
(o TunerStudio exige certos nomes e offsets para os gauges padrão), o que
costuma pesar a favor de uso livre, porém a decisão final é jurídica.

### Recomendação

1. Gerar o `.ini` a partir de uma descrição própria de páginas e canais
   (script no repositório), e não manter à mão.
2. Decidir se o Slowduino mantém os nomes e offsets do Speeduino por
   compatibilidade (aceitando o risco) ou define um mapa próprio.
3. Corrigir a assinatura: ou usar `slowduino ...` de fato, ou atualizar os
   comentários que dizem o contrário.
4. Reduzir a lista de páginas aos números realmente implementados.

## `comms.cpp`

### Cópia literal

Praticamente nenhuma (1 linha em 444).

### Tabela CRC32

A tabela é a de CRC-32 IEEE 802.3 (polinômio refletido `0xEDB88320`). O
conteúdo é determinado pela matemática. O Speeduino usa a biblioteca FastCRC,
que está sob licença MIT (`src/FastCRC/LICENCE.md`), então não há conflito.
**Sem risco identificado.**

### Evidências de consulta ao código do Speeduino

- Comentário em `comms.cpp:390`: "Estrutura real da Speeduino
  (`generateLiveValues` em `comms.cpp`)".
- Comentário em `comms.cpp:550`: "Speeduino real usa `payload[2]`".
- Constantes `SPEEDUINO_TABLE_DIM`, `SPEEDUINO_TABLE_PAGE_SIZE` com
  `static_assert` de "compatibilidade Speeduino".
- Tabela `pageSize[]` com 16 entradas comentadas com os papéis das páginas
  do Speeduino (`Seq fuel trims`, `WMI / aux maps`, `Programmable outputs`).
- Cabeçalho e histórico: arquivo criado em `7c8c4c3` (2025-11-05) e depois
  corrigido várias vezes para casar com o comportamento do Speeduino.

Isso mostra que o autor leu o código do Speeduino como referência para o
comportamento. Não prova cópia, mas **quebra a premissa de "sala limpa"**:
uma reescrita feita a partir da especificação teria registro de que o código
GPL não foi consultado.

### Classificação

**A auditar, risco baixo a médio.** Código estruturalmente diferente (um
único arquivo com `switch`, contra vários arquivos no Speeduino), sem trechos
idênticos. O risco vem do fluxo de trabalho (consulta ao GPL) e das
constantes de layout de páginas.

### Recomendação

1. Escrever uma especificação do protocolo (comandos, framing, tamanhos de
   resposta) a partir de **observação do tráfego** com o TunerStudio, e não
   do código do Speeduino. Dar a isso um documento em `docs/`.
2. Mover o layout das páginas e dos canais de realtime para uma descrição de
   dados única, da qual saem o `comms` e o `.ini`.
3. Remover os comentários que citam funções do Speeduino por nome.
4. Para a futura reescrita limpa do núcleo, quem escreve não deve consultar
   o código do Speeduino durante a escrita.

## Correção a um erro anterior

Na conversa eu disse que a `main` usa tabelas 8×8 de 72 bytes, com base no
`CLAUDE.md`. **Estava errado.** `config.h` define `TABLE_SIZE_X/Y = 16` e
`comms.cpp` tem `static_assert` exigindo 16×16. O `CLAUDE.md` está
desatualizado nesse ponto (e a tabela de substituição tinha o mesmo erro).

Consequência para a pergunta "16×16 cabe no Uno?": **cabe**, na `main` já
cabe (RAM em ~1464 de 2048 bytes, 71,5%, segundo as notas). O que não cabe é
a meta de 512 bytes da branch `ms1`/`tiny` com tabelas 16×16 residentes em
RAM. Isso muda o plano de `Table3D<N>`: o padrão seria 16×16, e o menor
tamanho seria uma opção para a build `tiny`.

## Próximos passos sugeridos

1. Decidir o item 2 do `.ini` (manter nomes e offsets do Speeduino ou não).
2. Corrigir a assinatura e os comentários desatualizados.
3. Auditar `decoders.cpp` e `storage.cpp` (os outros com `speeduino` no
   texto e os maiores).
4. Atualizar o `CLAUDE.md` (tabelas 16×16).
