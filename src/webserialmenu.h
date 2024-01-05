#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WebSerial.h>
#include "Pins.h"


AsyncWebServer server(80);

void recvMsg(uint8_t *data, size_t len){
  WebSerial.println("Received Data...");
  String d = "";
  for(int i=0; i < len; i++){
    d += char(data[i]);
  }
  WebSerial.println(d);
  if (d == "ON"){
    digitalWrite(LED_PCB, HIGH);
  }
  if (d=="OFF"){
    digitalWrite(LED_PCB, LOW);
  }
}


void setupwebserial() {
    WebSerial.begin(&server);
    WebSerial.msgCallback(recvMsg);
    server.begin();
}