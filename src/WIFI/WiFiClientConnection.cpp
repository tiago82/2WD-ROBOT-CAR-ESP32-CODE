#include "WiFiClientConnection.h"

WiFiClientConnection::WiFiClientConnection(const char* ssid, const char* password)
  : _ssid(ssid), _password(password), _connected(false) {}

void WiFiClientConnection::connect() {
  Serial.begin(115200);
  delay(1000);

  if (_manualIP == (uint32_t)0) {
    WiFi.begin(_ssid, _password);
  } else {
    WiFi.config(_manualIP, _manualGateway, _manualSubnet);
    WiFi.begin(_ssid, _password);
  }

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected");
  _connected = true;
}

void WiFiClientConnection::setManualIP(IPAddress ip, IPAddress gateway, IPAddress subnet) {
  _manualIP = ip;
  _manualGateway = gateway;
  _manualSubnet = subnet;
}

bool WiFiClientConnection::isConnected() {
  return _connected;
}

IPAddress WiFiClientConnection::getIP() {
  return WiFi.localIP();
}
