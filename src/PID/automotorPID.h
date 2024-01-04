#pragma once

#include <Arduino.h>
#include <Pins.h>

#include <PID_v1.h>
#include <PID_AutoTune_v0.h>
#include "SingleEncoder.h"




byte ATuneModeRemember=2;
double input=80, output=50, setpoint=100;
double kp=2,ki=0.5,kd=2;

double kpmodel=1.5, taup=100, theta[50];
double outputStart=5;
double aTuneStep=50, aTuneNoise=1, aTuneStartValue=100;
unsigned int aTuneLookBack=20;

boolean tuning = false;
unsigned long  modelTime, serialTime;

PID myPID(&input, &output, &setpoint,kp,ki,kd, DIRECT);
PID_ATune aTune(&input, &output);




//set to false to connect to the real world
boolean useSimulation = false;

//=========Prototipos==========
void changeAutoTune();
void AutoTuneHelper(boolean start);
void SerialReceive();
void SerialSend();
void DoModel();
void loopTestPID();
void PIDCompute();
//===============

void setupTestautoPID()
{
    pinMode(EN2, OUTPUT); // Motor2 Direito
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);

    //analogWrite(EN2,80);
    startEncoder(M2_S2);
    

  if(useSimulation)
  {
    for(byte i=0;i<50;i++)
    {
      theta[i]=outputStart;
    }
    modelTime = 0;
  }

  //Setup the pid 
  myPID.SetMode(AUTOMATIC);

  if(tuning)
  {
    tuning=false;
    changeAutoTune();
    tuning=true;
  }
  
  serialTime = 0;
  //Serial.begin(9600);
  setpoint = 100.0;

}


void loopTestautoPID(){

updateEncoder(PIDCompute);

  //===========

  unsigned long now = millis();

  if(!useSimulation)
  { //pull the input in from the real world
    input = getpulse();
  }
  
  if(tuning)
  {
    byte val = (aTune.Runtime());
    if (val!=0)
    {
      tuning = false;
    }
    if(!tuning)
    { //we're done, set the tuning parameters
      kp = aTune.GetKp();
      ki = aTune.GetKi();
      kd = aTune.GetKd();
      myPID.SetTunings(kp,ki,kd);
      AutoTuneHelper(false);
    }
  }
  else myPID.Compute();
  
  if(useSimulation)
  {
    theta[30]=output;
    if(now>=modelTime)
    {
      modelTime +=100; 
      DoModel();
    }
  }
  else
  {
     analogWrite(EN2,output); 
  }
  
  //send-receive with processing if it's time
  if(millis()>serialTime)
  {
    //SerialReceive(); // verifica de autorunning vai ser ativado
    SerialSend();
    serialTime+=500;
  }
}

void PIDCompute(){

 // Calcula a saída do PID para ajustar a velocidade
    input = getpulse();
    myPID.Compute();
    
    // Use a saída do PID para ajustar a velocidade dos motores (ajuste conforme necessário)
    analogWrite(EN2, output);
    SerialSend();
    


}


void changeAutoTune()
{
 if(!tuning)
  {
    //Set the output to the desired starting frequency.
    output=aTuneStartValue;
    aTune.SetNoiseBand(aTuneNoise);
    aTune.SetOutputStep(aTuneStep);
    aTune.SetLookbackSec((int)aTuneLookBack);
    AutoTuneHelper(true);
    tuning = true;
  }
  else
  { //cancel autotune
    aTune.Cancel();
    tuning = false;
    AutoTuneHelper(false);
  }
}

void AutoTuneHelper(boolean start)
{
  if(start)
    ATuneModeRemember = myPID.GetMode();
  else
    myPID.SetMode(ATuneModeRemember);
}


void SerialSend()
{
  Serial.print("setpoint: ");Serial.print(setpoint); Serial.print(" ");
  Serial.print("input: ");Serial.print(input); Serial.print(" ");
  Serial.print("output: ");Serial.print(output); Serial.print(" ");
  if(tuning){
    Serial.println("tuning mode");
  } else {
    Serial.print("kp: ");Serial.print(myPID.GetKp());Serial.print(" ");
    Serial.print("ki: ");Serial.print(myPID.GetKi());Serial.print(" ");
    Serial.print("kd: ");Serial.print(myPID.GetKd());Serial.println();
  }
}

void SerialReceive()
{
  if(Serial.available())
  {
   char b = Serial.read(); 
   Serial.flush(); 
   if((b=='1' && !tuning) || (b!='1' && tuning))changeAutoTune();
  }
}

void DoModel()
{
  //cycle the dead time
  for(byte i=0;i<49;i++)
  {
    theta[i] = theta[i+1];
  }
  //compute the input
  input = (kpmodel / taup) *(theta[0]-outputStart) + input*(1-1/taup) + ((float)random(-10,10))/100;

}

//=====================


void ajustarPID() {

  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');

    // Verifica se a entrada começa com "kp"
    if (input.startsWith("kp")) {
      String valueStr = input.substring(2);  // Pega os caracteres depois de "kp"
      kp = valueStr.toFloat();               // Converte para float
      Serial.print("Novo valor de kp: ");
      Serial.println(kp);
    }
    // Verifica se a entrada começa com "ki"
    else if (input.startsWith("ki")) {
      String valueStr = input.substring(2);  // Pega os caracteres depois de "ki"
      ki = valueStr.toFloat();               // Converte para float
      Serial.print("Novo valor de ki: ");
      Serial.println(ki);
    }
    // Verifica se a entrada começa com "kd"
    else if (input.startsWith("kd")) {
      String valueStr = input.substring(2);  // Pega os caracteres depois de "kd"
      kd = valueStr.toFloat();               // Converte para float
      Serial.print("Novo valor de kd: ");
      Serial.println(kd);
    }
    // Processa valores de kp, ki e kd separados por espaços
    else {
      char charArray[input.length() + 1];
      input.toCharArray(charArray, input.length() + 1);

      char *token = strtok(charArray, " ");

      // Obtendo kp
      if (token != NULL) {
        kp = atof(token);

        token = strtok(NULL, " ");
      }

      // Obtendo ki
      if (token != NULL) {
        ki = atof(token);

        token = strtok(NULL, " ");
      }

      // Obtendo kd
      if (token != NULL) {
        kd = atof(token);
      }
      Serial.print("kp: ");
      Serial.print(kp);
      Serial.print(" ki: ");
      Serial.print(ki);
      Serial.print(" kd: ");
      Serial.println(kd);

      myPID.SetTunings(kp, ki, kd);
    }
  }
}