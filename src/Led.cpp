#include "Led.h"


unsigned long previousMillis = 0; // Variável para armazenar o tempo anterior
//bool ledState = false; // Estado atual do LED
int ledState = 0; // Variável para rastrear o número de piscadas
const long duration = 500; // Duração do acionamento do LED em milissegundos (2 segundos)
long durationPiscar = 500;


void ledSetup() {
  pinMode(LED_PCB, OUTPUT);
  digitalWrite(LED_PCB, LOW);

}


void ledLoop() {
  unsigned long currentMillis = millis(); // Obtém o tempo atual
  if (ledState && (currentMillis - previousMillis >= duration)) { // Verifica se passaram 2 segundos desde que o LED foi ligado
    digitalWrite(LED_PCB, LOW); // Desliga o LED após 2 segundos
    ledState = false;
  }
}

void acenderLed() {
  digitalWrite(LED_PCB, HIGH); // Desliga o LED após 2 segundos
  previousMillis = millis(); // Obtém o tempo do acionamento
  ledState = true;
}


void ledLoopPiscar() {
  unsigned long currentMillis = millis(); // Obtém o tempo atual
  if (ledState > 0 && (currentMillis - previousMillis >= durationPiscar)) {
    digitalWrite(LED_PCB, !digitalRead(LED_PCB)); // Inverte o estado do LED
    previousMillis = currentMillis;

    if (digitalRead(LED_PCB) == LOW) {
      ledState--; // Decrementa o contador de piscadas quando o LED é desligado
    }
  }
}

void piscarLed(int numPiscadas) {
  ledState = numPiscadas ; // Cada piscada requer ligar e desligar o LED, então multiplicamos por 2 e subtrai 1
  digitalWrite(LED_PCB, HIGH); 
  previousMillis = millis();
}

void piscarLed(int numPiscadas, int duration) {
  ledState = numPiscadas ; // Cada piscada requer ligar e desligar o LED, então multiplicamos por 2 e subtrai 1
  durationPiscar = duration;
  digitalWrite(LED_PCB, HIGH); 
  previousMillis = millis();
}