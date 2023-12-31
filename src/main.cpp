#include <Arduino.h>
#include "Functions.h"

void setup() {

Serial.begin(115200);
//testMotor(50);
cardSetup();
ledSetup();

}

void loop() {
   
cardLoop();
ledLoopPiscar();

}

