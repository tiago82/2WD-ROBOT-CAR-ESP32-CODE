#ifndef WIFI_AP_H
#define WIFI_AP_H

#include <WiFi.h>

class WIFIAP {
  public:
    WIFIAP(const char* ssid, const char* password);
    void begin();
    IPAddress getIP();

  private:
    const char* _ssid;
    const char* _password;
};

#endif
