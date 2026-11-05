/*
  Ponte levadiça - o tabuleiro sobe 45 graus e desce de volta.
  Controle por entrada de texto no Serial Monitor (sem botão e sem LEDs).

  Comandos (digite e pressione Enter):
    s  ou  1  -> SOBE a ponte 45 graus
    d  ou  0  -> DESCE a ponte (volta na horizontal)

  Ligações:
    Servo sinal (laranja/amarelo) -> pino 9
    Servo VCC (vermelho)          -> 5V
    Servo GND (marrom/preto)      -> GND

  Serial Monitor: velocidade 9600 baud.
*/

#include <Servo.h>

const int PINO_SERVO = 9;

// Ajuste conforme a montagem física.
const int ANGULO_BAIXO = 0;    // ponte deitada, na horizontal (fechada)
const int ANGULO_CIMA  = 49;   // ponte levantada 45 graus (aberta)

const int VELOCIDADE_MS = 30;  // maior = sobe e desce mais devagar

Servo servo;
int anguloAtual = ANGULO_BAIXO;
bool ponteSubida = false;

void moverPara(int destino) {
  // Move 1 grau por vez para o movimento ser suave
  while (anguloAtual != destino) {
    anguloAtual += (destino > anguloAtual) ? 1 : -1;
    servo.write(anguloAtual);
    delay(VELOCIDADE_MS);
  }
}

void subirPonte() {
  if (ponteSubida) {
    Serial.println("A ponte já está levantada.");
    return;
  }
  Serial.println("Subindo ponte (49 graus)...");
  moverPara(ANGULO_CIMA);
  ponteSubida = true;
  Serial.println("Ponte levantada.");
}

void descerPonte() {
  if (!ponteSubida) {
    Serial.println("A ponte já está abaixada.");
    return;
  }
  Serial.println("Descendo ponte...");
  moverPara(ANGULO_BAIXO);
  ponteSubida = false;
  Serial.println("Ponte abaixada.");
}

void setup() {
  servo.attach(PINO_SERVO);
  servo.write(ANGULO_BAIXO);
  delay(500);

  Serial.begin(9600);
  Serial.println("Ponte pronta (abaixada).");
  Serial.println("Digite 's' para subir ou 'd' para descer.");
}

void loop() {
  if (Serial.available() > 0) {
    char comando = Serial.read();

    if (comando == 's' || comando == 'S' || comando == '1') {
      subirPonte();
    } else if (comando == 'd' || comando == 'D' || comando == '0') {
      descerPonte();
    } else if (comando != '\n' && comando != '\r') {
      Serial.println("Comando inválido. Use 's' (subir) ou 'd' (descer).");
    }
  }
}
