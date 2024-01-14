/*

Código de Teste Sem Uso de Classe para Implementação do ESP-NOW com Seleção das Variáveis PID

*/
#include <esp_now.h>
#include <WiFi.h>

double kp, kd, ki, setpoint;

uint8_t macAddress2Esp32[] = { 0xA8, 0x42, 0xE3, 0xCB, 0x82, 0xEC };  // MAC DO TIAGO

struct DataStruct {
  char message[100];
};

DataStruct dataSend;
DataStruct dataRecv;

esp_now_peer_info_t peerInfo;

void sendData(String message) {
  DataStruct dataSend;
  message.toCharArray(dataSend.message, sizeof(dataSend.message));
  esp_now_send(macAddress2Esp32, (uint8_t *)&dataSend, sizeof(DataStruct));
}

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  // Função chamada quando os dados são enviados
}

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  memcpy(&dataRecv, incomingData, sizeof(dataRecv));
  //Serial.println("Mensagem Recebida via ESP-NOW: " + String(dataRecv.message));
  Serial.println(String(dataRecv.message));  // Exibe a mensagem recebida na porta serial

  String input = String(dataRecv.message);

  input.trim();

  if (input.startsWith("kp")) {
    kp = input.substring(2).toFloat();
    Serial.print("Novo valor de kp: ");
    Serial.println(kp);
    sendData("Novo valor de kp: " + String(kp));
  } else if (input.startsWith("ki")) {
    ki = input.substring(2).toFloat();
    Serial.print("Novo valor de ki: ");
    Serial.println(ki);
    sendData("Novo valor de ki: " + String(ki));
  } else if (input.startsWith("kd")) {
    kd = input.substring(2).toFloat();
    Serial.print("Novo valor de kd: ");
    Serial.println(kd);
    sendData("Novo valor de kd: " + String(kd));
  } else if (input.startsWith("se")) {
    setpoint = input.substring(2).toFloat();
    Serial.print("Novo valor de setpoint: ");
    Serial.println(setpoint);
    sendData("Novo valor de setpoint: " + String(setpoint));
  } else {
    char charArray[input.length() + 1];
    input.toCharArray(charArray, input.length() + 1);

    char *token = strtok(charArray, " ");

    if (token != NULL) {
      kp = atof(token);
      token = strtok(NULL, " ");
    }

    if (token != NULL) {
      ki = atof(token);
      token = strtok(NULL, " ");
    }

    if (token != NULL) {
      kd = atof(token);
    }

    Serial.print(kp);
    Serial.print(" ");
    Serial.print(ki);
    Serial.print(" ");
    Serial.println(kd);
    sendData("KP: " + String(kp) + " KI: " + String(ki) + " KD: " + String(kd));
  }
}

void espnowinit() {
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

void espnowloop() {

  if (Serial.available() > 0) {
    memset(dataSend.message, 0, sizeof(dataSend.message));
    Serial.readBytesUntil('\n', dataSend.message, sizeof(dataSend.message));
    esp_now_send(macAddress2Esp32, (uint8_t *)&dataSend, sizeof(DataStruct));
  }
}
