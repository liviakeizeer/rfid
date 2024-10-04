#include <Arduino.h>
#include <ESP32Servo.h>
#include <NewPing.h>

const int trigPin = 23; // Pino do Trigger do HC-SR04
const int echoPin = 22; // Pino do Echo do HC-SR04
const int servoPin = 18; // Pino do servo
const int maxDistance = 200; // Distância máxima (em cm) que o sensor irá medir
const int numReadings = 5; // Número de leituras para média
NewPing sonar(trigPin, echoPin, maxDistance); // Cria o objeto NewPing
Servo meuServo; // Cria um objeto servo

void setup() {
  Serial.begin(115200); // Inicializa a comunicação serial
  meuServo.attach(servoPin); // Anexa o pino do servo
  meuServo.write(0); // Inicializa o servo em 0 graus
}

unsigned int getAverageDistance() {
  unsigned int totalDistance = 0;
  int validReadings = 0;

  for (int i = 0; i < numReadings; i++) {
    delay(50); // Aguarda entre as leituras
    unsigned int distance = sonar.ping_cm(); // Lê a distância em cm

    // Validação de leitura: ignorar se fora do intervalo
    if (distance > 2 && distance < 400) {
      totalDistance += distance;
      validReadings++;
    }
  }

  // Retorna a média, se houver leituras válidas
  return validReadings > 0 ? totalDistance / validReadings : 0;
}

void loop() {
  unsigned int distancia = getAverageDistance(); // Obtem a média das distâncias

  Serial.print("Distância média: ");
  Serial.print(distancia);
  Serial.println(" cm");

  // Se a distância for menor ou igual a 5 cm, abre o servo em 90 graus
  if (distancia > 0 && distancia <= 5) {
    meuServo.write(90); // Move o servo para 90 graus
  } else {
    meuServo.write(0); // Retorna o servo para 0 graus
  }

  delay(500); // Aguarda meio segundo antes de medir novamente
}
