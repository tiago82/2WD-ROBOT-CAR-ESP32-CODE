#include <Arduino.h>
#include <Preferences.h>
#include "MultiEncoder.h"
#include "PID/dualpid.h"
#include "Pins.h"
#include "rfid_functions.h"
#include "MotorDriver.h"
#include "SetPID_EspNow.h"

// Shift + Alt + F format code

// Variáveis globais
bool move = false;
double kp1, kp2;
double ki1, ki2;
double kd1, kd2;
double setpoint;

// Chaves para armazenar valores na Flash
const char *KP_KEY = "kp";
const char *KI_KEY = "ki";
const char *KD_KEY = "kd";
const char *SETPOINT_KEY = "setpoint";

// estados
bool frente = true;
bool gira = false;

// Endereço MAC do segundo ESP32
// uint8_t macAddress2Esp32[] = {0xA8, 0x42, 0xE3, 0xCB, 0x82, 0xEC};
uint8_t macAddress2Esp32[] = {0xB8, 0xD6, 0x1A, 0x47, 0x62, 0x8C}; // tiago ESP32 38 PIN

// Instâncias de classes
dualPID dualpid;
MyDerivedClass setpid2(macAddress2Esp32);
Preferences preferences;
MFRC522 mfrc522(SS_RFID_PIN, RST_RFID_PIN);
MotorDriver motor(EN1, IN1, IN2, EN2, IN4, IN3);

int OUTPUT_;

void startMotor()
{
  // motor.moveForward(move ? 0 : 300);  // Operador ternário (? :) Se move for verdadeiro, escolhemos 0 (parar o motor). Se move for falso, escolhemos 300.
  // move = !move;
  dualpid.init();
  move = true;
}

void StopMotor()
{
  dualpid.deinit();
  move = false;
  setpid2.sendData("Funcao parar ");
  setpid2.sendData("kp: " + String(dualPID::kp2) + "," + " ki: " + String(dualPID::ki2) + "," + " kd: " + String(dualPID::kd2) + "," + " setpoint: " + String(dualPID::setpoint));
  motor.stop();
  resettotalpulse();
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
  dualpid.updatePID(getpulse1()*0.99, getpulse2());

  int out1 = dualpid.getOutput1();
  int out2 = dualpid.getOutput2();
  int pulse1 = getpulse1();
  int pulse2 = getpulse2();

  if (getdiferencetotalpulse() > 0) // menor que zero - vira direita
  {
    out2 = dualpid.getOutput2() - 0.05*dualpid.getOutput2(); // reduz motor 2 para evitar virar esquerda
  }
  if (getdiferencetotalpulse() < 0) // maior que zero
  {
    out2 = dualpid.getOutput1() - 0.05*dualpid.getOutput1() ;
  }

  if (OUTPUT_ != dualpid.getOutput2())
  {
    OUTPUT_ = dualpid.getOutput2();
    if (frente)
    {
      motor.setSpeed(out1, out2);
    }
    // if (gira)
    // {
    //   motor.setSpeed(-dualpid.getOutput1(), -dualpid.getOutput2());
    // }
  }

  // setpid2.sendData("input2:" + String(dualpid.getInput2()) + "," + "output2:" + String(dualpid.getOutput2()) + "," + "setpoint:" + String(dualPID::setpoint)); // exibe o valor do sensor
  // setpid2.sendData(String(gettotalpulse1()) + "," + String(gettotalpulse2())); // exibe o total de pulsos
  setpid2.sendData(String(getdiferencetotalpulse())); // exibe o diferença de pulsos entre motores
  // setpid2.sendData(String(s(getpulse1(), getpulse2()))); // exibe distancia percorrida
  // setpid2.sendData("quantidade para a rotacao" + String(girarroborGraus(180)));

  dualPID::ki2 = kp2;
  dualPID::ki2 = ki2;
  dualPID::kd2 = kd2;
  dualPID::ki1 = kp2;
  dualPID::ki1 = ki2;
  dualPID::kd1 = kd2;
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
  RFID::addCardTwoFunctions(0x10602403, startMotor, StopMotor);
  MyDerivedClass::kp = kp2;
  MyDerivedClass::ki = ki2;
  MyDerivedClass::kd = kd2;
  MyDerivedClass::setpoint = setpoint;
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
  setpoint = MyDerivedClass::setpoint;
  dualPID::kp2 = kp2;
  dualPID::ki2 = ki2;
  dualPID::kd2 = kd2;
  dualPID::kp1 = kp2;
  dualPID::ki1 = ki2;
  dualPID::kd1 = kd2;
  dualPID::setpoint = setpoint;

  //   if (s(getpulse1(), getpulse2()) >= 0.2)
  // {
  //   StopMotor();
  // }

  if (frente)
  {
    if (gettotalpulse1() >= moverpordistancia(1))
    {
      // frente = false;
      setpid2.sendData("total " + String(gettotalpulse1()));
      StopMotor();
      
      gira = true;
      delay(500);
      // startMotor();
    }
  }
  // if (gira)
  // {
  //   if (gettotalpulse1() >= moverpordistancia(0.8))
  //   {
  //     frente = true;
  //     gira = false;
  //     setpid2.sendData("total " + String(gettotalpulse1()));
  //     StopMotor();
  //     delay(500);
  //   }
  // }
}
