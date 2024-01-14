#include <Arduino.h>

// #include "EspNowSerial.h"
#include "MultiEncoder.h"
#include "PID/dualpid.h"
#include "Pins.h"
#include "rfid_functions.h"
// #include "Led.h"
#include "MotorDriver.h"
#include "SetPID_EspNow.h"

bool move = false;
double kp1, kd1, ki1, setpoint;
double kp2, kd2, ki2;

uint8_t macAddress2Esp32[] = {0xA8, 0x42, 0xE3, 0xCB, 0x82, 0xEC}; // Replace with the target ESP32's MAC
// EspNowSerial espNowSerial(macAddress2Esp32);
dualPID dualpid;
MyDerivedClass setpid2(macAddress2Esp32);
// String myString = MyDerivedClass::Serialcommand;

MFRC522 mfrc522(SS_RFID_PIN, RST_RFID_PIN);
MotorDriver motor(EN1, IN2, IN1, EN2, IN3, IN4);

void myFunction1()
{
  // motor.moveForward(move ? 0 : 300);  // Operador ternário (? :) Se move for verdadeiro, escolhemos 0 (parar o motor). Se move for falso, escolhemos 300.
  // move = !move;

  dualpid.init();
  move = true;
  
}
void myFunction2(){
  dualpid.deinit();
  move = false;
  setpid2.print("Funcao parar");
   motor.setSpeed(0, 0);
}

void printEspNow()
{
  dualpid.updatePID(getpulse1(), getpulse2());
  motor.setSpeed(dualpid.getOutput1(), dualpid.getOutput2());

  // setpid2.sendData(String(getpulse1()) + "," + String(getpulse2())); // Plot
  setpid2.print(String(dualpid.getOutput1()) + "," + String(dualpid.getInput1())); // Convert the integer to a string before sending
  // setpid.ajustarPIDBT(myString);
  // setpid2.sendData(String(kp));

  dualPID::kp1 = MyDerivedClass::kp;
  dualPID::kp2 = MyDerivedClass::kp;
  dualPID::ki1 = MyDerivedClass::ki;
  dualPID::ki2 = MyDerivedClass::ki;
  dualPID::kd1 = MyDerivedClass::kd;
  dualPID::kd2 = MyDerivedClass::kd;
  dualPID::setpoint = MyDerivedClass::setpoint;

}
//=============== Main ==================
void setup()
{
  setpid2.init();

  analogWriteResolution(10);
  startEncoder(M1_S2, M2_S1);

  SPI.begin();        // Inicializa a biblioteca SPI para comunicação com o módulo RFID
  mfrc522.PCD_Init(); // Inicializa o módulo RFID
  // RFID::addCardTwoFunctions( 0x104a4913, myFunction111 ,myFunction2);
  // RFID::addCardFunction( 0x104a4913, myFunction111);

  RFID::addCardTwoFunctions(0x10602403, myFunction1, myFunction2);
}

void loop()
{
  RFID::checkRFIDPresent(mfrc522);
  if (move)
  {
    updateEncoder(printEspNow);
  }
}
