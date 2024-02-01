# 2WD Robot Car ESP32 - Projeto Controlador PID para Robô utilizando ESP32 e PlatformIO
## Descrição

Este projeto implementa um controlador Proporcional, Integral e Derivativo (PID) para ajustar a velocidade das rodas de um robô, especialmente desenvolvido para a plataforma ESP32 usando o ambiente de desenvolvimento PlatformIO. O controle PID é uma técnica eficaz em sistemas dinâmicos, proporcionando uma maior precisão no movimento do robô. Com o uso do PID, é possível alcançar uma movimentação mais suave, reduzindo erros e permitindo que o robô mantenha trajetórias, como andar em linha reta, com maior acurácia.

## Componentes Necessários

- ESP32 (Microcontrolador Principal)
- ESP32 ou ESP8266 para setar PID remotamente(opcional)
- Driver Ponte H
- Motores com Encoder
- Modulo RFID(opcional)

## Funcionamento

O controlador PID é composto por três componentes principais:

1. **Proporcional (P):** Calcula o erro atual, multiplicando-o por um ganho proporcional. Isso contribui para uma resposta rápida às variações.

2. **Integral (I):** Soma os erros passados ao longo do tempo, multiplicados por um ganho integral. Isso ajuda a corrigir o viés acumulado ao longo do tempo.

3. **Derivativo (D):** Prevê a tendência futura do erro, multiplicando a taxa de mudança do erro por um ganho derivativo. Isso ajuda a prevenir oscilações excessivas.

A saída do controlador PID é a soma ponderada desses três componentes.
 
# Estrutura do Projeto

O projeto está organizado para ser utilizado com a plataforma ESP32 e o ambiente de desenvolvimento PlatformIO. A estrutura inclui:

- `src/main.cpp`: Script principal que executa o controlador PID no ESP32.
- `src/MotorDriver.h`: Fornece funcionalidades para o controle dos motores do robô.
- `src/MultiEncoder.h`: Responsável por obter leituras dos encoders.
- `src/EspNowSerial.h`: Inicia a comunicação EspNow para facilitar a troca de dados com o robô.
- `src/SetPID_EspNow.h`: Dedicado ao tratamento das informações recebidas pelo EspNow, ajustando dinamicamente os parâmetros PID.
- `src/dualpid.h`: Implementa o controlador PID nos dois motores do robô.
- `src/bt.h`: Implementa a comunicação Bluetooth para interação remota com o robô.
- `src/Pins.h`: Define os pinos utilizados pelo ESP32. 
- `src/Led.h`: Responsável pelo controle do LED de status.

- ## Bibliotecas e Dependências

As principais bibliotecas e dependências usadas neste projeto incluem:

- `Preferences.h`: Biblioteca para salvar e recuperar configurações persistentes no ESP32.
- `rfid_functions.h`: Biblioteca que facilita as configurações de cartões RFID (Radio-Frequency Identification).
- `MFRC522.h`: Biblioteca para controle do módulo leitor RFID MFRC522.
- `PID_v1.h`: Biblioteca para implementação do controlador PID (Proporcional, Integral, Derivativo).

## Requisitos

Certifique-se de ter o PlatformIO e VScode instalado na sua estação de trabalho.

## Como Usar

1. Clone o repositório para o seu sistema local.
   ```bash
   git clone https://github.com/seu-usuario/controlador-pid-robo.git
   cd controlador-pid-robo
2. Abra o projeto usando o PlatformIO.

   ```bash
   platformio init --ide=vscode

3. Compile e carregue o código no ESP32.

   ```bash
   platformio run --target upload

## Licença

Este projeto é licenciado sob a Licença MIT.
