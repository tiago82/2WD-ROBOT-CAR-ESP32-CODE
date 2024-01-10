#include <Arduino.h>
#include "MultiEncoder.h"
#include "PID/dualpid.h"
#include "Pins.h"
#include "rfid_functions.h"
#include "EspNowSerial.h"
//#include "Led.h"
#include "MotorDriver.h"
#include "SerialSetPID.h"

bool move = false;

uint8_t macAddress2Esp32[] = { 0xA8, 0x42, 0xE3, 0xCB, 0x82, 0xEC }; // Replace with the target ESP32's MAC
EspNowSerial espNowSerial(macAddress2Esp32);
dualPID dualpid;
SerialSetPID setpid;
String myString = EspNowSerial::Serialcommand;

MFRC522 mfrc522(SS_RFID_PIN, RST_RFID_PIN);
MotorDriver motor(EN1, IN2, IN1, EN2, IN3, IN4);

void myFunction() {
    //motor.moveForward(move ? 0 : 300);  // Operador ternário (? :) Se move for verdadeiro, escolhemos 0 (parar o motor). Se move for falso, escolhemos 300.
   // move = !move;

    dualpid.init();
    move = true;
}

void printEspNow(){

    dualpid.updatePID(getpulse1(), getpulse2());
    motor.setSpeed(dualpid.getOutput1(), dualpid.getOutput2());

    espNowSerial.sendData(String(getpulse1())+","+String(getpulse2())); // Plot

   // espNowSerial.print(String(dualpid.getOutput1())+","+String(dualpid.getInput1())); // Convert the integer to a string before sending

   setpid.ajustarPIDBT(myString);

    double kp, ki, kd;
    std::tie(kp, ki, kd) = setpid.getconstants();
   
}

void setup() {

    espNowSerial.initESPNow();

    analogWriteResolution(10);
    startEncoder(M1_S2, M2_S1);

    SPI.begin(); // Inicializa a biblioteca SPI para comunicação com o módulo RFID
    mfrc522.PCD_Init(); // Inicializa o módulo RFID
    //RFID::addCardTwoFunctions( 0x104a4913, myFunction111 ,myFunction2);
    //RFID::addCardFunction( 0x104a4913, myFunction111);

    RFID::addCardFunction( 0x10602403, myFunction);

}

void loop() {

    RFID::checkRFIDPresent(mfrc522);
    if(move){updateEncoder(printEspNow);}    

}



