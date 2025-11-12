// Define o pino de saída para o sinal
const int pinoSinal = 2;

const int pinoMap = 9;
const int pinoTPS = 3;

int mapValue = 0;

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

// A função setup executa uma vez quando você pressiona reset ou liga a placa
void setup() {
  // Inicializa o pino de sinal como saída
  pinMode(pinoSinal, OUTPUT);
  pinMode(pinoMap, OUTPUT);
}

// A função loop executa repetidamente para sempre
void loop() {
  // Simula uma rotação completa
  for (int i = 1; i <= totalDentes; i++) {
    
    // Verifica se é o ponto da falha de dente (dente ausente)
    if (i == denteDeFalha) {
      // Simula a falha de dente: mantém o sinal em LOW (ou HIGH, dependendo da polaridade, 
      // mas LOW é mais comum para o "dente ausente" em sistemas 36-1)
      // por um tempo equivalente a um pulso inteiro.
      // Aqui, mantemos LOW pelo tempo de *dois* meios dentes (um dente completo)
      delayMicroseconds(tempoMeioDente_us * 2); 
      // NOTA: Em alguns sistemas, a falha é na verdade a ausência do pulso. 
      // Se estivéssemos gerando o pulso a cada iteração, simplesmente pularíamos 
      // o código de pulso nesta iteração. Como estamos gerando 35 pulsos e a falha 
      // é a ausência do 36º, vamos apenas garantir que haja uma pausa 
      // (aqui simulada como o tempo de um dente completo).
    } else {
      // Gera o pulso do "dente" (onda quadrada)
      
      // Parte HIGH do dente
      digitalWrite(pinoSinal, HIGH);
      delayMicroseconds(tempoMeioDente_us); // Tempo em HIGH (meio dente)
      
      // Parte LOW do dente
      digitalWrite(pinoSinal, LOW);
      delayMicroseconds(tempoMeioDente_us); // Tempo em LOW (meio dente)
    }
  }
  analogWrite(pinoMap, mapValue/4);
 analogWrite(pinoTPS, mapValue/4);
	mapValue++;
	if (mapValue > 1023)
		mapValue = 0;
}