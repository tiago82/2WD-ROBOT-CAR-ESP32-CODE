/*

  Esta classe é derivada da classe base EspNowSerial e possui funcionalidades adicionais para lidar com a comunicação ESP-NOW
  e a seleção das variáveis PID.

  Ela pega a classe principal que só se comunica e implementa a seleção de PID

*/

#ifndef MyDerivedClass_h
#define MyDerivedClass_h

#include "EspNowSerial.h"

class MyDerivedClass : public EspNowSerial
{
public:
  // ~MyDerivedClass();
  static uint8_t *macAddress2Esp32;

  MyDerivedClass(uint8_t *macAddress);
  static double kp1, kd1, ki1, setpoint1, setpoint2;
  static double kp2, kd2, ki2;
  static DataStruct dataSend;
  static DataStruct dataRecv;

  void init();
  static void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len);

  // Adicione métodos adicionais conforme necessário

private:
  // Adicione membros privados conforme necessário
  esp_now_peer_info_t peerInfo;
};

// ===========================================================================================================================

uint8_t *MyDerivedClass::macAddress2Esp32; //  inicializando esse ponteiro estático.
DataStruct MyDerivedClass::dataRecv;
DataStruct MyDerivedClass::dataSend;

double MyDerivedClass::kp1;
double MyDerivedClass::ki1;
double MyDerivedClass::kd1;
double MyDerivedClass::kp2;
double MyDerivedClass::ki2;
double MyDerivedClass::kd2;
double MyDerivedClass::setpoint1;
double MyDerivedClass::setpoint2;
void startMotor();
void StopMotor();
void gravarEPROM();

MyDerivedClass::MyDerivedClass(uint8_t *macAddress) : EspNowSerial(macAddress)
{ // Construtor da subclasse com parametro que passa o parametro para outra classe. Sem utilizar ": EspNowSerial(macAddress)" estava chamado o construtor sem parametro inexistente da outra classe base, ocasionando erro.
  macAddress2Esp32 = macAddress;
}

void MyDerivedClass::OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
  memcpy(&MyDerivedClass::dataRecv, incomingData, sizeof(MyDerivedClass::dataRecv));
  // Serial.println("Mensagem Recebida via ESP-NOW: " + String(dataRecv.message));
  Serial.println(String(MyDerivedClass::dataRecv.message)); // Exibe a mensagem recebida na porta serial

  String input = String(MyDerivedClass::dataRecv.message);

  input.trim();

  if (input.startsWith("kpt"))
  {
    MyDerivedClass::kp1 = input.substring(3).toFloat();
    MyDerivedClass::kp2 = MyDerivedClass::kp1;
    Serial.print("Novo valor de kp: ");
    Serial.println(MyDerivedClass::kp1);
    EspNowSerial::sendData("Novo valor de kp: " + String(MyDerivedClass::kp1));
  }
  else if (input.startsWith("kit"))
  {
    MyDerivedClass::ki1 = input.substring(3).toFloat();
    MyDerivedClass::ki2 = MyDerivedClass::ki1;
    Serial.print("Novo valor de ki: ");
    Serial.println(MyDerivedClass::ki1);
    EspNowSerial::sendData("Novo valor de ki: " + String(MyDerivedClass::ki1));
  }
  else if (input.startsWith("kdt"))
  {
    MyDerivedClass::kd1 = input.substring(3).toFloat();
    MyDerivedClass::kd2 = MyDerivedClass::kd1;
    Serial.print("Novo valor de kd: ");
    Serial.println(MyDerivedClass::kd1);
    EspNowSerial::sendData("Novo valor de kd: " + String(MyDerivedClass::kd1));
  }

  if (input.startsWith("kpa"))
  {
    MyDerivedClass::kp1 = input.substring(3).toFloat();
    Serial.print("Novo valor de kpa: ");
    Serial.println(MyDerivedClass::kp1);
    EspNowSerial::sendData("Novo valor de kpa: " + String(MyDerivedClass::kp1));
  }
  else if (input.startsWith("kia"))
  {
    MyDerivedClass::ki1 = input.substring(3).toFloat();
    Serial.print("Novo valor de kia: ");
    Serial.println(MyDerivedClass::ki1);
    EspNowSerial::sendData("Novo valor de kia: " + String(MyDerivedClass::ki1));
  }
  else if (input.startsWith("kda"))
  {
    MyDerivedClass::kd1 = input.substring(3).toFloat();
    Serial.print("Novo valor de kda: ");
    Serial.println(MyDerivedClass::kd1);
    EspNowSerial::sendData("Novo valor de kda: " + String(MyDerivedClass::kd1));
  }

  if (input.startsWith("kpb"))
  {
    MyDerivedClass::kp2 = input.substring(3).toFloat();
    Serial.print("Novo valor de kp: ");
    Serial.println(MyDerivedClass::kp2);
    EspNowSerial::sendData("Novo valor de kpb: " + String(MyDerivedClass::kp2));
  }
  else if (input.startsWith("kib"))
  {
    MyDerivedClass::ki2 = input.substring(3).toFloat();
    Serial.print("Novo valor de ki: ");
    Serial.println(MyDerivedClass::ki2);
    EspNowSerial::sendData("Novo valor de kib: " + String(MyDerivedClass::ki2));
  }
  else if (input.startsWith("kdb"))
  {
    MyDerivedClass::kd2 = input.substring(3).toFloat();
    Serial.print("Novo valor de kd: ");
    Serial.println(MyDerivedClass::kd2);
    EspNowSerial::sendData("Novo valor de kdb: " + String(MyDerivedClass::kd2));
  }

  else if (input.startsWith("set"))
  {
    MyDerivedClass::setpoint1 = input.substring(3).toFloat();
    MyDerivedClass::setpoint2 = MyDerivedClass::setpoint1;

    Serial.print("Novo valor de setpoint: ");
    Serial.println(MyDerivedClass::setpoint1);
    EspNowSerial::sendData("Novo valor de setpoint: " + String(MyDerivedClass::setpoint1));
  }
  else if (input.startsWith("sea"))
  {
    MyDerivedClass::setpoint1 = input.substring(3).toFloat();
    Serial.print("Novo valor de setpoint: ");
    Serial.println(MyDerivedClass::setpoint1);
    EspNowSerial::sendData("Novo valor de setpoint: " + String(MyDerivedClass::setpoint1));
  }
  else if (input.startsWith("seb"))
  {
    MyDerivedClass::setpoint2 = input.substring(3).toFloat();
    Serial.print("Novo valor de setpoint: ");
    Serial.println(MyDerivedClass::setpoint2);
    EspNowSerial::sendData("Novo valor de setpoint: " + String(MyDerivedClass::setpoint2));
  }
  else if (input.startsWith("r"))
  {
    esp_restart();
  }
  else if (input.startsWith("w"))
  {
    startMotor();
  }
  else if (input.startsWith("e"))
  {
    StopMotor();
  }
  else if (input.startsWith("sa"))
  {
    gravarEPROM();
  }
  // else
  // {
  //   char charArray[input.length() + 1];
  //   input.toCharArray(charArray, input.length() + 1);

  //   char *token = strtok(charArray, " ");

  //   if (token != NULL)
  //   {
  //     MyDerivedClass::kp1 = atof(token);
  //     token = strtok(NULL, " ");
  //   }

  //   if (token != NULL)
  //   {
  //     MyDerivedClass::ki1 = atof(token);
  //     token = strtok(NULL, " ");
  //   }

  //   if (token != NULL)
  //   {
  //     MyDerivedClass::kd1 = atof(token);
  //   }

  //   Serial.print(MyDerivedClass::kp1);
  //   Serial.print(" ");
  //   Serial.print(MyDerivedClass::ki1);
  //   Serial.print(" ");
  //   Serial.println(MyDerivedClass::kd1);
  //   EspNowSerial::sendData("KP: " + String(MyDerivedClass::kp1) + " KI: " + String(MyDerivedClass::ki1) + " KD: " + String(MyDerivedClass::kd1));
  // }
}

void MyDerivedClass::init()
{
  Serial.begin(115200);
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK)
  {
    delay(2500);
    ESP.restart();
  }

  esp_now_register_send_cb(MyDerivedClass::OnDataSent);
  esp_now_register_recv_cb(MyDerivedClass::OnDataRecv);

  memcpy(peerInfo.peer_addr, macAddress2Esp32, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK)
  {
    ESP.restart();
  }
}

#endif
