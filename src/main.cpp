#include <Arduino.h>
//#include "Functions.h"

#include "SingleEncoder.h"
#include "Pins.h"
#include "rfid_functions.h"



//#include "PID/motorPID.h"
#include "PID/automotorPID.h"

MFRC522 mfrc522(SS_RFID_PIN, RST_RFID_PIN);

void myFunction(){
    setupTestautoPID();
    while (true){
        loopTestautoPID();
    }
}


void setup() {
    Serial.begin(115200);

    SPI.begin(); // Inicializa a biblioteca SPI para comunicação com o módulo RFID
    mfrc522.PCD_Init(); // Inicializa o módulo RFID
    RFID::addCardFunction( 0x104a4913, myFunction);


    //setupPID();

    //setupTestautoPID();

 
}

void loop() {

    //loopPID();

    loopTestautoPID();
    RFID::checkRFIDPresent(mfrc522);

}


