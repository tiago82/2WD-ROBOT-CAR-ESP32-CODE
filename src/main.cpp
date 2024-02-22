/*
 *  Autor: Tiago
 *  Data: 01/01/2024
 *  Objetivo: Controle de robô com 2 motores DC com controle de velocidade e PID
 *  Plataforma: ESP32
 *  IDE: PlatformIO
 *  Bibliotecas:
 */

#include <Arduino.h>

#include <BluetoothSerial.h>
#include <NoDelay.h>
#include <PID_v1.h>
#include "Pins.h"
#include "rfid_functions.h"
#include <Ultrasonic.h>


// Shift + Alt + F format code

#define tagMu_1 "13 5A 43 10"
#define tagMuv_1 "B3 4D FE EC"
#define tagGirar_1 "A3 47 57 10"
#define tagNrf_1 "C3 5F 4D 10"
#define tagBluetooth_1 "03 7F E2 12"
#define tagSonar_1 "E3 80 B4 11"
#define tagSonarServo_1 "83 31 BB 11"

#define tagMu_2 "32 42 D6 4C"
#define tagMuv_2 "8C EE 80 47"
#define tagGirar_2 "33 D8 58 10"
#define tagNrf_2 "32 3E 96 4C"
#define tagBluetooth_2 "B3 69 78 11"
#define tagSonar_2 "73 35 54 10"
#define tagSonarServo_2 "13 14 BB 11"

#define tagMu_3 "32 42 D6 4C"
#define tagMuv_3 "8C EE 80 47"
#define tagGirar_3 "A3 47 57 10"
#define tagNrf_3 "32 3E 96 4C"
#define tagBluetooth_3 "03 24 60 10"
#define tagSonar_3 "13 49 4A 10"
#define tagSonarServo_3 "13 14 BB 11"

// Variáveis globais
double kp1 = 0.6;
double ki1 = 0.5;
double kd1 = 0.0;
double kp2 = 0.6;
double ki2 = 0.5;
double kd2 = 0.0;
double setpoint1 = 250;
double setpoint2 = 250;
double input1, output1;
double input2, output2;

int timeCountEncoder = 250; // Se necessário, ajuste o intervalo em milisegundos de contagem dos pulsos .
volatile int EncSpeed1 = 0;
volatile int EncSpeed2 = 0;
volatile int pulseCount1 = 0;
volatile int pulseCount2 = 0;
volatile int pulseTotalCountEncoder1 = 0;
volatile int pulseTotalCountEncoder2 = 0;
volatile unsigned long lastUpdateTime = 0;

noDelay ESPNOWmsgtime(1000); // Creats a noDelay varible set to 1000ms

String conteudo = "";
char btdata = 'a';
#define btnome "PROMETHEUS"

// const String *name_bt = "legal";

// estados
bool move = false;
bool frente = false;
bool tras = false;
bool viraE = false;
bool viraD = false;

MFRC522 mfrc522(SS_RFID_PIN, RST_RFID_PIN);
// MotorDriver motor(EN1, IN1, IN2, EN2, IN4, IN3);

Ultrasonic ultrasonic(TRIG_PIN, ECHO_PIN);

BluetoothSerial BT;

PID myPID1(&input1, &output1, &setpoint1, kp1, ki1, kd1, DIRECT);
PID myPID2(&input2, &output2, &setpoint2, kp2, ki2, kd2, DIRECT);

int OUTPUT_;

void bluetooth();
void bluetoothPID();
void sonar();
void reset();

void ICACHE_RAM_ATTR funcaoInterrupcao1()
{
  pulseCount1++;
  pulseTotalCountEncoder1++;
}
void ICACHE_RAM_ATTR funcaoInterrupcao2()
{
  pulseCount2++;
  pulseTotalCountEncoder2++;
}

void startEncoder(int pinEncoder1, int pinEncoder2)
{

  pinMode(pinEncoder2, INPUT);
  attachInterrupt(digitalPinToInterrupt(pinEncoder1), funcaoInterrupcao1, RISING);
  attachInterrupt(digitalPinToInterrupt(pinEncoder2), funcaoInterrupcao2, RISING);
}

void updateEncoder()
{
  unsigned long currentTime = millis();
  if (currentTime - lastUpdateTime >= timeCountEncoder)
  {
    // Serial.print("Pulsos por segundo: ");
    // Serial.println(pulseCountEncoder);
    EncSpeed1 = pulseCount1;
    EncSpeed2 = pulseCount2;
    pulseCount1 = 0;
    pulseCount2 = 0;
    lastUpdateTime = currentTime;
  }
}

int getdiferencetotalpulse()
{
  int diferenca1 = pulseTotalCountEncoder1 - pulseTotalCountEncoder2;
  return diferenca1;
}

void PIDinit()
{
  myPID1.SetOutputLimits(150, 500); // PWM 10bits vai de 0 a 1023
  myPID2.SetOutputLimits(150, 500);
  myPID1.SetMode(AUTOMATIC);
  myPID2.SetMode(AUTOMATIC);
}

void loopPID(int Input1, int Input2)
{
  input1 = Input1;
  input2 = Input2;
  myPID1.Compute();
  myPID2.Compute();
}

void startMotor()
{
  // motor.moveForward(move ? 0 : 300);  // test Operador ternário (? :) Se move for verdadeiro, escolhemos 0 (parar o motor). Se move for falso, escolhemos 300.
  // move = !move;
  PIDinit();
  // setpoint1 = 0;
  // setpoint2 = 0;

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN3, LOW);
  analogWrite(EN1, 250);
  analogWrite(EN1, 250);

  move = true;
  frente = true;
  tras = false;
  viraE = false;
  viraD = false;
}
void StopMotor()
{
  PIDinit();
  move = false;
  frente = false;
  tras = false;
  viraE = false;
  viraD = false;
  // motor.stop();
  //  resettotalpulse();
}

void viraDireita()
{
  PIDinit();
  move = true;
  frente = false;
  tras = false;
  viraE = false;
  viraD = true;
}
void viraEsquerda()
{
  PIDinit();
  move = true;
  frente = false;
  tras = false;
  viraE = true;
  viraD = false;
}
void re()
{
  PIDinit();
  move = true;
  frente = false;
  tras = true;
  viraE = false;
  viraD = false;
}

void rfid()
{
  if (mfrc522.PICC_IsNewCardPresent())
  {
    if (mfrc522.PICC_ReadCardSerial())
    {
      for (byte i = 0; i < mfrc522.uid.size; i++)
      {
        conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
        conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
      }
      conteudo.toUpperCase();
    }
  }
}

void ComputerPID()
{
  // dualpid.updatePID(getpulse1() * 1, getpulse2());

  int out1 = output1;
  int out2 = output2;
  int pulse1 = EncSpeed1;
  int pulse2 = EncSpeed2;

  // if (getdiferencetotalpulse() > 0) // menor que zero - vira direita
  // {
  //   out2 = dualpid.getOutput2() - 0.05*dualpid.getOutput2(); // reduz motor 2 para evitar virar esquerda
  // }
  // if (getdiferencetotalpulse() < 0) // maior que zero
  // {
  //   out2 = dualpid.getOutput1() - 0.05*dualpid.getOutput1() ;
  // }

  // if (OUTPUT_ != output2) // verificacao obsoleta
  // {
  //   OUTPUT_ = output2;
  //   if (frente)
  //   {
  //     // motor.setSpeed(out1, out2);
  //     motor.setSpeed(out1, out2);
  //   }
  //   if (tras)
  //   {
  //     motor.setSpeed(-out1, -out2);
  //   }
  //   if (viraE)
  //   {
  //     motor.setSpeed(out1, -out2);
  //   }
  //   if (viraD)
  //   {
  //     motor.setSpeed(-out1, out2);
  //   }
  // }
}

//======================== Setup ========================
void setup()
{

  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(LED_PCB, OUTPUT);

  digitalWrite(EN1, LOW);
  digitalWrite(EN2, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN3, LOW);

  // motor.stop();
  analogWriteResolution(10);
  startEncoder(M1_S2, M2_S1);

  SPI.begin();        // Inicializa a biblioteca SPI para comunicação com o módulo RFID
  mfrc522.PCD_Init(); // Inicializa o módulo RFID
  // RFID::addCardTwoFunctions( 0x104a4913, myFunction111 ,myFunction2);
  // RFID::addCardTwoFunctions(0x10602403, startMotor, StopMotor);

  // btsetup();
  //  SerialBT.setPin(pin_bt);
  // bluetooth();
  // bluetoothPID();
}

//======================== Loop ========================
void loop()
{
  updateEncoder();
  input1 = EncSpeed1;
  input2 = EncSpeed2;
  // btloop();

  RFID::checkRFIDPresent(mfrc522);
  if (move)
  {
    myPID1.Compute();
    myPID2.Compute();
    analogWrite(EN1, output1);
    analogWrite(EN2, output2);
  }

  rfid();

  if (conteudo.substring(1) == tagBluetooth_1 || conteudo.substring(1) == tagBluetooth_2 || conteudo.substring(1) == tagBluetooth_3)
  {
    // bluetooth();
    bluetoothPID();
  }
  if (conteudo.substring(1) == tagSonar_1 || conteudo.substring(1) == tagSonar_2 || conteudo.substring(1) == tagSonar_3)
  {
    sonar();
  }
}

void bluetooth()
{
  digitalWrite(LED_PCB, HIGH);
  delay(400);
  digitalWrite(LED_PCB, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  BT.begin(btnome);
  delay(1500);

  while (true)
  {
    if (btdata == 'a')
    {
      digitalWrite(LED_PCB, HIGH);
      delay(1000);
      digitalWrite(LED_PCB, LOW);
      delay(1000);
      if (BT.available())
      {
        btdata = BT.read();
      }
      conteudo = "";
      // rfid();
      // if (conteudo.substring(1) == tagBluetooth_1 || conteudo.substring(1) == tagBluetooth_2 || conteudo.substring(1) == tagBluetooth_3) {
      //   BT.disconnect();
      //   BT.end();
      //   reset();
      //   return;
      // }
    }

    else
    {
      if (BT.available())
      {
        btdata = BT.read();
      }

      if (btdata == '1')
      {
        analogWrite(EN1, 100);
        analogWrite(EN2, 100);
      }

      if (btdata == '2')
      {
        analogWrite(EN1, 150);
        analogWrite(EN2, 150);
      }

      if (btdata == '3')
      {
        analogWrite(EN1, 200);
        analogWrite(EN2, 200);
      }

      if (btdata == '4')
      {
        analogWrite(EN1, 250);
        analogWrite(EN2, 250);
      }

      if (btdata == '5')
      {
        analogWrite(EN1, 300);
        analogWrite(EN2, 300);
      }

      if (btdata == '6')
      {
        analogWrite(EN1, 350);
        analogWrite(EN2, 350);
      }

      if (btdata == '7')
      {
        analogWrite(EN1, 400);
        analogWrite(EN2, 400);
      }

      if (btdata == '8')
      {
        analogWrite(EN1, 450);
        analogWrite(EN2, 450);
      }

      if (btdata == '9')
      {
        analogWrite(EN1, 500);
        analogWrite(EN2, 500);
      }

      if (btdata == 'q')
      {
        analogWrite(EN1, 550);
        analogWrite(EN2, 550);
      }

      // Foward
      if (btdata == 'F')
      {
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
      }

      // Back
      else if (btdata == 'B')
      {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
      }

      // Left
      else if (btdata == 'L')
      {
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
      }

      // Right
      else if (btdata == 'R')
      {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
      }

      // Stop
      else if (btdata == 'S')
      {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
      }

      else if (btdata == 'V')
      {
        digitalWrite(LED_PCB, HIGH);
      }

      else if (btdata == 'v')
      {
        digitalWrite(LED_PCB, LOW);
      }

      else if (btdata == 'X' || btdata == 'x')
      {
        BT.disconnect();
        BT.end();
        // reset();
        return;
      }

      delay(20);
    }
  }
}

void bluetoothPID()
{
  digitalWrite(LED_PCB, HIGH);
  delay(100);
  digitalWrite(LED_PCB, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  myPID1.SetOutputLimits(150, 500); // PWM 10bits vai de 0 a 1023
  myPID2.SetOutputLimits(150, 500);
  myPID1.SetMode(AUTOMATIC);
  myPID2.SetMode(AUTOMATIC);

  BT.begin(btnome);
  delay(1500);

  while (true)
  {
    if (btdata == 'a')
    {
      digitalWrite(LED_PCB, HIGH);
      delay(1000);
      digitalWrite(LED_PCB, LOW);
      delay(1000);
      if (BT.available())
      {
        btdata = BT.read();
      }
      conteudo = "";
      // rfid();
      // if (conteudo.substring(1) == tagBluetooth_1 || conteudo.substring(1) == tagBluetooth_2 || conteudo.substring(1) == tagBluetooth_3) {
      //   BT.disconnect();
      //   BT.end();
      //   reset();
      //   return;
      // }
    }

    else
    {
      if (BT.available())
      {
        btdata = BT.read();
      }

      if (btdata == '1')
      {

        setpoint1 = 100;
        setpoint2 = 100;
      }

      if (btdata == '2')
      {
        setpoint1 = 150;
        setpoint2 = 150;
      }

      if (btdata == '3')
      {
        setpoint1 = 200;
        setpoint2 = 200;
      }

      if (btdata == '4')
      {
        setpoint1 = 250;
        setpoint2 = 250;
      }

      if (btdata == '5')
      {
        setpoint1 = 100;
        setpoint2 = 100;
      }

      if (btdata == '6')
      {
        setpoint1 = 100;
        setpoint2 = 100;
      }

      if (btdata == '7')
      {
        setpoint1 = 100;
        setpoint2 = 100;
      }

      if (btdata == '8')
      {
        setpoint1 = 100;
        setpoint2 = 100;
      }

      if (btdata == '9')
      {
        setpoint1 = 100;
        setpoint2 = 100;
      }

      if (btdata == 'q')
      {
        setpoint1 = 300;
        setpoint2 = 300;
      }

      // Foward
      if (btdata == 'F')
      {
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
      }

      // Back
      else if (btdata == 'B')
      {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
      }

      // Left
      else if (btdata == 'L')
      {
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
      }

      // Right
      else if (btdata == 'R')
      {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
      }

      // Stop
      else if (btdata == 'S')
      {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
      }

      else if (btdata == 'V')
      {
        digitalWrite(LED_PCB, HIGH);
      }

      else if (btdata == 'v')
      {
        digitalWrite(LED_PCB, LOW);
      }

      else if (btdata == 'X' || btdata == 'x')
      {
        BT.disconnect();
        BT.end();
        // reset();
        return;
      }

      delay(20);
      analogWrite(EN1, output1);
      analogWrite(EN2, output2);
      myPID1.Compute();
      myPID2.Compute();
    }
  }
}

int distance()
{
  digitalWrite(TRIG_PIN, LOW);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  return (pulseIn(ECHO_PIN, HIGH)) / 58;
}

void sonar()
{
  digitalWrite(LED_PCB, HIGH);
  delay(100);
  digitalWrite(LED_PCB, LOW);
  delay(1500);
  while (true)
  {
    if (distance() < 15)
    {
      while (true)
      {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        analogWrite(EN1, 300);
        analogWrite(EN2, 300);
        delay(500);
        if (random(2) == 0)
        {
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, HIGH);
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, HIGH);
        }
        else
        {
          digitalWrite(IN1, HIGH);
          digitalWrite(IN2, LOW);
          digitalWrite(IN3, HIGH);
          digitalWrite(IN4, LOW);
        }
        analogWrite(EN1, 300);
        analogWrite(EN2, 300);
        delay(500); // tempo giro
        break;
      }
    }
    else
    {
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      analogWrite(EN1, 300);
      analogWrite(EN2, 300);
      conteudo = "";
      rfid();
      if (conteudo.substring(1) == tagSonar_1 || conteudo.substring(1) == tagSonar_2 || conteudo.substring(1) == tagSonar_3)
      {
        reset();
        return;
      }
    }
  }
}

void reset()
{
  // speed1 = 0;
  // speed2 = 0;
  analogWrite(EN1, 0);
  analogWrite(EN2, 0);
  btdata = 'a';
  // resetData();
  digitalWrite(LED_PCB, HIGH);
  delay(100);
  digitalWrite(LED_PCB, LOW);
  delay(1500);
}