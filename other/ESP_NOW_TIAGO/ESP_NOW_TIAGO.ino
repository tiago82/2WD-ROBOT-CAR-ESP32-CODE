#include <esp_now.h>
#include <WiFi.h>

// Endereço MAC do outro ESP32 para comunicação
uint8_t macAddress2Esp32[] = { 0x48, 0xE7, 0x29, 0x9F, 0xEC, 0x20 };  // MAC DO GERE

// Estrutura de dados para enviar e receber mensagens
struct DataStruct {
  char message[100];  // Armazena uma mensagem de até 100 caracteres
};

DataStruct dataSend;  // Variável para os dados a serem enviados
DataStruct dataRecv;  // Variável para os dados recebidos

esp_now_peer_info_t peerInfo;  // Informações sobre o outro ESP32 na rede ESP-NOW

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  // Função chamada quando os dados são enviados
  // Aqui poderiam ser adicionadas ações após o envio, se necessário
}

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  // Função chamada quando os dados são recebidos via ESP-NOW
  memcpy(&dataRecv, incomingData, sizeof(dataRecv));  // Copia os dados recebidos para dataRecv
  //Serial.println("Mensagem Recebida via ESP-NOW: " + String(dataRecv.message)); // Exibe a mensagem recebida na porta serial
  Serial.println(String(dataRecv.message));  // Exibe a mensagem recebida na porta serial
}

void setup() {
  Serial.begin(115200);  // Inicializa a comunicação serial
  WiFi.disconnect();     // Desconecta de qualquer rede WiFi previamente conectada
  WiFi.mode(WIFI_STA);   // Configura o modo WiFi como Station (cliente)

  if (esp_now_init() != ESP_OK) {  // Inicializa o protocolo ESP-NOW
    delay(2500);                   // Espera por 2,5 segundos
    ESP.restart();                 // Reinicia o dispositivo em caso de falha na inicialização do ESP-NOW
  }

  esp_now_register_send_cb(OnDataSent);  // Registra a função callback para envio de dados
  esp_now_register_recv_cb(OnDataRecv);  // Registra a função callback para recebimento de dados

  memcpy(peerInfo.peer_addr, macAddress2Esp32, 6);  // Copia o endereço MAC do outro ESP32 para peerInfo
  peerInfo.channel = 0;                             // Define o canal de comunicação como 0
  peerInfo.encrypt = false;                         // Desativa a encriptação na comunicação

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {  // Adiciona o outro ESP32 como par na rede ESP-NOW
    ESP.restart();                              // Reinicia o dispositivo se falhar ao adicionar o peer
  }
}

void loop() {
  if (Serial.available() > 0) {                                                // Verifica se há dados disponíveis na porta serial
    memset(dataSend.message, 0, sizeof(dataSend.message));                     // Limpa o buffer de mensagem
    Serial.readBytesUntil('\n', dataSend.message, sizeof(dataSend.message));   // Lê a mensagem da porta serial até a quebra de linha
    esp_now_send(macAddress2Esp32, (uint8_t *)&dataSend, sizeof(DataStruct));  // Envia a mensagem para o outro ESP32 via ESP-NOW
  }
}