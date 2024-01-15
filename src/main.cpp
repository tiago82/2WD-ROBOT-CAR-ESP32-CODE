#include <Arduino.h>

#include <Preferences.h>

Preferences preferences;

const char *KP_KEY = "kp";
const char *KI_KEY = "ki";
const char *KD_KEY = "kd";
const char *SETPOINT_KEY = "setpoint";

// #include "EspNowSerial.h"
#include "MultiEncoder.h"
#include "PID/dualpid.h"
#include "Pins.h"
#include "rfid_functions.h"
// #include "Led.h"
#include "MotorDriver.h"
#include "SetPID_EspNow.h"

#define SinglePID

bool move = false;
double kp1, kp2;
double ki1, ki2;
double kd1, kd2;

double setpoint;

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
void myFunction2()
{
  dualpid.deinit();
  move = false;

  setpid2.sendData("Funcao parar ");
  setpid2.sendData("kp: " + String(dualPID::kp2) + "," + " ki: " + String(dualPID::ki2) + "," + " kd: " + String(dualPID::kd2) + "," + " setpoint: " + String(dualPID::setpoint));

  motor.setSpeed(0, 0);
}

void gravarEPROM()
{
  preferences.begin("myApp", false);
  preferences.putDouble(KP_KEY, kp2);
  preferences.putDouble(KI_KEY, ki2);
  preferences.putDouble(KD_KEY, kd2);
  preferences.putDouble(SETPOINT_KEY, setpoint);
  preferences.end();

  setpid2.sendData("Constantes gravadas na EEPROM");
  setpid2.sendData(String(kp2) + "," + String(ki2) + "," + String(kd2) + "," + String(setpoint));
}

void printEspNow()
{
  dualpid.updatePID(getpulse1(), getpulse2());
  motor.setSpeed(dualpid.getOutput1(), dualpid.getOutput2());

  // setpid2.sendData(String(getpulse1()) + "," + String(getpulse2())); // Plot
  // setpid2.print("input1:" + String(dualpid.getInput1()) + "," + "output2:" + String(dualpid.getOutput1())); // Convert the integer to a string before sending
  // setpid.ajustarPIDBT(myString);
  // setpid2.sendData(String(kp));
  setpid2.sendData("input2:" + String(dualpid.getInput2()) + "," + "output2:" + String(dualpid.getOutput2()) + "," + "setpoint:" + String(dualPID::setpoint));

  dualPID::ki2 = kp2;
  dualPID::ki2 = ki2;
  dualPID::kd2 = kd2;
  dualPID::setpoint = setpoint;
}
//=============== Main ==================
void setup()
{

  preferences.begin("myApp", false); // Open the preferences with the namespace "myApp"

  // Uncomment the next line to clear preferences (for testing purposes)
  // preferences.clear();

  // Read initial values from preferences
  kp2 = preferences.getDouble(KP_KEY, 0.0);
  ki2 = preferences.getDouble(KI_KEY, 0.0);
  kd2 = preferences.getDouble(KD_KEY, 0.0);
  setpoint = preferences.getDouble(SETPOINT_KEY, 0.0);
  preferences.end();

  setpid2.init();
  setpid2.sendData("kp: " + String(kp2) + "," + " ki: " + String(ki2) + "," + " kd: " + String(kd2) + "," + " setpoint: " + String(setpoint));

  analogWriteResolution(10);
  startEncoder(M1_S2, M2_S1);

  SPI.begin();        // Inicializa a biblioteca SPI para comunicação com o módulo RFID
  mfrc522.PCD_Init(); // Inicializa o módulo RFID
  // RFID::addCardTwoFunctions( 0x104a4913, myFunction111 ,myFunction2);
  RFID::addCardFunction(0x104a4913, gravarEPROM);
  MyDerivedClass::kp = kp2;
  MyDerivedClass::ki = ki2;
  MyDerivedClass::kd = kd2;
  MyDerivedClass::setpoint = setpoint;
  dualPID::kp2 = kp2;
  dualPID::ki2 = ki2;
  dualPID::kd2 = kd2;
  dualPID::setpoint = setpoint;

  RFID::addCardTwoFunctions(0x10602403, myFunction1, myFunction2);
}

void loop()
{
  RFID::checkRFIDPresent(mfrc522);
  if (move)
  {
    updateEncoder(printEspNow);
  }
  kp2 = MyDerivedClass::kp;
  ki2 = MyDerivedClass::ki;
  kd2 = MyDerivedClass::kd;
  dualPID::ki2 = kp2;
  dualPID::ki2 = ki2;
  dualPID::kd2 = kd2;


  setpoint = MyDerivedClass::setpoint;
}
