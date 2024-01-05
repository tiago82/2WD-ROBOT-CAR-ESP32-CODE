#include <Arduino.h>
//#include "Functions.h"

//#include "SingleEncoder.h"
#include "MultiEncoder.h"
#include "Pins.h"
#include "rfid_functions.h"
//#include <BluetoothSerial.h>
#include "OTA.h"

#include "Led.h"
#include "webserialmenu.h"

#include "MotorDriver.h"

bool verdade = true;

#include "PID/motorPID.h"
//#include "PID/automotorPID.h"

//#include "PID/motorPIDBT.h"

MFRC522 mfrc522(SS_RFID_PIN, RST_RFID_PIN);
MotorDriver motor(EN1, IN2, IN1, EN2, IN3, IN4);

int a = 0;
bool updatenow = false;
bool move = false;

void myFunction111(){
    a = 1;
}
void myFunction3(){

    if(move == false){
    motor.moveForward(300);
    move = !move;
    }else
    {
    motor.moveForward(0);
    move = !move;
    }
}

void myFunction2(){
    analogWrite(EN2, 0);
    a = 0;
}

void OTAupdate(){

ledSetup();
acenderLed();
        setupOTA();
        while (true)
        {
           loopOTA();
        }
        
}

void setup() {
    Serial.begin(115200);
    analogWriteResolution(10);
    SPI.begin(); // Inicializa a biblioteca SPI para comunicação com o módulo RFID
    mfrc522.PCD_Init(); // Inicializa o módulo RFID
    //RFID::addCardTwoFunctions( 0x104a4913, myFunction111 ,myFunction2);

    RFID::addCardFunction( 0x104a4913, OTAupdate);
    RFID::addCardFunction( 0x10602403, myFunction3);

    startEncoder(M1_S1, M2_S1);

    //setupPID();
    //setupPIDBT();

    
    //setupwebserial();
    
    

 
}

void loop() {

    //loopPID();

    //loopTestautoPID();
    RFID::checkRFIDPresent(mfrc522);

    // if(a == 1){
    //     loopPID();
    // }

    updateEncoderPrint(); 

}


