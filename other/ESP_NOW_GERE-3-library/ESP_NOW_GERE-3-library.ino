#include <esp_now.h>
#include <WiFi.h>
#include "nowtest2.h"

EspNowSerial espnn;

void setup() {
  espnn.init();
  
}

void loop() {
  espnn.loop();

}
