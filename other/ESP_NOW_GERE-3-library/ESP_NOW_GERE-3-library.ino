#include <esp_now.h>
#include <WiFi.h>
//#include "nowtest2.h"
//#include "ESPNOWSERIAL.h"

#include "operation.h"

MyDerivedClass adss;

void setup() {
  adss.init();
  
}

void loop() {
  adss.loop();

}
