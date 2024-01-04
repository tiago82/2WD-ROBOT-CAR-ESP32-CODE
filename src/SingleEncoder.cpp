#include "SingleEncoder.h"

int timeCountEncoder = 250;

volatile int pulseCountEncoder = 0;
volatile unsigned long lastUpdateTime = 0;

void ICACHE_RAM_ATTR funcaoInterrupcao() {
  pulseCountEncoder++;
}

void startEncoder(int pinEncoder) {
  pinMode(pinEncoder, INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(pinEncoder), funcaoInterrupcao, RISING);
}

void updateEncoder() {
  unsigned long currentTime = millis();
  if (currentTime - lastUpdateTime >= timeCountEncoder) {
    //Serial.print("Pulsos por segundo: ");
    //Serial.println(pulseCountEncoder);
    pulseCountEncoder = 0;
    lastUpdateTime = currentTime;
  }
}

void updateEncoder(FuncPtr func) {
  unsigned long currentTime = millis();
  if (currentTime - lastUpdateTime >= timeCountEncoder) {
    func(); // Chama a função passada como argumento
    pulseCountEncoder = 0;
    lastUpdateTime = currentTime;
  }
}

void updateEncoderPrint() {
  unsigned long currentTime = millis();
  if (currentTime - lastUpdateTime >= timeCountEncoder) {
    Serial.print("Pulsos por segundo: ");
    Serial.println(pulseCountEncoder);
    pulseCountEncoder = 0;
    lastUpdateTime = currentTime;
  }
}

int getpulse(){
  return pulseCountEncoder;
} 

