
#include <esp_now.h>
#include <WiFi.h>

// Pino do LED
const int lightME = 15;

// Estrutura dos dados recebidos
struct __attribute__((packed)) dataPacket {
  int state; // Estado recebido
};

// Função de callback executada ao receber dados
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  // Cria uma estrutura para armazenar os dados recebidos
  dataPacket packet;
  // Copia os dados recebidos para a estrutura
  memcpy(&packet, incomingData, sizeof(packet));
  // Exibe o estado recebido no Monitor Serial
  Serial.print("Botão: ");
  Serial.println(packet.state);
  // Define o estado do LED de acordo com o estado recebido
  digitalWrite(lightME, packet.state);
}

void setup() {
  // Inicializa o Monitor Serial
  Serial.begin(115200);
  // Configura o pino do LED como saída
  pinMode(lightME, OUTPUT);
  
  // Define o dispositivo como Estação Wi-Fi
  WiFi.mode(WIFI_STA);

  // Inicializa o ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Erro ao inicializar o ESP-NOW");
    return;
  }
  
  // Após a inicialização bem-sucedida do ESPNow, registramos o callback de recebimento para
  // obter informações do pacote recebido
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  // Vazio, já que toda a lógica de recebimento de dados é tratada no callback de recebimento
}
