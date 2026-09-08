# Prompt para retomar: bug de corrupção de execução no Slowduino-HC08 (ucsim)

Cole isto no início da próxima sessão.

## Contexto

Estou validando o port `slowduino_hc08` (SDCC, MC68HC908GP32) rodando no
fork do ucsim em `~/Projects/ucsim` (`ucsim_ms1` wrapper). O objetivo final é
conectar o TunerStudio nesse firmware, igual já funciona 100% com o firmware
MS1 original (`/home/alexandre/Downloads/029y4a/msns-extra.s19`, porta 12000).

Build do Slowduino:
```
cd ~/Projects/slowduino/slowduino_hc08
make clean && make        # gera slowduino_hc08.s19
```

Rodar no simulador:
```
cd ~/Projects/ucsim
MS1_TRIGGER_RPM=800 MS1_TRIGGER_PATTERN=36-1 MS1_TRIGGER_ENABLE=1 MS1_SCI_VERBOSE=1 \
  ./src/sims/m68hc08.src/ucsim_m68hc08 \
  ~/Projects/slowduino/slowduino_hc08/slowduino_hc08.s19 \
  -t HCS08 -X 8000000 -S "uart=0,port=12000,raw" -Z 12001 -g < /dev/null
```
(ou via `./ucsim_ms1 --firmware .../slowduino_hc08.s19 --tcp-port 12000 --rpm 800 --pattern 36-1 --sci-verbose`)

## Bugs já achados e corrigidos nesta investigação (branch `hc908` do slowduino, e branch `master` do ucsim)

Commits do ucsim (`~/Projects/ucsim`, branch master):
- `5888d2cb` até `05dfbe27`: fixes de infraestrutura do simulador (banner SCI, bytes RX perdidos em burst, pino IRQ físico, timers TIM1/TIM2).
- `04b4ff07` **"Run as CPU_HCS08"**: `ucsim_ms1` agora sempre passa `-t HCS08` porque o GP32 real suporta opcodes do superset HCS08 (ex: `LDHX` extended, `0x32`) que o SDCC gera e o core HC08 puro do ucsim rejeitava.

Commits do slowduino (`~/Projects/slowduino`, branch `hc908`):
- `93b062d` **fix de build**: tabela de vetores de interrupção ausente (criei `vectors.s` com `.area CODEIVT (ABS)` + `.org` pra cada vetor - SDCC só gera o vetor de RESET automaticamente) + extensão de saída trocada de `.ihx` pra `.s19` (SDCC gera S-record de verdade, e o ucsim escolhe o parser só pela extensão do arquivo, não pelo conteúdo).
- `9ebaa70` **`__critical` em vez de `noInterrupts()/interrupts()` cru**: o padrão herdado do AVR fazia sei/cli incondicional sem save/restore; dois call sites rodavam de dentro de uma ISR (`micros()` chamado por `triggerPri_MissingTooth`), reabilitando interrupções aninhadas de verdade. Trocado por `__critical { }` (confirmei que o SDCC gera `tpa/sei ... tap` de verdade pra hc08).
- `46ef251` **guarda de divisão por zero**: `triggerSetup_MissingTooth()` fazia `3600 / triggerState.triggerTeeth`, e numa instalação limpa (sem TunerStudio configurar nada, `configPage2` zerado) `triggerTeeth=0`. Adicionei fallback pra 36-1 se vier zero.

## O bug que falta (não resolvido)

Mesmo depois de TODOS os fixes acima, o firmware ainda trava cedo, antes do
`comms.c` conseguir responder qualquer coisa pela serial (SCI recebe o byte,
mas nunca retorna resposta).

**Sintoma exato**: a CPU acaba executando dentro da rotina `__divsint` (divisão
signed 16-bit de biblioteca do SDCC, presente em `hc08.lib`) chamada a partir
de `triggerSetup_MissingTooth()` (endereço da chamada varia por build, ~0x924f
numa build recente) com operandos **3600 / 36** (totalmente normais, nada de
divisão por zero aqui). Depois de ~1300-1500 instruções (mais do que os
16-32 ciclos que uma divisão 16-bit deveria levar), a CPU acaba pulando pra
memória não-linkada (bytes zerados, decodificados como `brset #0,*$00,+3`
repetidamente - um "deserto" de flash vazio) e a partir daí executa lixo até
travar de vez ou ficar girando pra sempre.

**Já testei e ELIMINEI como causa**:
- Não é bug geral do `__divsint` nem do core HC08/HCS08 do ucsim: escrevi um
  programa isolado (`int a=3600,b=36,c; for(;;) c=a/b;`) compilado com as
  MESMAS flags, rodando no MESMO ucsim - funciona perfeitamente, roda pra
  sempre sem corromper nada (~23 milhões de ticks testados).
- `--nooverlay` (desliga reaproveitamento de RAM entre variáveis locais de
  funções folha) não mudou nada - ainda trava.
- Remover `--stack-auto` de vez não é viável: sem ele o DSEG estoura (RAM
  insuficiente), nem builda (`ASlink-Warning-Paged Area DSEG Length Error`).
- Não é interrupção real disparando: `triggerInit()` (que chama a divisão
  problemática) roda em `main()` ANTES da chamada a `interrupts()` (linha 26
  de `main.c`) - ou seja, a CPU ainda está com interrupções globalmente
  desabilitadas nesse ponto exato. Confirmei isso lendo o registrador P
  (CCR) durante o breakpoint.
- Confirmei que o vetor de reset e os 4 vetores de interrupção que a gente
  adicionou (`vectors.s`) estão corretos e resolvidos certinho no `.map`.

**Hipótese não testada ainda**: já que é específico do PROGRAMA COMPLETO e
não reproduz isolado, pode ser:
1. Um bug de alocação de overlay/OSEG mais sutil que `--nooverlay` não cobre
   (talvez precise também de `--no-peep` ou alguma flag de otimização que
   está fazendo o compilador assumir uma coisa errada sobre o call graph).
2. Um bug real de emulação de CPU no ucsim só visível com o LAYOUT DE MEMÓRIA
   específico dessa build maior (por exemplo, um opcode que o `inst.cc` do
   ucsim decodifica com tamanho errado, e que só aparece no meio do código
   de `__divsint` quando ele está posicionado em determinados endereços -
   testar comparando bytes exatos da rotina isolada vs a rotina dentro do
   binário completo, byte a byte, pode revelar se são literalmente idênticas
   ou se há alguma diferença de codegen entre as duas builds).
3. Stack overflow real por profundidade de chamada (mesmo com SP começando
   "raso" nesse ponto - vale conferir o tamanho total dos frames empilhados
   até ali, e se algum array/buffer grande de alguma struct global está de
   alguma forma vazando pra cima do stack).

## Ferramenta de debug que funcionou bem (e a que NÃO funcionou)

**Funciona bem**: uma ÚNICA conexão `nc localhost <porta_Z>` persistente,
mandando vários comandos em sequência com `sleep` entre eles, tudo dentro do
MESMO pipe/processo `nc`, redirecionando pra um arquivo de log e depois
grepando. Reconectar via múltiplas chamadas separadas de `nc` (uma conexão
nova por comando) causa comportamento inconsistente/confuso (estado
"perdido" entre reconexões, provavelmente por causa de como o console do
ucsim lida com múltiplos consoles).

Exemplo de sessão persistente que funcionou bem:
```bash
{
  printf 'break 0xd38c\r\n'; sleep 0.3
  printf 'go\r\n'; sleep 1
  printf 'step 10\r\n'; sleep 0.2
  # ... mais comandos, sempre no mesmo pipe
} | timeout 20 nc localhost <cmd_port> > /tmp/trace.log 2>&1
```

Comandos úteis do console do ucsim (via porta `-Z`):
- `break 0xADDR` / `go` - breakpoint fetch
- `step N` - executa N instruções, mostra registradores completos (só na
  transição de estado "rodando -> parado"; chamar `regs` sozinho depois não
  reimprime o bloco completo)
- `dc START END` - disassembla um range (desconfiar de desalinhamento se o
  PC real não bateu exatamente no START)
- `dump rom START END` - mostra bytes (mas formatados como disassembly, não
  hex puro; dava pra extrair os bytes brutos da coluna do meio)
- Endereço de retorno de uma chamada: está em `memory[SP+1]:memory[SP+2]`
  (big-endian) logo após entrar na função

**Não tive sucesso tentando**: reconectar a cada comando (gera timing/estado
inconsistente), usar `dump` sem o parâmetro `memory_type` (sintaxe errada,
dá resultado sem sentido).

## Arquivos relevantes

- `~/Projects/slowduino/slowduino_hc08/decoders.c` - `triggerSetup_MissingTooth()`,
  `triggerPri_MissingTooth()`, todo o decoder de trigger
- `~/Projects/slowduino/slowduino_hc08/main.c` - ordem de boot
- `~/Projects/slowduino/slowduino_hc08/Makefile` - flags de build (`CFLAGS`)
- `~/Projects/slowduino/slowduino_hc08/vectors.s` - tabela de vetores manual
- `~/Projects/slowduino/slowduino_hc08/slowduino_hc08.map` - símbolos com
  endereços finais (útil pra achar `grep -n "__divsint\b"` etc.)
- `~/Projects/ucsim/src/sims/m68hc08.src/inst.cc` - implementação das
  instruções do CPU (candidato a ter o bug de emulação, se for isso)
- `/tmp/divtest/divtest.c` - o teste isolado que PROVOU que `__divsint`
  sozinho funciona (pode já ter sido limpo do `/tmp` - é só recriar, é
  pequeno, está citado acima)

## Primeiro passo sugerido

Comparar os BYTES exatos de `__divsint` extraídos do binário isolado
(`divtest.s19`) contra os bytes de `__divsint` dentro do
`slowduino_hc08.s19` completo. Se forem idênticos byte a byte, o problema
é de CONTEXTO DE EXECUÇÃO (memória ao redor, stack, etc), não da rotina em
si - aí focar em stack depth e layout de memória ao redor da chamada real.
Se forem DIFERENTES, o problema é de codegen/linking specific dessa build
maior.
