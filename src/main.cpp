#include <Arduino.h>
#include <Preferences.h>
#include "MultiEncoder.h"
#include "PID/dualpid.h"
#include "Pins.h"
#include "rfid_functions.h"
#include "MotorDriver.h"
#include "SetPID_EspNow.h"
#include "bt.h"

// Shift + Alt + F format code

// Variáveis globais
double kp1, kp2;
double ki1, ki2;
double kd1, kd2;
double setpoint1, setpoint2;

// Chaves para armazenar valores na Flash
const char *KP1_KEY = "kp1";
const char *KI1_KEY = "ki1";
const char *KD1_KEY = "kd1";
const char *KP2_KEY = "kp2";
const char *KI2_KEY = "ki2";
const char *KD2_KEY = "kd2";
const char *SETPOINT1_KEY = "setpoint1";
const char *SETPOINT2_KEY = "setpoint2";

// estados
bool move = false;
bool frente = false;
bool tras = false;
bool viraE = false;
bool viraD = false;

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
  frente = true;
  tras = false;
  viraE = false;
  viraD = false;
}

void re()
{
  // motor.moveForward(move ? 0 : 300);  // Operador ternário (? :) Se move for verdadeiro, escolhemos 0 (parar o motor). Se move for falso, escolhemos 300.
  // move = !move;
  dualpid.init();
  move = true;
  frente = false;
  tras = true;
  viraE = false;
  viraD = false;
}
void viraDireita()
{
  dualpid.init();
  move = true;
  frente = false;
  tras = false;
  viraE = false;
  viraD = true;
}
void viraEsquerda()
{
  dualpid.init();
  move = true;
  frente = false;
  tras = false;
  viraE = true;
  viraD = false;
}

void StopMotor()
{
  dualpid.deinit();
  move = false;
  frente = false;
  tras = false;
  viraE = false;
  viraD = false;
  setpid2.sendData("Funcao parar ");
  setpid2.sendData("kpa: " + String(kp1) + " kia: " + String(ki1) + " kda: " + String(kd1) + " | " + " kpb: " + String(kp2) + " kib: " + String(ki2) + " kdb: " + String(kd2) + " | " + " setpoint1: " + String(setpoint1) + " setpoint2: " + String(setpoint2));
  motor.stop();
  resettotalpulse();
}

void gravarEPROM()
{
  preferences.begin("myApp", false);
  preferences.putDouble(KP1_KEY, kp1);
  preferences.putDouble(KI1_KEY, ki1);
  preferences.putDouble(KD1_KEY, kd1);
  preferences.putDouble(KP2_KEY, kp2);
  preferences.putDouble(KI2_KEY, ki2);
  preferences.putDouble(KD2_KEY, kd2);
  preferences.putDouble(SETPOINT1_KEY, setpoint1);
  preferences.putDouble(SETPOINT2_KEY, setpoint2);
  preferences.end();
  preferences.begin("myApp", false);
  setpid2.sendData("Constantes gravadas na EEPROM");
  setpid2.sendData("kpa: " + String(kp1) + " kia: " + String(ki1) + " kda: " + String(kd1) + " | " + " kpb: " + String(kp2) + " kib: " + String(ki2) + " kdb: " + String(kd2) + " | " + " setpoint1: " + String(setpoint1) + " setpoint2: " + String(setpoint2));
  preferences.end();
}

void printEspNow()
{
  dualpid.updatePID(getpulse1() * 1, getpulse2());

  int out1 = dualpid.getOutput1();
  int out2 = dualpid.getOutput2();
  int pulse1 = getpulse1();
  int pulse2 = getpulse2();

  // if (getdiferencetotalpulse() > 0) // menor que zero - vira direita
  // {
  //   out2 = dualpid.getOutput2() - 0.05*dualpid.getOutput2(); // reduz motor 2 para evitar virar esquerda
  // }
  // if (getdiferencetotalpulse() < 0) // maior que zero
  // {
  //   out2 = dualpid.getOutput1() - 0.05*dualpid.getOutput1() ;
  // }

  if (OUTPUT_ != dualpid.getOutput2())
  {
    OUTPUT_ = dualpid.getOutput2();
    if (frente)
    {
      motor.setSpeed(out1, out2);
    }
    if (tras)
    {
      motor.setSpeed(-out1, -out2);
    }
    if (viraE)
    {
      motor.setSpeed(out1, -out2);
    }
    if (viraD)
    {
      motor.setSpeed(-out1, out2);
    }
  }

  setpid2.sendData("input1:" + String(dualpid.getInput1()) + ", " + "output1:" + String(dualpid.getOutput1()) + ", " + "input2:" + String(dualpid.getInput2()) + ", " + "output2:" + String(dualpid.getOutput2()) + ", " + "setpoint:" + String(dualPID::setpoint1) + ", " + "diferença_contagem:" + String(getdiferencetotalpulse())); // exibe o valor do sensor
  // setpid2.sendData(String(gettotalpulse1()) + "," + String(gettotalpulse2())); // exibe o total de pulsos
  // setpid2.sendData(String(getdiferencetotalpulse())); // exibe o diferença de pulsos entre motores
  // setpid2.sendData(String(s(getpulse1(), getpulse2()))); // exibe distancia percorrida
  // setpid2.sendData("quantidade para a rotacao" + String(girarroborGraus(180)));

  dualPID::ki2 = kp2;
  dualPID::ki2 = ki2;
  dualPID::kd2 = kd2;
  dualPID::ki1 = kp2;
  dualPID::ki1 = ki2;
  dualPID::kd1 = kd2;
  dualPID::setpoint1 = setpoint1;
  dualPID::setpoint2 = setpoint2;
}

//=============== Main ==================
void setup()
{

  preferences.begin("myApp", false); // Open the preferences with the namespace "myApp"
  // Uncomment the next line to clear preferences (for testing purposes)
  // preferences.clear();

  // Read initial values from preferences
  kp1 = preferences.getDouble(KP1_KEY, 0.0);
  ki1 = preferences.getDouble(KI1_KEY, 0.0);
  kd1 = preferences.getDouble(KD1_KEY, 0.0);
  kp2 = preferences.getDouble(KP2_KEY, 0.0);
  ki2 = preferences.getDouble(KI2_KEY, 0.0);
  kd2 = preferences.getDouble(KD2_KEY, 0.0);
  setpoint1 = preferences.getDouble(SETPOINT1_KEY, 0.0);
  setpoint2 = preferences.getDouble(SETPOINT2_KEY, 0.0);
  preferences.end();

  setpid2.init();
  setpid2.sendData("kpa: " + String(kp1) + " kia: " + String(ki1) + " kda: " + String(kd1) + " | " + " kpb: " + String(kp2) + " kib: " + String(ki2) + " kdb: " + String(kd2) + " | " + " setpoint1: " + String(setpoint1) + " setpoint2: " + String(setpoint2));
  motor.stop();

  analogWriteResolution(10);
  startEncoder(M1_S2, M2_S1);

  SPI.begin();        // Inicializa a biblioteca SPI para comunicação com o módulo RFID
  mfrc522.PCD_Init(); // Inicializa o módulo RFID
  // RFID::addCardTwoFunctions( 0x104a4913, myFunction111 ,myFunction2);
  RFID::addCardFunction(0x104a4913, gravarEPROM);
  RFID::addCardTwoFunctions(0x10602403, startMotor, StopMotor);

  btsetup();

  MyDerivedClass::kp1 = kp1;
  MyDerivedClass::ki1 = ki1;
  MyDerivedClass::kd1 = kd1;
  MyDerivedClass::kp2 = kp2;
  MyDerivedClass::ki2 = ki2;
  MyDerivedClass::kd2 = kd2;
  MyDerivedClass::setpoint1 = setpoint1;
  MyDerivedClass::setpoint2 = setpoint2;
}

void loop()
{

  btloop();

  RFID::checkRFIDPresent(mfrc522);
  if (move)
  {
    updateEncoder(printEspNow);
  }
  kp1 = MyDerivedClass::kp1;
  ki1 = MyDerivedClass::ki1;
  kd1 = MyDerivedClass::kd1;
  kp2 = MyDerivedClass::kp2;
  ki2 = MyDerivedClass::ki2;
  kd2 = MyDerivedClass::kd2;
  setpoint1 = MyDerivedClass::setpoint1;
  setpoint2 = MyDerivedClass::setpoint2;
  dualPID::kp2 = kp2;
  dualPID::ki2 = ki2;
  dualPID::kd2 = kd2;
  dualPID::kp1 = kp1;
  dualPID::ki1 = ki1;
  dualPID::kd1 = kd1;
  dualPID::setpoint1 = setpoint1;
  dualPID::setpoint2 = setpoint2;

  //   if (s(getpulse1(), getpulse2()) >= 0.2)
  // {
  //   StopMotor();
  // }

  // if (frente)
  // {
  //   if (gettotalpulse1() >= 2000) // mudei contagem encoder logo edometria falta consetar
  //   {
  //     // frente = false;
  //     setpid2.sendData("totalpulsos1=" + String(gettotalpulse1()) + " totalpulsos2=" + String(gettotalpulse2()));
  //     StopMotor();

  //     gira = true;
  //     delay(500);
  //     // startMotor();
  //   }
  // }
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
