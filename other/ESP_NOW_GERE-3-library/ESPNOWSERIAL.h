#ifndef EspNowSerial_h
#define EspNowSerial_h

#include <esp_now.h>
#include <WiFi.h>

struct DataStruct {
  char message[100];
};

class EspNowSerial {
public:
  EspNowSerial();
  ~EspNowSerial();

  void init();
  void loop();
  //static double kp, kd, ki, setpoint;
  static DataStruct dataSend;
  static DataStruct dataRecv;
  static uint8_t macAddress2Esp32[6];

  static void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
  static void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len);
  static void sendData(String message);


private:


  esp_now_peer_info_t peerInfo;
};

#endif

uint8_t EspNowSerial::macAddress2Esp32[6] = { 0xA8, 0x42, 0xE3, 0xCB, 0x82, 0xEC };

DataStruct EspNowSerial::dataSend;
DataStruct EspNowSerial::dataRecv;
// double EspNowSerial::kp;
// double EspNowSerial::ki;
// double EspNowSerial::kd;
// double EspNowSerial::setpoint;


EspNowSerial::EspNowSerial() {
  // // Configurar o endereço MAC do ESP32 remoto
  // macAddress2Esp32[0] = 0xA8;
  // macAddress2Esp32[1] = 0x42;
  // macAddress2Esp32[2] = 0xE3;
  // macAddress2Esp32[3] = 0xCB;
  // macAddress2Esp32[4] = 0x82;
  // macAddress2Esp32[5] = 0xEC;
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

  // String input = String(EspNowSerial::dataRecv.message);

  // input.trim();

  // if (input.startsWith("kp")) {
  //   EspNowSerial::kp = input.substring(2).toFloat();
  //   Serial.print("Novo valor de kp: ");
  //   Serial.println(EspNowSerial::kp);
  //   EspNowSerial::sendData("Novo valor de kp: " + String(EspNowSerial::kp));
  // } else if (input.startsWith("ki")) {
  //   EspNowSerial::ki = input.substring(2).toFloat();
  //   Serial.print("Novo valor de ki: ");
  //   Serial.println(EspNowSerial::ki);
  //   EspNowSerial::sendData("Novo valor de ki: " + String(EspNowSerial::ki));
  // } else if (input.startsWith("kd")) {
  //   EspNowSerial::kd = input.substring(2).toFloat();
  //   Serial.print("Novo valor de kd: ");
  //   Serial.println(EspNowSerial::kd);
  //   EspNowSerial::sendData("Novo valor de kd: " + String(EspNowSerial::kd));
  // } else if (input.startsWith("se")) {
  //   EspNowSerial::setpoint = input.substring(2).toFloat();
  //   Serial.print("Novo valor de setpoint: ");
  //   Serial.println(EspNowSerial::setpoint);
  //   EspNowSerial::sendData("Novo valor de setpoint: " + String(EspNowSerial::setpoint));
  // } else {
  //   char charArray[input.length() + 1];
  //   input.toCharArray(charArray, input.length() + 1);

  //   char *token = strtok(charArray, " ");

  //   if (token != NULL) {
  //     EspNowSerial::kp = atof(token);
  //     token = strtok(NULL, " ");
  //   }

  //   if (token != NULL) {
  //     EspNowSerial::ki = atof(token);
  //     token = strtok(NULL, " ");
  //   }

  //   if (token != NULL) {
  //     EspNowSerial::kd = atof(token);
  //   }

  //   Serial.print(EspNowSerial::kp);
  //   Serial.print(" ");
  //   Serial.print(EspNowSerial::ki);
  //   Serial.print(" ");
  //   Serial.println(EspNowSerial::kd);
  //   EspNowSerial::sendData("KP: " + String(EspNowSerial::kp) + " KI: " + String(EspNowSerial::ki) + " KD: " + String(EspNowSerial::kd));
  // }
}
