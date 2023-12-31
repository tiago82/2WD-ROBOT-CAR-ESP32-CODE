#ifndef WIFI_CLIENT_CONNECTION_H
#define WIFI_CLIENT_CONNECTION_H

#include <WiFi.h>

class WiFiClientConnection {
  public:
    WiFiClientConnection(const char* ssid, const char* password);
    void connect();
    void setManualIP(IPAddress ip, IPAddress gateway, IPAddress subnet);
    bool isConnected();
    IPAddress getIP();

  private:
    const char* _ssid;
    const char* _password;
    bool _connected;
    IPAddress _manualIP;
    IPAddress _manualGateway;
    IPAddress _manualSubnet;
};

#endif
