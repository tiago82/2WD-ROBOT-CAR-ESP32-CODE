// EspNowSerial.h
#ifndef EspNowSerial_h
#define EspNowSerial_h

#include <esp_now.h>
#include <WiFi.h>
#include <Print.h>

struct DataStruct {
  char message[100];
};

class EspNowSerial : public Print { // A classe EspNowSerial herda da classe Print
  private:
    uint8_t *targetMAC;
    esp_now_peer_info_t peerInfo;

    //Print espNowSerial;

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

    size_t write(uint8_t c) override { // Sobrescreve a função write da classe Print
        // Esta implementação ainda é necessária para outros usos de write
        esp_now_send(targetMAC, &c, sizeof(uint8_t));
        return 1; // Retorna o número de bytes escritos
    }

    size_t write(const uint8_t *buffer, size_t size) override {
        esp_now_send(targetMAC, buffer, size);
        return size; // Retorna o número de bytes escritos
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

// class espNowSerialClass : public Print {
// public:
//   size_t write(uint8_t c) {
//     // Convert the uint8_t value to a String
//     String message = String(c);
//     // Implemente aqui a lógica para enviar 'c' usando ESP-NOW
//     espNowSerial.sendData(message);
//     return 1; // Retorna o número de bytes escritos
//   }
// };



#endif
