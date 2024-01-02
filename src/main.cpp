#include <Arduino.h>
//#include "Functions.h"
#include "PID/motorPID.h"
#include "SingleEncoder.h"
#include "Pins.h"

#include "rfid_functions.h"

MFRC522 mfrc522(SS_RFID_PIN, RST_RFID_PIN);

void doido1(){

    Serial.println("like1");
}

void doido2(){

    Serial.println("like2");
}

void doido3(){

    Serial.println("like3");
}

void setup() {
Serial.begin(115200);

  SPI.begin(); // Inicializa a biblioteca SPI para comunicação com o módulo RFID
  mfrc522.PCD_Init(); // Inicializa o módulo RF

//setupTestPID();

 RFID::addCardTwoFunctions(mfrc522, 0x104A4913,  doido1,  doido2);
 RFID::addCardFunction(mfrc522, 0x10602403, doido3);


}

void loop() {
//loopTestPID();

RFID::checkRFIDPresent2(mfrc522);

}


