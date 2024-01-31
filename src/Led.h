/**
 *  Led.h
 *  Biblioteca para controlar um LED em um robô de carro de 2 rodas.
 * 
 * Esta biblioteca fornece funções para configurar e controlar um LED em um robô de carro de 2 rodas.
 * Ela permite acender o LED, fazer o LED piscar um número específico de vezes e controlar o LED em um loop contínuo.
 * 
 *  Esta biblioteca depende da biblioteca Pins.h onde estao definidos os pinos do LED.
 */

#ifndef LED_H
#define LED_H

#include <Arduino.h>
#include "Pins.h"

class Led
{
private:
  unsigned long previousMillis = 0; // Variável para armazenar o tempo anterior
  // bool ledState = false; // Estado atual do LED
  const long duration = 500; // Duração do acionamento do LED em milissegundos (2 segundos)
  long durationPiscar = 500;

public:
  int ledState = 0; // Variável para rastrear o número de piscadas

  void ledSetup(); // Declaração da função para configurar o LED

  void ledLoop(); // Declaração da função para controlar o LED em um loop contínuo
  void acenderLed();
  void acenderLed2();

  void ledLoopPiscar();                      // Declaração da função para controlar o LED piLscando em um loop
  void piscarLed(int numPiscadas);           // Declaração da função para piscar o LED um número específico de vezes
  void piscarLed(int numPiscadas, int rate); // Declaração da função para piscar o LED com um intervalo específico entre as piscadas
};

void Led::ledSetup()
{
  pinMode(LED_PCB, OUTPUT);
  digitalWrite(LED_PCB, LOW);
}

void Led::ledLoop()
{
  unsigned long currentMillis = millis(); // Obtém o tempo atual
  if (Led::ledState && (currentMillis - Led::previousMillis >= Led::duration))
  {                             // Verifica se passaram 2 segundos desde que o LED foi ligado
    digitalWrite(LED_PCB, LOW); // Desliga o LED após 2 segundos
    ledState = false;
  }
}

void Led::acenderLed()
{
  digitalWrite(LED_PCB, HIGH); // Desliga o LED após 2 segundos
  previousMillis = millis();   // Obtém o tempo do acionamento
  Led::ledState = true;
}

void Led::acenderLed2()
{
  unsigned long currentMillis = millis(); // Obtém o tempo atual
  if (Led::ledState > 0 && (currentMillis - previousMillis >= durationPiscar))
  {
    digitalWrite(LED_PCB, !digitalRead(LED_PCB)); // Inverte o estado do LED
    previousMillis = currentMillis;

    if (digitalRead(LED_PCB) == LOW)
    {
      Led::ledState--; // Decrementa o contador de piscadas quando o LED é desligado
    }
  }
}

void Led::piscarLed(int numPiscadas)
{
  Led::ledState = numPiscadas; // Cada piscada requer ligar e desligar o LED, então multiplicamos por 2 e subtrai 1
  digitalWrite(LED_PCB, HIGH);
  previousMillis = millis();
}

void Led::piscarLed(int numPiscadas, int duration)
{
  Led::ledState = numPiscadas; // Cada piscada requer ligar e desligar o LED, então multiplicamos por 2 e subtrai 1
  Led::durationPiscar = duration;
  digitalWrite(LED_PCB, HIGH);
  Led::previousMillis = millis();
}

#endif