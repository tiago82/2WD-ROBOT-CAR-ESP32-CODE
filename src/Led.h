#ifndef LED_H
#define LED_H

#include <Arduino.h>
#include "Pins.h"

void ledSetup();

void ledLoop();
void acenderLed();

void ledLoopPiscar();
void piscarLed(int numPiscadas);
void piscarLed(int numPiscadas, int rate);


#endif