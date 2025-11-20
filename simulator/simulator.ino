// -----------------------------
// Configuração do gerador 36-1
// -----------------------------
const int pinoSinal = 2;

const int totalDentes = 36;
const int denteDeFalha = 36;   // Último dente (ausente)

// RPM mínimo e máximo para varredura
const int rpmMin = 800;
const int rpmMax = 6500;

// Quanto mudar a cada passo (RPM)
const int passoRPM = 50;

// Variáveis de controle
int rpmAtual = rpmMin;
bool subindo = true;

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
}

void loop() {
  // Calcula tempo do meio-dente baseado na RPM atual
  unsigned long tempoMeio = calculaTempoMeioDente(rpmAtual);

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

  // Opcional: descomente para ver a RPM no Serial Monitor
  // Serial.println(rpmAtual);
}
