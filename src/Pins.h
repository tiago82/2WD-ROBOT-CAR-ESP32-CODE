/*
    Este arquivo contém as definições dos pinos utilizados no projeto do  robô 2wd com ESP32.
    Aqui estão definidos os pinos para os motores, encoders, RFID, NRF24, LED e sonar.
*/

#ifndef PINS_H
#define PINS_H

#include <Arduino.h>

// Motor
#define EN1 22 // Motor1 Esquerdo
#define IN1 25
#define IN2 26

#define EN2 21 // Motor2 Direito
#define IN3 32
#define IN4 33

// Encoder
#define M1_S1 1 // TX0 - M1 Motor Esquerdo
#define M1_S2 3 // RX0

#define M2_S1 17 // TX2 - M2 Motor Direito
#define M2_S2 16 // RX2

// RFID (HSPI)
#define SS_RFID_PIN 5  // Define o pino SDA do MFRC522
#define RST_RFID_PIN 2 // Define o pino RST do MFRC522

#define RFID_SCK 18
#define RFID_MOSI 23
#define RFID_MISO 19

// NRF24 (VSPI)
#define CE_RFID_PIN 27  // Define o pino CE do módulo NRF24L01
#define CSN_RFID_PIN 15 // Define o pino CSN do módulo NRF24L01

// Led
#define LED_PCB 4

// Sonar
#define ECHO_PIN 13
#define TRIG_PIN 15

#endif