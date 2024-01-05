#pragma once
#include <Arduino.h>


typedef void (*FuncPtr)(); // Define um tipo de ponteiro para função

void startEncoder(int pinEncoder1, int pinEncoder2);

void updateEncoder(); // Atualiza a contagem de pulsos 
void updateEncoder(FuncPtr func); // Atualiza a contagem de pulsos e executa uma função passada como parâmetro, Importante para chamar funcao que calcula PID.
void updateEncoderPrint(); // Atualiza a contagem de pulsos e imprime o valor por serial.
int getpulse1(); // Retorna o número atual de pulsos por segundo .
int getpulse2(); // Retorna o número atual de pulsos por segundo .


int timeCountEncoder = 250;

volatile int pulseCountEncoder1 = 0;
volatile int pulseCountEncoder2 = 0;
volatile unsigned long lastUpdateTime = 0;

void ICACHE_RAM_ATTR funcaoInterrupcao1() {
  pulseCountEncoder1++;
}
void ICACHE_RAM_ATTR funcaoInterrupcao2() {
  pulseCountEncoder2++;
}

void startEncoder(int pinEncoder1, int pinEncoder2) {
  pinMode(pinEncoder1, INPUT_PULLDOWN);
  pinMode(pinEncoder2, INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(pinEncoder1), funcaoInterrupcao1, RISING);
  attachInterrupt(digitalPinToInterrupt(pinEncoder2), funcaoInterrupcao2, RISING);
}

void updateEncoder() {
  unsigned long currentTime = millis();
  if (currentTime - lastUpdateTime >= timeCountEncoder) {
    //Serial.print("Pulsos por segundo: ");
    //Serial.println(pulseCountEncoder);
    pulseCountEncoder1 = 0;
    pulseCountEncoder2 = 0;
    lastUpdateTime = currentTime;
  }
}

void updateEncoder(FuncPtr func) {
  unsigned long currentTime = millis();
  if (currentTime - lastUpdateTime >= timeCountEncoder) {
    func(); // Chama a função passada como argumento
    pulseCountEncoder1 = 0;
    pulseCountEncoder2 = 0;
    lastUpdateTime = currentTime;
  }
}

void updateEncoderPrint() {
  unsigned long currentTime = millis();
  if (currentTime - lastUpdateTime >= timeCountEncoder) {
    Serial.print("Pulsos por segundo1: ");
    Serial.print(pulseCountEncoder1);
    Serial.print(" Pulsos por segundo2: ");
    Serial.println(pulseCountEncoder2);
    pulseCountEncoder1 = 0;
    pulseCountEncoder2 = 0;
    lastUpdateTime = currentTime;
  }
}

int getpulse1(){
  return pulseCountEncoder1;
} 
int getpulse2(){
  return pulseCountEncoder2;
} 

