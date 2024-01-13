#ifndef LED_H
#define LED_H

#include <Arduino.h>
#include "Pins.h"

void ledSetup(); // Declaração da função para configurar o LED

void ledLoop(); // Declaração da função para controlar o LED em um loop contínuo
void acenderLed();

void ledLoopPiscar();                      // Declaração da função para controlar o LED piscando em um loop
void piscarLed(int numPiscadas);           // Declaração da função para piscar o LED um número específico de vezes
void piscarLed(int numPiscadas, int rate); // Declaração da função para piscar o LED com um intervalo específico entre as piscadas

#endif