#ifndef PINS_H
#define PINS_H

#include <Arduino.h>

//Motor
#define EN1 21
#define IN1 32
#define IN2 33
#define EN2 22
#define IN3 25
#define IN4 26

//Encoder
#define M1_S1 16
#define M1_S2 17
#define M2_S1 3 // RX0
#define M2_S2 1 // TX0

//RFID (HSPI)
#define SS_RFID_PIN 5   // Define o pino SDA do MFRC522
#define RST_RFID_PIN 2  // Define o pino RST do MFRC522

#define RFID_SCK 18
#define RFID_MOSI 23
#define RFID_MISO 19

//NRF24 (VSPI)
#define CE_RFID_PIN 27   // Define o pino CE do módulo NRF24L01
#define CSN_RFID_PIN 15 // Define o pino CSN do módulo NRF24L01

//Led
#define LED_PCB 4

//Sonar
#define ECHO_PIN 13
#define TRIG_PIN 15

#endif