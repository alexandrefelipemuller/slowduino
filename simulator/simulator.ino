// Define o pino de saída para o sinal
const int pinoSinal = 2;

// Define o número total de dentes (pulsos)
const int totalDentes = 36;
// Define a posição da falha de dente (por exemplo, após o 35º dente)
const int denteDeFalha = 36; 
// A falha de dente é na verdade a ausência do 36º pulso.

// Tempo para cada "meio dente" em microssegundos (determina a "velocidade" do motor)
// Um período completo de um dente (HIGH e LOW) será o dobro deste valor.
// 500 us por meio dente = 1000 us (1 ms) por dente completo.
// 35 dentes * 1ms/dente + 1ms de falha = 36 ms por rotação
// Rotações por segundo (RPS) = 1 / 0.036s ≈ 27.78 RPS
// Rotações por minuto (RPM) = 27.78 RPS * 60 ≈ 1667 RPM
const long tempoMeioDente_us = 500; 
int i=0;

// A função setup executa uma vez quando você pressiona reset ou liga a placa
void setup() {
  // Inicializa o pino de sinal como saída
  pinMode(pinoSinal, OUTPUT);
}

// A função loop executa repetidamente para sempre
void loop() {
  // Simula uma rotação completa
  	i++;
    // Verifica se é o ponto da falha de dente (dente ausente)
     // Gera o pulso do "dente" (onda quadrada)
     // Parte HIGH do dente
     digitalWrite(pinoSinal, HIGH); // Tempo em HIGH (meio dente)
     delayMicroseconds(tempoMeioDente_us);      
     // Parte LOW do dente
     digitalWrite(pinoSinal, LOW); // Tempo em LOW (meio dente)
     delayMicroseconds(tempoMeioDente_us);

  if (i >= denteDeFalha) {
      // Simula a falha de dente: mantém o sinal em LOW (ou HIGH, dependendo da polaridade, 
      // mas LOW é mais comum para o "dente ausente" em sistemas 36-1)
      // por um tempo equivalente a um pulso inteiro.
      // Aqui, mantemos LOW pelo tempo de *dois* meios dentes (um dente completo)
      digitalWrite(pinoSinal, LOW);      
      delayMicroseconds(tempoMeioDente_us*2); 
      i=0;
      // NOTA: Em alguns sistemas, a falha é na verdade a ausência do pulso. 
      // Se estivéssemos gerando o pulso a cada iteração, simplesmente pularíamos 
      // o código de pulso nesta iteração. Como estamos gerando 35 pulsos e a falha 
      // é a ausência do 36º, vamos apenas garantir que haja uma pausa 
      // (aqui simulada como o tempo de um dente completo).
    }
}