#pragma once

#include <Arduino.h>
#include <Pins.h>

#include <PID_v1.h>
#include "SingleEncoder.h"
#include "rfid_functions.h"

#include <string.h>


byte ATuneModeRemember=2;
double input=80, output=50, setpoint=100;
double kp=2,ki=0.5,kd=2;

// double kpmodel=1.5, taup=100, theta[50];
// double outputStart=5;
// double aTuneStep=50, aTuneNoise=1, aTuneStartValue=100;
// unsigned int aTuneLookBack=20;

// boolean tuning = false;
// unsigned long  modelTime, serialTime;

PID myPID(&input, &output, &setpoint,kp,ki,kd, DIRECT);

void PIDfunction();
void ajustarPID();
void SerialSend();



void setupPID() {

    pinMode(EN2, OUTPUT); // Motor2 Direito
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);

    //analogWrite(EN2,80);
    startEncoder(M2_S2);

    myPID.SetMode(AUTOMATIC);



}


void loopPID() {

updateEncoder(PIDfunction); // Cada segundo que a funcao encoder calcula o executa a funcao 
analogWrite(EN2, output);

ajustarPID();


}

void PIDfunction(){

myPID.Compute();

}


void SerialSend()
{
  Serial.print("setpoint: ");Serial.print(setpoint); Serial.print(" ");
  Serial.print("input: ");Serial.print(input); Serial.print(" ");
  Serial.print("output: ");Serial.print(output); Serial.print(" ");
}


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
    else if (input.startsWith("se")) {
      String valueStr = input.substring(2);  // Pega os caracteres depois de "kd"
      setpoint = valueStr.toFloat();               // Converte para float
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
