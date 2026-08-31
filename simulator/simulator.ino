// -----------------------------
// Configuração do gerador 36-1
// -----------------------------
// ATENÇÃO - PINAGEM MUDOU:
//   Sinal de trigger (roda fônica) agora sai no D8, não mais no D2.
//   D2 (INT0) e D3 (INT1) ficam livres para MONITORAR a saída de ignição
//   da ECU (fecha o loop: valida ângulo/dwell em vez de só gerar trigger).
//
// Ligações:
//   Simulador D8  -> ECU D2  (trigger, saída do simulador)
//   ECU D4 (IGN1) -> Simulador D2 (entrada, INT0)
//   ECU D5 (IGN2) -> Simulador D3 (entrada, INT1)

const int pinoSinal = 8;
const int pinoIgn1 = 2;   // INT0 - monitora IGN1 da ECU (cilindros 1+4)
const int pinoIgn2 = 3;   // INT1 - monitora IGN2 da ECU (cilindros 2+3)

const int totalDentes = 36;
const int denteDeFalha = 36;   // Último dente (ausente)

// RPM mínimo e máximo para varredura
const int rpmMin = 800;
const int rpmMax = 13000;

// Quanto mudar a cada passo (RPM)
const int passoRPM = 50;

// Variáveis de controle
int rpmAtual = rpmMin;
bool subindo = true;

// -------------------------------------------
// Monitoramento de ignição (fecha o loop de validação)
// -------------------------------------------
// Cada canal deve disparar 1x a cada 2 revoluções (wasted spark, 2 canais
// alternando). Se um canal ficar mais que isso sem disparar, é um evento
// perdido - loga como erro.
const uint8_t MAX_REVS_SEM_EVENTO = 3;

volatile uint32_t ign1RiseTime = 0;
volatile uint16_t ign1Dwell = 0;
volatile bool ign1NovoEvento = false;

volatile uint32_t ign2RiseTime = 0;
volatile uint16_t ign2Dwell = 0;
volatile bool ign2NovoEvento = false;

// Referência de ângulo: marcada no início de cada revolução gerada
// (equivalente ao "dente #1"/toothOneTime que a própria ECU calcula)
volatile uint32_t revStartTime = 0;
volatile uint32_t revPeriod = 0;

uint8_t revsSemIgn1 = 0;
uint8_t revsSemIgn2 = 0;

void ign1ISR() {
  if (digitalRead(pinoIgn1) == HIGH) {
    ign1RiseTime = micros();
  } else {
    ign1Dwell = (uint16_t)(micros() - ign1RiseTime);
    ign1NovoEvento = true;
  }
}

void ign2ISR() {
  if (digitalRead(pinoIgn2) == HIGH) {
    ign2RiseTime = micros();
  } else {
    ign2Dwell = (uint16_t)(micros() - ign2RiseTime);
    ign2NovoEvento = true;
  }
}

// Ângulo (0-359) do instante eventTime, relativo ao início da revolução atual
uint16_t anguloDoEvento(uint32_t eventTime, uint32_t inicioRev, uint32_t periodoRev) {
  if (periodoRev == 0) return 0;
  uint32_t delta = eventTime - inicioRev;
  if (delta >= periodoRev) delta = periodoRev - 1;  // clamp (evento já na próxima rev)
  return (uint16_t)(((uint32_t)delta * 360UL) / periodoRev);
}

// -------------------------------------------
// Converte RPM → tempo por meio-dente (µs)
// Fórmula:
// Tempo por rotação (µs) = 60e6 / RPM
// Tempo por dente = Trot / 36
// Tempo por meio-dente = Tdente / 2
// -------------------------------------------
unsigned long calculaTempoMeioDente(int rpm) {
  double tempoRot = 60000000.0 / rpm;       // µs por rotação
  double tempoDente = tempoRot / totalDentes;
  return (unsigned long)(tempoDente / 2.0); // meio dente
}

void setup() {
  pinMode(pinoSinal, OUTPUT);
  digitalWrite(pinoSinal, LOW);

  pinMode(pinoIgn1, INPUT);
  pinMode(pinoIgn2, INPUT);
  attachInterrupt(digitalPinToInterrupt(pinoIgn1), ign1ISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinoIgn2), ign2ISR, CHANGE);

  Serial.begin(115200);
  Serial.println(F("Simulador 36-1 + monitor de ignicao (IGN1=D2, IGN2=D3)"));
}

void loop() {
  // Calcula tempo do meio-dente baseado na RPM atual
  unsigned long tempoMeio = calculaTempoMeioDente(rpmAtual);

  // Marca início desta revolução (referência de ângulo) e guarda a duração
  // da revolução anterior (aproximação suficiente, RPM varia devagar)
  uint32_t agora = micros();
  uint32_t inicioRevAtual = agora;
  uint32_t periodoRevAnterior = revPeriod;
  revPeriod = agora - revStartTime;
  revStartTime = agora;

  revsSemIgn1++;
  revsSemIgn2++;

  // ----- GERA UMA ROTAÇÃO COMPLETA -----
  for (int i = 1; i <= totalDentes; i++) {

    if (i == denteDeFalha) {
      // Dente ausente → pausa equivalente a 1 dente completo
      digitalWrite(pinoSinal, LOW);
      delayMicroseconds(tempoMeio * 2);
      continue;
    }

    // Pulso normal de um dente
    digitalWrite(pinoSinal, HIGH);
    delayMicroseconds(tempoMeio);

    digitalWrite(pinoSinal, LOW);
    delayMicroseconds(tempoMeio);
  }

  // ----- REPORTA EVENTOS DE IGNIÇÃO CAPTURADOS NESTA REVOLUÇÃO -----
  noInterrupts();
  bool ev1 = ign1NovoEvento;
  uint16_t dwell1 = ign1Dwell;
  uint32_t rise1 = ign1RiseTime;
  ign1NovoEvento = false;

  bool ev2 = ign2NovoEvento;
  uint16_t dwell2 = ign2Dwell;
  uint32_t rise2 = ign2RiseTime;
  ign2NovoEvento = false;
  interrupts();

  if (ev1) {
    revsSemIgn1 = 0;
    Serial.print(F("IGN1 dwell="));
    Serial.print(dwell1);
    Serial.print(F("us angulo="));
    Serial.print(anguloDoEvento(rise1, inicioRevAtual, periodoRevAnterior));
    Serial.print(F("deg RPM="));
    Serial.println(rpmAtual);
  }

  if (ev2) {
    revsSemIgn2 = 0;
    Serial.print(F("IGN2 dwell="));
    Serial.print(dwell2);
    Serial.print(F("us angulo="));
    Serial.print(anguloDoEvento(rise2, inicioRevAtual, periodoRevAnterior));
    Serial.print(F("deg RPM="));
    Serial.println(rpmAtual);
  }

  if (revsSemIgn1 > MAX_REVS_SEM_EVENTO) {
    Serial.print(F("!!! IGN1 MISSING - RPM="));
    Serial.println(rpmAtual);
    revsSemIgn1 = 0;  // evita spam repetido a cada volta
  }

  if (revsSemIgn2 > MAX_REVS_SEM_EVENTO) {
    Serial.print(F("!!! IGN2 MISSING - RPM="));
    Serial.println(rpmAtual);
    revsSemIgn2 = 0;
  }

  // ----- AJUSTA RPM PARA PRÓXIMA ROTAÇÃO -----
  if (subindo) {
    rpmAtual += passoRPM;
    if (rpmAtual >= rpmMax) {
      rpmAtual = rpmMax;
      subindo = false;
    }
  } else {
    rpmAtual -= passoRPM;
    if (rpmAtual <= rpmMin) {
      rpmAtual = rpmMin;
      subindo = true;
    }
  }
}
