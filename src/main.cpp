#include <Arduino.h>
#include "Functions.h"


//EncoderReader encoderM2(M2_S1);
//BluetoothSerial SerialBT;

void setup() {
Serial.begin(115200);
    btsetup("dddd");
}



void loop() {
    btloop();
}

