#include "WIFIAP.h"

WIFIAP::WIFIAP(const char* ssid, const char* password)
  : _ssid(ssid), _password(password) {}

void WIFIAP::begin() {
  Serial.begin(115200);
  delay(1000);

  // Start Access Point
  WiFi.mode(WIFI_AP);
  WiFi.softAP(_ssid, _password);

  Serial.println("Access Point Started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());
}

IPAddress WIFIAP::getIP() {
  return WiFi.softAPIP();
}
