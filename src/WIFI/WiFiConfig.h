#ifndef WIFI_CONFIG_H
#define WIFI_CONFIG_H

#include <WiFi.h>

void WifiInit(const char* ssid, const char* password);
void WifiInit(const char* ssid, const char* password, IPAddress ip, IPAddress gateway, IPAddress subnet);

#endif
