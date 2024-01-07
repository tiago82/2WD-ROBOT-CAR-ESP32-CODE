# EspNowSerial Library

## Overview
Esta biblioteca permite a comunicação entre dois ESP32 via ESP-NOW e Serial. Ela simplifica o envio e recebimento de mensagens entre dois dispositivos ESP32.

## Installation
1. Baixe o arquivo `EspNowSerial.h`.
2. Coloque o arquivo `EspNowSerial.h` no mesmo diretório do seu sketch do Arduino.
3. Inclua a biblioteca no seu sketch usando `#include "EspNowSerial.h"`.

## Usage
### Initializing ESP-NOW Communication
```cpp
#include "EspNowSerial.h"

// MAC address of the receiving ESP32
uint8_t macAddress2Esp32[] = { 0x48, 0xE7, 0x29, 0x9F, 0xEC, 0x20 }; // Replace with the target ESP32's MAC

EspNowSerial espNowSerial(macAddress2Esp32);

void setup() {
  Serial.begin(115200);
  espNowSerial.initESPNow(); // Initialize ESP-NOW communication
}

void loop() {
  // Your code logic here

  // Sending data via ESP-NOW
  if (Serial.available() > 0) {
    String message = Serial.readStringUntil('\n');
    espNowSerial.sendData(message);
  }
}
