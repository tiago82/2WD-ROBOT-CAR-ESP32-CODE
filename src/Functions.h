#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <Arduino.h>
#include "MotorDriver.h"
#include "EncoderReader.h"
#include <MFRC522.h>
#include "rfid_functions.h"
#include "Pins.h"
#include <BluetoothSerial.h>
#include "Led.h"

// Declare as funções
void wifiSetup();
void wifiLoop();
void testMotor(int speed); // testa motores com velocidades iguais da roda
void testMotor(int speed1, int speed2); // testa motor com velocidades diferentes
void cardSetup();
void cardLoop();
void myFunction1();
void myFunction2();
void btSetup(String BTName); // Escolha o nome do Bluetooth
void btLoop();



#endif 



