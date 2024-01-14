#ifndef MyDerivedClass_h
#define MyDerivedClass_h

#include "EspNowSerial.h"

class MyDerivedClass : public EspNowSerial {
public:
  MyDerivedClass();
  ~MyDerivedClass();

 
  static double kp, kd, ki, setpoint;
  static DataStruct dataSend;
  static DataStruct dataRecv;

  void init();
  static void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len);
  static void sendData(String message);


  // Adicione métodos adicionais conforme necessário

private:
  // Adicione membros privados conforme necessário
  esp_now_peer_info_t peerInfo;
};

#endif // ===========================================================================================================================

DataStruct MyDerivedClass::dataRecv;
DataStruct MyDerivedClass::dataSend;

double MyDerivedClass::kp;
double MyDerivedClass::ki;
double MyDerivedClass::kd;
double MyDerivedClass::setpoint;


MyDerivedClass::MyDerivedClass() {
  // Inicialize membros adicionais, se necessário
}

MyDerivedClass::~MyDerivedClass() {
  // Adicione quaisquer limpezas necessárias ao destruir a instância da classe
}


void MyDerivedClass::OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  memcpy(&MyDerivedClass::dataRecv, incomingData, sizeof(MyDerivedClass::dataRecv));
  //Serial.println("Mensagem Recebida via ESP-NOW: " + String(dataRecv.message));
  Serial.println(String(MyDerivedClass::dataRecv.message));  // Exibe a mensagem recebida na porta serial

  String input = String(MyDerivedClass::dataRecv.message);

  input.trim();

  if (input.startsWith("kp")) {
    MyDerivedClass::kp = input.substring(2).toFloat();
    Serial.print("Novo valor de kp: ");
    Serial.println(MyDerivedClass::kp);
    MyDerivedClass::sendData("Novo valor de kp: " + String(MyDerivedClass::kp));
  } else if (input.startsWith("ki")) {
    MyDerivedClass::ki = input.substring(2).toFloat();
    Serial.print("Novo valor de ki: ");
    Serial.println(MyDerivedClass::ki);
    MyDerivedClass::sendData("Novo valor de ki: " + String(MyDerivedClass::ki));
  } else if (input.startsWith("kd")) {
    MyDerivedClass::kd = input.substring(2).toFloat();
    Serial.print("Novo valor de kd: ");
    Serial.println(MyDerivedClass::kd);
    MyDerivedClass::sendData("Novo valor de kd: " + String(MyDerivedClass::kd));
  } else if (input.startsWith("se")) {
    MyDerivedClass::setpoint = input.substring(2).toFloat();
    Serial.print("Novo valor de setpoint: ");
    Serial.println(MyDerivedClass::setpoint);
    MyDerivedClass::sendData("Novo valor de setpoint: " + String(MyDerivedClass::setpoint));
  } else {
    char charArray[input.length() + 1];
    input.toCharArray(charArray, input.length() + 1);

    char *token = strtok(charArray, " ");

    if (token != NULL) {
      MyDerivedClass::kp = atof(token);
      token = strtok(NULL, " ");
    }

    if (token != NULL) {
      MyDerivedClass::ki = atof(token);
      token = strtok(NULL, " ");
    }

    if (token != NULL) {
      MyDerivedClass::kd = atof(token);
    }

    Serial.print(MyDerivedClass::kp);
    Serial.print(" ");
    Serial.print(MyDerivedClass::ki);
    Serial.print(" ");
    Serial.println(MyDerivedClass::kd);
    MyDerivedClass::sendData("KP: " + String(MyDerivedClass::kp) + " KI: " + String(MyDerivedClass::ki) + " KD: " + String(MyDerivedClass::kd));
  }
}

void MyDerivedClass::sendData(String message) {
  DataStruct dataSend;
  message.toCharArray(dataSend.message, sizeof(dataSend.message));
  esp_now_send(macAddress2Esp32, (uint8_t *)&dataSend, sizeof(DataStruct));
}

void MyDerivedClass::init() {
  Serial.begin(115200);
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    delay(2500);
    ESP.restart();
  }

  esp_now_register_send_cb(MyDerivedClass::OnDataSent);
  esp_now_register_recv_cb(MyDerivedClass::OnDataRecv);

  memcpy(peerInfo.peer_addr, macAddress2Esp32, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    ESP.restart();
  }
}
