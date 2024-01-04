#include <Arduino.h>
//#include "Functions.h"

#include "SingleEncoder.h"
#include "Pins.h"
#include "rfid_functions.h"
#include <BluetoothSerial.h>

bool verdade = true;

//#include "PID/motorPID.h"
//#include "PID/automotorPID.h"

#include "PID/motorPIDBT.h"

MFRC522 mfrc522(SS_RFID_PIN, RST_RFID_PIN);


int a = 0;

void myFunction111(){
    a = 1;
}
void myFunction2(){
    analogWrite(EN2, 0);
    a = 0;
}


void setup() {
    Serial.begin(115200);

    SPI.begin(); // Inicializa a biblioteca SPI para comunicação com o módulo RFID
    mfrc522.PCD_Init(); // Inicializa o módulo RFID
    RFID::addCardTwoFunctions( 0x104a4913, myFunction111 ,myFunction2);


    //setupPID();
    setupPIDBT();
    
    

 
}

void loop() {

    //loopPID();

    //loopTestautoPID();
    RFID::checkRFIDPresent(mfrc522);

    if(a == 1){
    loopPID();
    }

    

}


