# SLOWDUINO
## Super Lowcost Speeduino

ECU minimalista e open-source para motores de combustão interna, otimizada para rodar em **ATmega328p** (Arduino Uno/Nano).

Baseada na Speeduino, mas drasticamente simplificada para caber em apenas **32KB de Flash** e **2KB de RAM**.

---

![](https://raw.githubusercontent.com/alexandrefelipemuller/slowduino/refs/heads/main/resources/PCB_3d.jpeg)


## 🎯 Objetivo

Criar uma ECU totalmente funcional, de baixo custo, com controle de injeção e ignição, compatível com comunicação básica com TunerStudio, sem recursos avançados.

**Prioridades:**
- ✅ Simplicidade
- ✅ Tamanho reduzido de código
- ✅ Clareza lógica
- ✅ Funcionalidade real em hardware limitado

---

## ⚙️ Especificações Técnicas

### Hardware Suportado
- **MCU**: ATmega328p (Arduino Uno, Nano, Pro Mini)
- **Clock**: 16 MHz
- **Flash**: 32 KB (firmware ~20-24 KB)
- **RAM**: 2 KB (uso ~50-60%)
- **EEPROM**: 1 KB

### Capacidades do Motor
- **Cilindros**: 1-4
- **Injeção**: Wasted Paired (2 canais)
- **Ignição**: Wasted Spark (2 canais)
- **Trigger Wheels**: Missing Tooth (36-1, 60-2) ou Basic Distributor

---

## 📊 Mapeamento de Pinos

### Saídas Digitais
| Função | Pino Arduino | Descrição |
|--------|--------------|-----------|
| Injetor 1 | D10 | Cilindros 1+4 (wasted paired) |
| Injetor 2 | D11 | Cilindros 2+3 (wasted paired) |
| Bobina 1 | D4 | Ignição cilindros 1+4 |
| Bobina 2 | D5 | Ignição cilindros 2+3 |
| Ventoinha | D8 | Relé da ventoinha do radiador |
| Válvula Marcha Lenta | D9 | Selenoide IAC (PWM) |
| Bomba Combustível | D6 | Relé da bomba de combustível |

### Entradas Digitais
| Função | Pino Arduino | Descrição |
|--------|--------------|-----------|
| Trigger Primário | D2 (INT0) | Sensor de rotação (crank) |
| Trigger Secundário | D3 | Sensor de fase (cam) - futuro |
| Velocidade | D12 | Sensor de velocidade (VSS) |

### Entradas Analógicas
| Função | Pino Arduino | Descrição |
|--------|--------------|-----------|
| CLT | A0 | Temperatura do motor (NTC 10K) |
| IAT | A1 | Temperatura do ar (NTC 10K) |
| MAP | A2 | Pressão do coletor (sensor MPX4250) |
| TPS | A3 | Posição da borboleta (potenciômetro) |
| O2 | A4 | Sonda Lambda narrowband |
| Bateria | A5 | Tensão da bateria (divisor 10K:1K5) |
| Pressão Óleo | A6 | Sensor de pressão de óleo (0-5V = 0-1000 kPa) |
| Pressão Combustível | A7 | Sensor de pressão de combustível (0-5V = 0-1000 kPa) |

---

![](https://github.com/alexandrefelipemuller/slowduino/blob/main/resources/Schematic_Slowduino-injection_2025-11-06.png)


[Schematic Overview](Schematic.md)


## 📂 Estrutura de Arquivos

```
slowduino/
├── slowduino.ino          # Loop principal (setup + loop)
├── globals.h/cpp          # Estruturas de dados globais
├── config.h               # Configurações e constantes
├── storage.h/cpp          # Persistência EEPROM
├── tables.h/cpp           # Tabelas 3D/2D e interpolação
├── sensors.h/cpp          # Leitura de sensores ADC
├── decoders.h/cpp         # Decoders de trigger wheel
├── fuel.h/cpp             # Cálculos de injeção
├── ignition.h/cpp         # Cálculos de ignição
├── scheduler.h/cpp        # Agendamento de eventos (Timer1)
├── auxiliaries.h/cpp      # Controle de ventoinha, IAC e bomba
├── comms.h/cpp            # Comunicação serial (TunerStudio)
└── README.md              # Esta documentação
```

---

## 🔧 Mapas e Tabelas

### Tabelas 3D (8×8)
- **VE Table** (Volumetric Efficiency): 0-255%
- **Ignition Table** (Spark Advance): -10 a +45° BTDC

**Eixos:**
- X: RPM (500-6000 RPM, 8 pontos)
- Y: MAP (20-160 kPa, 8 pontos)

**Interpolação:** Bilinear em aritmética inteira

### Correções de Combustível

| Correção | Tipo | Descrição |
|----------|------|-----------|
| WUE | Tabela 1D (6 pontos) | Enriquecimento por temperatura |
| ASE | Fixo + contador | Enriquecimento pós-partida |
| AE | TPSdot | Pump shot em aceleração |
| CLT | Tabela 1D | Ajuste fino por temperatura |
| Bateria | Lookup | Compensa deadtime do injetor |

### Correções de Ignição

| Correção | Tipo | Descrição |
|----------|------|-----------|
| CLT Advance | Tabela 1D (4 pontos) | Mais avanço em motor frio |
| Idle Advance | Fixo | Avanço adicional em marcha lenta |
| Rev Limiter | Threshold | Corta avanço acima do RPM limite |

---

## 💾 Layout da EEPROM (1024 bytes)

| Offset | Tamanho | Conteúdo |
|--------|---------|----------|
| 0 | 1 byte | Versão da EEPROM |
| 10 | 64 bytes | Tabela VE 8×8 |
| 74 | 16 bytes | Eixo X da VE (RPM) |
| 90 | 8 bytes | Eixo Y da VE (MAP) |
| 100 | 64 bytes | Tabela Ignição 8×8 |
| 164 | 16 bytes | Eixo X da Ignição |
| 180 | 8 bytes | Eixo Y da Ignição |
| 200 | 128 bytes | ConfigPage1 (fuel settings) |
| 328 | 128 bytes | ConfigPage2 (ignition settings) |
| 456+ | | Reservado para expansão |

---

## 🚀 Primeiros Passos

### 1. Hardware

**Lista de Materiais:**
- Arduino Uno ou Nano (ATmega328p)
- Sensor MAP (ex: MPX4250)
- Sensor TPS (potenciômetro 5K)
- 2× Termistores NTC 10K (CLT e IAT)
- Sensor de rotação (Hall ou indutivo)
- Sensor de pressão de óleo (0-5V, 0-1000 kPa)
- Sensor de pressão de combustível (0-5V, 0-1000 kPa)
- 2× Drivers de injetor (ex: ULN2003 ou MOSFET)
- 2× Módulos de ignição (ex: BIP373 ou similar)
- 3× Relés 12V (ventoinha, bomba combustível, reserva)
- 1× Válvula IAC (idle air control) ou selenoide PWM
- Regulador 5V e proteções

### 2. Software

**Upload do Firmware:**
```bash
# Via Arduino IDE
1. Abrir slowduino.ino
2. Selecionar placa: "Arduino Uno" ou "Arduino Nano"
3. Selecionar porta serial
4. Upload
```

**Primeira Inicialização:**
- Ao ligar, firmware carrega valores padrão na EEPROM
- Aguarda detecção de sincronismo do trigger
- LED TX/RX piscará durante comunicação

### 3. Calibração Básica

**Passos mínimos:**
1. **TPS**: Calibrar 0% (pedal solto) e 100% (WOT)
2. **MAP**: Verificar leitura atmosférica (~100 kPa)
3. **Trigger**: Configurar dentes (ex: 36-1) e ângulo de referência
4. **Required Fuel**: Calcular baseado em deslocamento e injetores
   ```
   reqFuel = (deslocamento_cc / nCylindros) / (fluxo_injetor_cc/min) * 1000
   ```

---

## 📡 Comunicação Serial

### Protocolo TunerStudio Simplificado

**Velocidade:** 115200 bps

**Comandos Implementados:**
| Comando | Código | Descrição |
|---------|--------|-----------|
| Version | 'Q' | Retorna versão do firmware |
| Realtime Data | 'A' | Envia struct currentStatus |
| Read VE Table | 'V' | Lê tabela VE completa |
| Read Ign Table | 'I' | Lê tabela Ignição |
| Write VE Table | 'W' | Escreve tabela VE |
| Write Ign Table | 'X' | Escreve tabela Ignição |
| Burn EEPROM | 'B' | Salva config na EEPROM |
| Test Comms | 'T' | Teste de comunicação |

### Formato de Dados

**Realtime Data (struct Statuses):**
```c
RPM           (uint16_t)  // 0-8000
MAP           (uint8_t)   // 0-255 kPa
TPS           (uint8_t)   // 0-100%
coolant       (int8_t)    // -40 a +150°C
IAT           (int8_t)    // -40 a +150°C
battery10     (uint8_t)   // Volts × 10
PW1           (uint16_t)  // Microsegundos
advance       (int8_t)    // Graus BTDC
VE            (uint8_t)   // %
... (ver globals.h para struct completa)
```

---

## 🔍 Debug e Diagnóstico

### Debug Serial

Descomente `#define DEBUG_ENABLED` em `config.h` para ativar logs:

```
RPM: 1850 | Sync: OK | MAP: 45 kPa | TPS: 12% | CLT: 82C | PW: 8450us | Adv: 18deg
```

### LEDs de Diagnóstico

- **LED_BUILTIN (D13)**: Pisca a cada revolução (se configurado)
- **TX/RX**: Atividade serial

### Problemas Comuns

**Motor não sincroniza:**
- Verificar sinal do trigger com osciloscópio
- Conferir configuração de dentes (36-1, 60-2)
- Verificar filtro de debounce (50us padrão)

**Injetores não acionam:**
- Verificar conexão dos drivers
- Testar pinos D2/D3 com LED
- Conferir cálculo de Required Fuel

**Ignição sem faísca:**
- Verificar módulos de ignição
- Conferir polaridade (configPage2.ignInvert)
- Validar cálculo de dwell (3-6ms típico)

---

## 📈 Performance e Limitações

### Uso de Recursos

| Recurso | Usado | Disponível | % |
|---------|-------|------------|---|
| Flash | ~22 KB | 32 KB | 68% |
| RAM | ~1100 bytes | 2048 bytes | 53% |
| EEPROM | ~550 bytes | 1024 bytes | 54% |

### Limitações Conhecidas

**Vs. Speeduino completa:**
- ❌ Tabelas menores (8×8 vs 16×16)
- ❌ Sem VVT, boost control, launch control
- ❌ Sem CAN bus
- ❌ Sem flex fuel
- ❌ Máximo 4 cilindros
- ❌ Sem modo sequential
- ✅ Mas funciona em hardware 4× mais barato!

**Precisão de Timing:**
- Timer1 @ 2 MHz = **0.5 µs de resolução**
- Erro típico de agendamento: **< 5 µs**
- Suficiente até 8000 RPM

---

## 🛠️ Desenvolvimento Futuro

### v0.2 (Atual)

- [x] Controle de ventoinha por temperatura
- [x] Bomba de combustível com priming
- [x] Válvula de marcha lenta (IAC) com PWM
- [x] Sensores de pressão de óleo e combustível
- [x] Priming pulse de injeção

### Roadmap v0.3

- [ ] Agendamento correto baseado em ângulo do virabrequim
- [ ] Modo sequential (4 canais de injeção)
- [ ] Sensor de cam (sincronismo completo)
- [ ] Closed-loop O2
- [ ] Tabela de AFR target

### Roadmap v0.4

- [ ] Datalogger SD card
- [ ] Compatibilidade completa com TunerStudio INI
- [ ] Launch control básico
- [ ] Expansão para 6 cilindros (ATmega2560)

---

## 🤝 Contribuindo

Pull requests são bem-vindos!

**Áreas de contribuição:**
- Otimização de memória
- Novos decoders de trigger
- Correções de bugs
- Documentação
- Testes em bancada

---

## 📜 Licença

GNU GPL v2 (mesma da Speeduino original)

---

## 📚 Referências

- **Speeduino**: https://speeduino.com
- **TunerStudio**: https://www.tunerstudio.com
- **ATmega328p Datasheet**: https://www.microchip.com/en-us/product/ATmega328P
- **Aritmética Inteira para ECUs**: "Building Electronic Engine Controls" (Greg Banish)

---

## ⚠️ Disclaimer

**Este projeto é experimental e educacional.**

- Use por sua conta e risco
- Não recomendado para uso em vias públicas sem homologação
- Sempre tenha backups de segurança
- Teste extensivamente em bancada antes de instalar em veículo

**O autor não se responsabiliza por danos a motores, veículos ou pessoas.**

---

## 📧 Contato

Dúvidas e sugestões: abra uma issue no repositório.

---

**Slowduino** - Porque nem todo motor precisa de 8 MB de RAM! 🚗💨


