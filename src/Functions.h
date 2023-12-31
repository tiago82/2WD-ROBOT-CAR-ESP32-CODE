#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <Arduino.h>
#include "MotorDriver.h"
#include "EncoderReader.h"
#include <MFRC522.h>
#include "rfid_functions.h"

// Declaração das funções
void wifisetup();
void wifiloop();
void motordriver();
void cardsetup();
void cardloop();

#endif 

