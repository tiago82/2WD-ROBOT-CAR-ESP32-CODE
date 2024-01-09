#include <Arduino.h>
#include "MultiEncoder.h"
#include "Pins.h"
#include "rfid_functions.h"
#include "EspNowSerial.h"
#include "Led.h"
#include "webserialmenu.h"
#include "MotorDriver.h"
bool verdade = true;

#include "PID/dualpid.h"

uint8_t macAddress2Esp32[] = { 0xA8, 0x42, 0xE3, 0xCB, 0x82, 0xEC }; // Replace with the target ESP32's MAC
EspNowSerial espNowSerial(macAddress2Esp32);
dualPID dualpid;

MFRC522 mfrc522(SS_RFID_PIN, RST_RFID_PIN);
MotorDriver motor(EN1, IN2, IN1, EN2, IN3, IN4);

int a = 0;
bool move = false;

void myFunction111(){
    a = 1;
}
void myFunction3() {
    //motor.moveForward(move ? 0 : 300);  // Operador ternário (? :) Se move for verdadeiro, escolhemos 0 (parar o motor). Se move for falso, escolhemos 300.
   // move = !move;

motor.setSpeed(move ? dualpid.getOutput1() : 0, move ? dualpid.getOutput2() : 0); //Operador ternário (? :)
move = !move;
    
}

void myFunction2(){
    analogWrite(EN2, 0);
    a = 0;
}

void printEspNow(){
    //dualpid.setInput1(getpulse1());
    //dualpid.setInput2(getpulse2());
    dualpid.updatePID(getpulse1(), getpulse2());
    motor.setSpeed(dualpid.getOutput1(), dualpid.getOutput2());

   

    espNowSerial.sendData(String(getpulse1())+","+String(getpulse2())); // Plot
    
    //espNowSerial.sendData(String(dualpid.getOutput1())+","+String(dualpid.getInput1())); // Convert the integer to a string before sending
    
    //espNowSerial.sendData("motor2: ");
    
}

void setup() {
    //Serial.begin(115200);

    //espNowSerial.initESPNow(); // Initialize ESP-NOW communication

    analogWriteResolution(10);

    SPI.begin(); // Inicializa a biblioteca SPI para comunicação com o módulo RFID
    mfrc522.PCD_Init(); // Inicializa o módulo RFID
    //RFID::addCardTwoFunctions( 0x104a4913, myFunction111 ,myFunction2);

    RFID::addCardFunction( 0x104a4913, myFunction111);
    RFID::addCardFunction( 0x10602403, myFunction3);

    startEncoder(M1_S1, M2_S1);

    
    //setupPIDBT();

    
    //setupwebserial();
    espNowSerial.initESPNow();
    
    dualpid.setup();


}


void loop() {

    

    //loopTestautoPID();
    RFID::checkRFIDPresent(mfrc522);

    // if(a == 1){
    //     loopPID();
    // }

    updateEncoder(printEspNow);

    

}




