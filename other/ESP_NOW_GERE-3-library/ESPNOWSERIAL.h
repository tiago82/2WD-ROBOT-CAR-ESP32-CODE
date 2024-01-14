/*

  Código de Teste para Comunicação ESP-NOW usando Classe.

  Este código é destinado ao teste de comunicação via ESP-NOW, projetado para ser usado com a subclasse SetPID_EspNow.h.

*/

#ifndef EspNowSerial_h
#define EspNowSerial_h

#include <esp_now.h>
#include <WiFi.h>

struct DataStruct {
  char message[100];
};

class EspNowSerial : public Print {
public:
  static DataStruct dataSend;
  static DataStruct dataRecv;
  static uint8_t *macAddress2Esp32;


  EspNowSerial(uint8_t *macAddress);
  ~EspNowSerial();

  void init();
  void loop();
  static void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
  static void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len);
  static void sendData(String message);
  void disableESPNow() {
    esp_now_deinit();  // Desativa o ESP-NOW
  }

  size_t write(uint8_t c) override {  // Sobrescreve a função write da classe Print
    // Esta implementação ainda é necessária para outros usos de write
    esp_now_send(macAddress2Esp32, &c, sizeof(uint8_t));
    return 1;  // Retorna o número de bytes escritos
  }

  size_t write(const uint8_t *buffer, size_t size) override {
    esp_now_send(macAddress2Esp32, buffer, size);
    return size;  // Retorna o número de bytes escritos
  }
private:
  esp_now_peer_info_t peerInfo;
};

#endif

uint8_t *EspNowSerial::macAddress2Esp32;
DataStruct EspNowSerial::dataSend;
DataStruct EspNowSerial::dataRecv;


EspNowSerial::EspNowSerial(uint8_t *macAddress) {
  macAddress2Esp32 = macAddress;
}

EspNowSerial::~EspNowSerial() {
  // Adicionar quaisquer limpezas necessárias ao destruir a instância da classe
}

void EspNowSerial::init() {
  Serial.begin(115200);
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    delay(2500);
    ESP.restart();
  }

  esp_now_register_send_cb(EspNowSerial::OnDataSent);
  esp_now_register_recv_cb(EspNowSerial::OnDataRecv);

  memcpy(peerInfo.peer_addr, macAddress2Esp32, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    ESP.restart();
  }
}

void EspNowSerial::loop() {
  if (Serial.available() > 0) {
    memset(dataSend.message, 0, sizeof(dataSend.message));
    Serial.readBytesUntil('\n', dataSend.message, sizeof(dataSend.message));
    esp_now_send(macAddress2Esp32, (uint8_t *)&dataSend, sizeof(DataStruct));
  }
}

void EspNowSerial::sendData(String message) {
  DataStruct dataSend;
  message.toCharArray(dataSend.message, sizeof(dataSend.message));
  esp_now_send(macAddress2Esp32, (uint8_t *)&dataSend, sizeof(DataStruct));
}

void EspNowSerial::OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  // Função chamada quando os dados são enviados
}

void EspNowSerial::OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  memcpy(&EspNowSerial::dataRecv, incomingData, sizeof(EspNowSerial::dataRecv));
  //Serial.println("Mensagem Recebida via ESP-NOW: " + String(dataRecv.message));
  Serial.println(String(EspNowSerial::dataRecv.message));  // Exibe a mensagem recebida na porta serial
}
