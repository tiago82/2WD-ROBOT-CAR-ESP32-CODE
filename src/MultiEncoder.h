#pragma once
#include <Arduino.h>

int timeCountEncoder = 50; // faixa em milisegundos de contagem dos pulsos.
volatile int pulseCountEncoder1 = 0;
volatile int pulseCountEncoder2 = 0;
volatile int pulseTotalCountEncoder1 = 0;
volatile int pulseTotalCountEncoder2 = 0;
volatile unsigned long lastUpdateTime = 0;
typedef void (*FuncPtr)(); // Define um tipo de ponteiro para função

void startEncoder(int pinEncoder1, int pinEncoder2);
void updateEncoder();             // Atualiza a contagem de pulsos
void updateEncoder(FuncPtr func); // Atualiza a contagem de pulsos e executa uma função passada como parâmetro, Importante para chamar funcao que calcula PID.
void updateEncoderPrint();        // Atualiza a contagem de pulsos e imprime o valor por serial.
int getpulse1();                  // Retorna o número atual de pulsos por segundo .
int getpulse2();                  // Retorna o número atual de pulsos por segundo .

void ICACHE_RAM_ATTR funcaoInterrupcao1()
{
  pulseCountEncoder1++;
  pulseTotalCountEncoder1++;
}
void ICACHE_RAM_ATTR funcaoInterrupcao2()
{
  pulseCountEncoder2++;
  pulseTotalCountEncoder2++;
}

void startEncoder(int pinEncoder1)
{
  pinMode(pinEncoder1, INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(pinEncoder1), funcaoInterrupcao1, RISING);
}

void startEncoder(int pinEncoder1, int pinEncoder2)
{
  pinMode(pinEncoder1, INPUT_PULLDOWN);
  pinMode(pinEncoder2, INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(pinEncoder1), funcaoInterrupcao1, RISING);
  attachInterrupt(digitalPinToInterrupt(pinEncoder2), funcaoInterrupcao2, RISING);
}

void updateEncoder()
{
  unsigned long currentTime = millis();
  if (currentTime - lastUpdateTime >= timeCountEncoder)
  {
    // Serial.print("Pulsos por segundo: ");
    // Serial.println(pulseCountEncoder);
    pulseCountEncoder1 = 0;
    pulseCountEncoder2 = 0;
    lastUpdateTime = currentTime;
  }
}

void updateEncoder(FuncPtr func)
{
  unsigned long currentTime = millis();
  if (currentTime - lastUpdateTime >= timeCountEncoder)
  {
    func(); // Chama a função passada como argumento
    pulseCountEncoder1 = 0;
    pulseCountEncoder2 = 0;
    lastUpdateTime = currentTime;
  }
}

void updateEncoderPrint()
{
  unsigned long currentTime = millis();
  if (currentTime - lastUpdateTime >= timeCountEncoder)
  {
    Serial.print("Pulsos por segundo1: ");
    Serial.print(pulseCountEncoder1);
    Serial.print(" Pulsos por segundo2: ");
    Serial.println(pulseCountEncoder2);
    pulseCountEncoder1 = 0;
    pulseCountEncoder2 = 0;
    lastUpdateTime = currentTime;
  }
}

/**
 * @brief Retorna o valor do pulso 1.
 *
 * @return O valor do pulso 1.
 */
int getpulse1()
{
  return pulseCountEncoder1;
}
/**
 * @brief Retorna o valor do pulso 2.
 *
 * @return O valor do pulso 2.
 */
int getpulse2()
{
  return pulseCountEncoder2;
}

int gettotalpulse1()
{
  return pulseTotalCountEncoder1;
}
int gettotalpulse2()
{
  return pulseTotalCountEncoder2;
}
void resettotalpulse()
{
  pulseTotalCountEncoder1 = 0;
  pulseTotalCountEncoder2 = 0;
}
