#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <Arduino.h>
#include "MotorDriver.h"
#include "EncoderReader.h"
#include <MFRC522.h>
#include "rfid_functions.h"
#include "Pins.h"

// Declare as funções
void wifisetup();
void wifiloop();
void motordriver();
void cardsetup();
void cardloop();
void myFunction1();
void myFunction2();


#endif 



