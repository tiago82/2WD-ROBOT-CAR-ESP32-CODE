#include <esp_now.h>
#include <WiFi.h>

#include "SetPID_EspNow.h"



uint8_t macAddress2Esp32[] = {0xA8, 0x42, 0xE3, 0xCB, 0x82, 0xEC}; // Replace with the target ESP32's MAC
MyDerivedClass adss2(macAddress2Esp32);


void setup() {
  adss2.init();
  
}

void loop() {
  adss2.loop();

}
