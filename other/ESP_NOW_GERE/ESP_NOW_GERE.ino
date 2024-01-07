#include <esp_now.h>
#include <WiFi.h>

uint8_t macAddress2Esp32[] = { 0xA8, 0x42, 0xE3, 0xCB, 0x82, 0xEC };  // MAC DO TIAGO

struct DataStruct {
  char message[100];
};

DataStruct dataSend;
DataStruct dataRecv;

esp_now_peer_info_t peerInfo;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  // Função chamada quando os dados são enviados
}

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  memcpy(&dataRecv, incomingData, sizeof(dataRecv));
  //Serial.println("Mensagem Recebida via ESP-NOW: " + String(dataRecv.message));
  Serial.println(String(dataRecv.message));  // Exibe a mensagem recebida na porta serial
}

void setup() {
  Serial.begin(115200);
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    delay(2500);
    ESP.restart();
  }

  esp_now_register_send_cb(OnDataSent);
  esp_now_register_recv_cb(OnDataRecv);

  memcpy(peerInfo.peer_addr, macAddress2Esp32, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    ESP.restart();
  }
}

void loop() {
  if (Serial.available() > 0) {
    memset(dataSend.message, 0, sizeof(dataSend.message));
    Serial.readBytesUntil('\n', dataSend.message, sizeof(dataSend.message));
    esp_now_send(macAddress2Esp32, (uint8_t *)&dataSend, sizeof(DataStruct));
  }
}
