#include <Arduino.h>
#include "Functions.h"

MotorDriver motor(EN1, IN2, IN1, EN2, IN3, IN4);// EN1 IN1, IN2, EN2, IN3, IN4) (LEFT, RIGHT)
EncoderReader encoderM1(M1_S1);
//EncoderReader encoderM2(M2_S1);
//BluetoothSerial SerialBT;

void setup() {
Serial.begin(115200);
    btsetup("dddd");
}



void loop() {
    btloop();
}

