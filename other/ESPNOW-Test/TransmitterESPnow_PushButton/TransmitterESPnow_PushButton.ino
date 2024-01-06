
#include <esp_now.h>
#include <WiFi.h>


// Pino do botão pressionado
const int pushDown = 26;

// ENDEREÇO MAC do receptor - SUBSTITUA PELO SEU ENDEREÇO MAC DO RECEPTOR
uint8_t broadcastAddress[] = {0x70, 0xB8, 0xF6, 0x5B, 0xED, 0xB0};

// Estrutura dos dados a serem enviados
struct __attribute__((packed)) dataPacket {
  int state;
};

esp_now_peer_info_t peerInfo;

// Função de callback quando os dados são enviados
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nStatus do Último Pacote Enviado:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Entrega com Sucesso" : "Falha na Entrega");
}
 
void setup() {
  // Configura o pino do botão como entrada com pull-up
  pinMode(pushDown, INPUT_PULLUP);
  
  // Inicializa o Monitor Serial
  Serial.begin(115200);
 
  // Define o dispositivo como Estação Wi-Fi
  WiFi.mode(WIFI_STA);

  // Inicializa o ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Erro ao inicializar o ESP-NOW");
    return;
  }

  // Após a inicialização bem-sucedida do ESPNow, registramos o callback de envio para
  // obter o status do pacote transmitido
  esp_now_register_send_cb(OnDataSent);
  
  // Registra o receptor
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Adiciona o receptor        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Falha ao adicionar o receptor");
    return;
  }
}
 
void loop() {
  // Cria um pacote de dados
  dataPacket packet;
  // Lê o estado do botão e atribui ao pacote
  packet.state = digitalRead(pushDown);

  // Envia os dados via ESP-NOW para o receptor especificado
  esp_now_send(broadcastAddress, (uint8_t *) &packet, sizeof(packet));

  // Aguarda um pequeno intervalo antes de enviar o próximo pacote
  delay(30);
}
