# Memória do Projeto - Slowduino

## 📱 Visão Geral
- **Tipo:** ECU minimalista para motores 1-4 cilindros
- **Hardware:** ATmega328p (Arduino Uno/Nano)
- **Limitações:** 32KB Flash, 2KB RAM, 1KB EEPROM
- **Linguagem:** C++ (Arduino)
- **Arquitetura:** ISR-driven, offline-first, integer-only
- **Inspiração:** Speeduino (protocolo compatível com TunerStudio)
- **Versão:** 0.2.0 (com auxiliares)

## 🎯 Objetivos do Projeto

Criar uma ECU funcional que:
- ✅ Controla injeção (wasted paired, 2 canais para 4 cilindros)
- ✅ Controla ignição (wasted spark, 2 canais)
- ✅ Lê sensores (MAP, TPS, CLT, IAT, O2, Battery, Oil Press, Fuel Press)
- ✅ Decodifica trigger wheels (Missing Tooth 36-1/60-2, Basic Distributor)
- ✅ Comunica com TunerStudio via serial (Legacy + Modern protocol)
- ✅ Usa tabelas 3D (8×8) com interpolação bilinear
- ✅ Aplica correções (WUE, ASE, AE, CLT, Battery)
- ✅ Agendamento em tempo real via ISR direta
- ✅ Controla auxiliares (ventoinha, IAC, bomba combustível)

## 🏗️ Estrutura de Arquivos

### Arquivos Core
```
slowduino.ino          - Loop principal e setup
globals.h/cpp          - Estruturas de dados e variáveis globais
config.h               - Constantes, defaults, PROGMEM tables
```

### Subsistemas
```
storage.h/cpp          - Persistência EEPROM
tables.h/cpp           - Tabelas 3D (8×8) com interpolação bilinear
sensors.h/cpp          - Leitura ADC com filtros IIR
decoders.h/cpp         - Trigger decoders + ISR scheduling
fuel.h/cpp             - Cálculo de injeção e correções
ignition.h/cpp         - Cálculo de avanço e dwell
scheduler.h/cpp        - Timer1 para eventos de injeção/ignição
comms.h/cpp            - Protocolo Speeduino (TunerStudio)
auxiliaries.h/cpp      - Controle de ventoinha, IAC e bomba
```

## 🔧 Conceitos Críticos

### 1. ISR-Driven Scheduling (CRÍTICO!)

**Paradigma:** Agendamento acontece DIRETAMENTE na ISR do trigger, não no loop!

**Como funciona:**
```cpp
// decoders.cpp - ISR do trigger
void triggerPri_MissingTooth() {
  // Detecta gap (dente faltante)
  if (gap_encontrado) {
    // *** AGENDAMENTO DIRETO NA ISR ***
    scheduleInjectionISR();  // inline function
    scheduleIgnitionISR();   // inline function
  }
}

// Funções inline com __attribute__((always_inline))
inline void scheduleInjectionISR() {
  uint32_t timeToInjection = (INJECTION_ANGLE * revolutionTime) / 360;
  uint16_t pw = currentStatus.PW1;
  setFuelSchedule(&fuelSchedule1, timeToInjection, pw, 1);
}
```

**Por quê ISR direta?**
- ❌ Loop-based tem latência (pode perder timing crítico)
- ✅ ISR direta = zero latência, precisão máxima
- ✅ Scheduler usa Timer1 para precisão de 0.5µs

### 2. Wasted Paired Injection/Ignition

**Conceito:** 1 canal controla 2 cilindros simultaneamente

**Injeção:**
- Canal 1 (PIN_INJECTOR_1) → Cilindros 1 + 4
- Canal 2 (PIN_INJECTOR_2) → Cilindros 2 + 3
- Ambos injetam na mesma quantidade (PW1 = PW2)
- Alternância via `revolutionCounter` (0 ou 1)

**Ignição:**
- Canal 1 (PIN_IGNITION_1) → Cilindros 1 + 4
- Canal 2 (PIN_IGNITION_2) → Cilindros 2 + 3
- Mesmos timing de avanço e dwell

### 3. Trigger Decoders

**Missing Tooth (36-1, 60-2):**
- Detecta gap (dente faltante) para sincronizar
- Gap = ~2x maior que dente normal
- Threshold: `curGap > lastGap + (lastGap >> 1)` (1.5x)
- Valida contagem de dentes para confirmar sync
- Reseta `toothCurrentCount` no gap

**Basic Distributor:**
- 1 pulso = 1 revolução completa
- Sincronização imediata (sem gap detection)
- Mais simples, menos preciso

### 4. Timer1 Scheduler

**Configuração:**
- Modo CTC, prescaler 8
- Resolução: 0.5µs por tick (16MHz / 8)
- Compare Match A/B para 2 canais simultâneos

**Estados:**
```cpp
enum ScheduleStatus {
  SCHED_OFF,      // Inativo
  SCHED_PENDING,  // Agendado, aguardando
  SCHED_RUNNING   // Executando (injetor aberto/bobina carregando)
};
```

**ISR flow:**
```cpp
ISR(TIMER1_COMPA_vect) {
  if (fuelSchedule1.status == PENDING) {
    openInjector1();
    fuelSchedule1.status = RUNNING;
    OCR1A = endCompare; // Reagenda para fechar
  } else if (fuelSchedule1.status == RUNNING) {
    closeInjector1();
    fuelSchedule1.status = OFF;
  }
}
```

### 5. Protocolo Speeduino

**PRIORIDADE MÁXIMA** - user explicitamente solicitou

**Dual Protocol Support:**
- **Legacy:** ASCII single-byte commands ('A', 'Q', 'S', etc)
- **Modern:** Binary + CRC32 validation

**Auto-detection:**
```cpp
void commsProcess() {
  if (Serial.available()) {
    uint8_t cmd = Serial.peek();
    if (cmd >= 'A' && cmd <= 'z') {
      processLegacyCommand(Serial.read());
    } else {
      processModernCommand();
    }
  }
}
```

**Realtime Data Packet (127 bytes):**
```
[0]: secl
[7]: coolant+40
[14-15]: RPM (little-endian uint16)
[24]: advance+40
[25]: TPS
[76-77]: PW1 (little-endian uint16)
...
```

**Endianness:**
- Little-endian: offsets, lengths, data fields
- Big-endian: CRC32 apenas

**CRC32:**
- Algoritmo padrão (FastCRC32 compatible)
- Lookup table em PROGMEM (256 entradas)
- Envia: `sendU32BE(crc)`

## 📂 Estruturas de Dados

### currentStatus (RAM)
```cpp
struct Statuses {
  uint16_t RPM, PW1, PW2, dwell;
  uint8_t MAP, TPS, VE;
  int8_t coolant, IAT, advance;
  uint8_t battery10, O2;
  bool hasSync;
  uint32_t secl, runSecs, loopCount;
  // ... correções, flags
};
```

### configPage1 (EEPROM, 128 bytes)
```cpp
struct ConfigPage1 {
  uint8_t nCylinders;
  uint16_t reqFuel, injOpen;
  uint8_t tpsMin, tpsMax, tpsFilter;
  uint8_t mapMin, mapMax, mapFilter;
  uint8_t wueBins[6], wueValues[6];  // Warm-Up Enrichment
  uint8_t asePct, aseCount;          // After-Start
  uint8_t aeThresh, aePct, aeTime;   // Accel Enrichment
  uint8_t primePulse;                // ms * 10
  uint8_t crankRPM;
  // ... spare
} __attribute__((packed));
```

### configPage2 (EEPROM, 128 bytes)
```cpp
struct ConfigPage2 {
  uint8_t triggerPattern;     // 0=Missing Tooth, 1=Basic Dist
  uint8_t triggerTeeth;       // ex: 36
  uint8_t triggerMissing;     // ex: 1 (36-1)
  uint8_t triggerAngle;
  uint8_t dwellMode;          // 0=Fixed, 1=Variable
  uint16_t dwellFixed;        // us
  uint8_t dwellRPMBins[4], dwellValues[4];
  bool ignInvert;             // Inversão de polaridade
  // ... spare
} __attribute__((packed));
```

### Table3D (RAM, 72 bytes cada)
```cpp
struct Table3D {
  union {
    uint8_t valuesU[8][8];  // Unsigned (VE)
    int8_t valuesI[8][8];   // Signed (Advance)
  };
  uint16_t axisX[8];  // RPM (bins)
  uint8_t axisY[8];   // MAP (bins)
  bool isSigned;
};
```

## 🎮 Mapeamento de Pinos

**⚠️ IMPORTANTE:** Arduino Uno/Nano só tem interrupções em D2 e D3!
- INT0 → Pino D2
- INT1 → Pino D3

```cpp
// Trigger inputs (CRÍTICO: PRECISA de INT0/INT1!)
#define PIN_TRIGGER_PRIMARY   2  // D2 - INT0 (roda fônica) ⚡
#define PIN_TRIGGER_SECONDARY 3  // D3 - INT1 (cam - futuro) ⚡

// Saídas (Arduino Uno/Nano)
#define PIN_IGNITION_1     4   // D4 - Bobinas 1+4
#define PIN_IGNITION_2     5   // D5 - Bobinas 2+3
#define PIN_FUEL_PUMP      6   // D6 - Relé bomba combustível
#define PIN_FAN            8   // D8 - Relé ventoinha radiador
#define PIN_IDLE_VALVE     9   // D9 - Válvula marcha lenta (PWM)
#define PIN_INJECTOR_1    10   // D10 - Injetores 1+4
#define PIN_INJECTOR_2    11   // D11 - Injetores 2+3

// Outras entradas digitais
#define PIN_VSS           12   // D12 - Velocidade do veículo
#define PIN_SPARE_1        7   // D7 - Reserva

// Sensores ADC
#define PIN_CLT             A0  // Temperatura motor (NTC)
#define PIN_IAT             A1  // Temperatura ar (NTC)
#define PIN_MAP             A2  // Pressão coletor
#define PIN_TPS             A3  // Posição borboleta
#define PIN_O2              A4  // Sonda Lambda
#define PIN_BATTERY         A5  // Tensão bateria
#define PIN_OIL_PRESSURE    A6  // Pressão óleo (0-5V = 0-1000 kPa)
#define PIN_FUEL_PRESSURE   A7  // Pressão combustível (0-5V = 0-1000 kPa)
```

## 🔌 Sistema de Auxiliares (v0.2)

### Controle de Ventoinha (Fan Control)

**Implementação:** digitalWrite() simples com histerese

**Lógica:**
```cpp
if (coolant >= 95°C) FAN_ON();
if (coolant <= 90°C) FAN_OFF();
// Entre 90-95°C: mantém estado (histerese)
```

**Por quê simples?**
- Não precisa de PWM (relé on/off)
- Histerese evita liga/desliga rápido
- Executado a 4Hz (250ms) é suficiente

### Bomba de Combustível (Fuel Pump)

**Implementação:** digitalWrite() com controle de estado

**Fases:**
1. **Priming:** Liga por 2s ao boot
2. **Operação:** Liga se RPM > 0 ou cranking
3. **Timeout:** Desliga 1s após motor parar

**Segurança:** Se motor parar sem desligar ignição, bomba desliga automaticamente

### Válvula de Marcha Lenta (IAC)

**Implementação:** analogWrite() PWM no pino D9

**Controle proporcional simples:**
```cpp
int16_t erro = 850 - RPM;  // Alvo 850 RPM
if (abs(erro) > 50) {      // Deadband ±50 RPM
  if (erro > 0) duty += 2%; // RPM baixo: abre mais
  else duty -= 2%;           // RPM alto: fecha
}
```

**Limites:**
- TPS < 5% (só atua em idle)
- CLT > 60°C (motor aquecido)
- Duty 0-100%

**Por quê não PID?**
- RAM limitada
- Resposta lenta ok em idle
- Simples de entender e ajustar

### Sensores de Pressão

**Pressão de óleo e combustível:**
- Sensores típicos: 0-5V = 0-1000 kPa
- Armazenado em uint8_t (0-250, multiplicar por 4 para kPa real)
- Filtro IIR médio (α=100)
- Lidos a 4Hz junto com CLT/IAT

**Uso:**
- Monitoramento/alerta (futuro)
- Datalog
- Não afetam cálculos de injeção/ignição

## 📊 Decisões Técnicas

### 1. Tabelas 8×8 (não 16×16)
**Razão:** Economia de RAM
- 16×16 = 256 bytes por tabela × 2 = 512 bytes
- 8×8 = 64 bytes × 2 = 128 bytes
- **Economia: 384 bytes (~19% da RAM total!)**

### 2. Integer-Only Math
**Razão:** Performance e tamanho de código
- Sem biblioteca float (~2KB Flash!)
- Aritmética inteira é 10-100x mais rápida
- Usa shifts (`>> 1` = div por 2) sempre que possível

### 3. PROGMEM para Dados Constantes
**Razão:** RAM é escassa, Flash tem espaço
```cpp
const uint8_t defaultVETable[8][8] PROGMEM = { ... };
const uint32_t crc32_table[256] PROGMEM = { ... };

// Leitura:
uint8_t value = pgm_read_byte(&defaultVETable[x][y]);
```

### 4. Inline ISR Functions
**Razão:** Eliminar overhead de chamada de função
```cpp
inline void scheduleInjectionISR() __attribute__((always_inline));
```

### 5. IIR Digital Filters
**Razão:** Suavização de sensores sem buffer
```cpp
// α = 0.75 (192/256)
newValue = (input * (256 - alpha) + oldValue * alpha) / 256;
```

## 🚫 Regras CRÍTICAS

### NUNCA fazer:
- ❌ Float/double arithmetic (exceto conversão final)
- ❌ Alocação dinâmica (`malloc`, `new`)
- ❌ `String` class do Arduino (usa muita RAM)
- ❌ Blocking delays em ISRs
- ❌ Serial.print() em ISRs
- ❌ Funções longas em ISRs (máx 20µs!)

### SEMPRE fazer:
- ✅ `volatile` para variáveis compartilhadas com ISR
- ✅ `noInterrupts()` / `interrupts()` ao acessar multi-byte vars
- ✅ `F()` macro para strings (`Serial.println(F("texto"))`)
- ✅ `constrain()` valores antes de usar
- ✅ Validar dados antes de salvar EEPROM
- ✅ Usar `static` para variáveis locais persistentes

## 🔍 Loops do Sistema

### Loop Principal
```cpp
void loop() {
  commsProcess();        // MÁXIMA PRIORIDADE

  // Time-sliced loops:
  if (33ms)  { readTPS(); readMAP(); }
  if (67ms)  { calculateRPM(); checkSyncLoss(); updateEngineStatus(); }
  if (250ms) { readCLT(); readIAT(); readO2(); readBattery(); }

  // Cálculos (quando synced):
  if (hasSync && RPM > 0) {
    currentStatus.PW1 = calculateInjection();
    currentStatus.advance = calculateAdvance();
    currentStatus.dwell = calculateDwell();
    // Scheduling já aconteceu na ISR!
  }
}
```

### Priming Pulse
```cpp
// Ao obter primeiro sync, dispara pulso inicial
if (!primedFuel && hasSync && RPM > 0) {
  uint32_t duration = configPage1.primePulse * 100; // ms*10 -> us
  openInjector1();
  openInjector2();
  primeStartTime = micros();
  primedFuel = true;
}

// Fecha após duração (non-blocking)
if (primeStartTime > 0 && elapsed >= duration) {
  closeInjector1();
  closeInjector2();
  primeStartTime = 0;
}
```

## 📈 Uso de Recursos

### Flash (ROM)
```
Core functions:        ~10 KB
Tables + interpolation: ~2 KB
Sensors + filters:      ~2 KB
Decoders:              ~2 KB
Fuel + Ignition:       ~2 KB
Scheduler:             ~2 KB
Communication:         ~5 KB (CRC table!)
PROGMEM data:          ~1 KB
----------------------------------
TOTAL:                ~26 KB / 32 KB (81%)
```

### RAM
```
Statuses (currentStatus):   ~80 bytes
ConfigPage1:               128 bytes
ConfigPage2:               128 bytes
VE Table (8×8):             72 bytes
Ignition Table (8×8):       72 bytes
Schedules (4×16):           64 bytes
Stack:                     ~200 bytes
Sensor filters:             ~30 bytes
Serial buffers:             ~64 bytes
----------------------------------
TOTAL:                    ~838 bytes / 2048 bytes (41%)
```

### EEPROM
```
Magic number (4B) + version (4B):  8 bytes
ConfigPage1:                     128 bytes
ConfigPage2:                     128 bytes
VE Table (8×8):                   64 bytes
Ignition Table (8×8):             64 bytes
Calibration Tables:              ~100 bytes
----------------------------------
TOTAL:                          ~492 bytes / 1024 bytes (48%)
```

## 🐛 Troubleshooting

### Motor não sincroniza
- Verificar conexão do sensor de trigger
- Verificar `triggerFilterTime` (debounce)
- Testar com Basic Distributor (mais simples)
- Aumentar logging em `calculateRPM()`

### Injeção não funciona
- Verificar `hasSync && RPM > 0`
- Confirmar que `calculateInjection()` retorna PW válido
- Checar se `scheduleInjectionISR()` está sendo chamada
- Validar Timer1 configurado corretamente

### Ignição não funciona
- Verificar polaridade (`ignInvert` em configPage2)
- Confirmar `dwell` dentro do range (DWELL_MIN-DWELL_MAX)
- Checar cálculo de `sparkAngle` e `dwellStartAngle`
- Testar com dwell fixo primeiro

### TunerStudio não conecta
- Confirmar baudrate 115200
- Testar comando 'Q' (firmware version)
- Verificar CRC32 no Modern Protocol
- Habilitar `DEBUG_ENABLED` para logs

### Uso excessivo de RAM
- Evitar `String` class
- Usar `F()` para literais
- Reduzir buffers seriais
- Considerar mover mais dados para PROGMEM

## 📝 Padrões de Código

### Nomenclatura
```cpp
// Constantes
#define MAX_RPM 10000

// Variáveis globais
struct Statuses currentStatus;

// Funções inline (críticas)
inline void openInjector1() { digitalWrite(PIN_INJECTOR_1, HIGH); }

// Funções normais (camelCase)
uint16_t calculateInjection();
```

### Macros Úteis
```cpp
#define BIT_SET(var, bit)    ((var) |= (1 << (bit)))
#define BIT_CLEAR(var, bit)  ((var) &= ~(1 << (bit)))
#define BIT_CHECK(var, bit)  ((var) & (1 << (bit)))
```

### Threading/ISR Safety
```cpp
// Leitura de multi-byte volatile
noInterrupts();
uint16_t rpm = currentStatus.RPM;
interrupts();

// Escrita
noInterrupts();
triggerState.revolutionTime = newValue;
interrupts();
```

## 🎓 Conceitos Arduino Avançados

### Timer1 Modes
- **Normal:** Conta 0 → 65535, overflow
- **CTC (Clear Timer on Compare):** Conta até OCR1A, reseta
- **Usado:** CTC para precisão de timing

### Interrupts
- **External:** INT0 (trigger), INT1 (cam)
- **Timer:** TIMER1_COMPA, TIMER1_COMPB
- **Priority:** External > Timer > Main loop

### PROGMEM
```cpp
const uint8_t data[] PROGMEM = {1, 2, 3};
uint8_t value = pgm_read_byte(&data[i]);
uint16_t value16 = pgm_read_word(&data16[i]);
uint32_t value32 = pgm_read_dword(&data32[i]);
```

---

## 📝 Changelog Recente

### [HOJE] - Correções Críticas de Hardware

**Problemas identificados:**
1. ❌ **Pino de interrupção errado:** `PIN_TRIGGER_PRIMARY` estava no D6, que NÃO tem interrupção!
2. ❌ **Conflito de pinos:** D2 e D3 usados por injetores, mas são os únicos com INT0/INT1
3. ⚠️ **Operação módulo cara:** `getCrankAngle()` usava `%` (muito lento em AVR)

**Mudanças implementadas:**

1. **Remapeamento de pinos (globals.h)**
   - Trigger movido para D2 (INT0) e D3 (INT1) ✅
   - Injetores movidos para D10 e D11 (pinos comuns funcionam perfeitamente)
   - Bomba combustível para D6 (D10 liberado)
   - D7 vira pino reserva

2. **Otimização getCrankAngle() (decoders.cpp)**
   - Clamp em vez de módulo (eliminado operação cara)
   - Validação de `revolutionTime == 0` adicionada
   - Código mais rápido e previsível

**Resultado:**
- ✅ Interrupções funcionam corretamente (INT0 no pino certo!)
- ✅ Todos pinos com função apropriada
- ✅ Performance melhorada (sem operações módulo)
- ✅ Documentação atualizada

**Projeto:** Slowduino - Super Lowcost Speeduino
**Stack:** Arduino C++ + ATmega328p
**Filosofia:** Real-time ISR-driven, Integer-only, PROGMEM-first
**Protocolo:** Speeduino-compatible (TunerStudio)
**Última atualização:** Janeiro 2025
