// EspNowSerial.h
#ifndef EspNowSerial_h
#define EspNowSerial_h

#include <esp_now.h>
#include <WiFi.h>

struct DataStruct {
  char message[100];
};

class EspNowSerial {
  private:
    uint8_t *targetMAC;
    esp_now_peer_info_t peerInfo;

    static void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
      // Função chamada quando os dados são enviados
    }

    static void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
      DataStruct dataRecv;
      memcpy(&dataRecv, incomingData, sizeof(dataRecv));
      //Serial.println("Mensagem Recebida via ESP-NOW: " + String(dataRecv.message));
      Serial.println(String(dataRecv.message));
    }

  public:
    EspNowSerial(uint8_t *macAddress) {
      targetMAC = macAddress;
    }

    void initESPNow() {
      WiFi.disconnect();
      WiFi.mode(WIFI_STA);

      if (esp_now_init() != ESP_OK) {
        delay(2500);
        ESP.restart();
      }

      esp_now_register_send_cb(OnDataSent);
      esp_now_register_recv_cb(OnDataRecv);

      memcpy(peerInfo.peer_addr, targetMAC, 6);
      peerInfo.channel = 0;
      peerInfo.encrypt = false;

      if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        ESP.restart();
      }
    }

    void sendData(String message) {
      DataStruct dataSend;
      message.toCharArray(dataSend.message, sizeof(dataSend.message));
      esp_now_send(targetMAC, (uint8_t *)&dataSend, sizeof(DataStruct));
    }

    void disableESPNow() {
      esp_now_deinit(); // Desativa o ESP-NOW
    }
};

#endif
