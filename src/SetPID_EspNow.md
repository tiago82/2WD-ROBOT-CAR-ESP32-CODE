# Manual da Classe MyDerivedClass

## Introdução

A classe `MyDerivedClass` é uma classe derivada da classe base `EspNowSerial`, fornecendo funcionalidades adicionais para comunicação via ESP-NOW e seleção de variáveis PID. Este manual descreve os comandos disponíveis para interagir com a classe `MyDerivedClass` através da comunicação ESP-NOW.

## Como Funciona

Nesta aplicação, a comunicação via ESP-NOW é estabelecida entre um transmissor e um receptor. O transmissor é responsável por enviar os textos escritos pelo usuário no monitor serial, enquanto esse código no receptor trata os dados recebidos, atribuindo valores aos parâmetros do controlador PID conforme necessário.

## Comandos Disponíveis

Os comandos a seguir podem ser enviados para a placa ESP32 para interagir com a classe `MyDerivedClass` através da comunicação ESP-NOW:

### Configuração do PID:

- `kpt <valor>`: Define o valor do ganho proporcional (Kp) para ambos motores.
- `kit <valor>`: Define o valor do ganho integral (Ki)  para ambos motores.
- `kdt <valor>`: Define o valor do ganho derivativo (Kd)  para ambos motores.

- `kpa <valor>`: Define o valor do ganho proporcional (Kp) para o primeiro motor.
- `kia <valor>`: Define o valor do ganho integral (Ki) para o primeiro motor.
- `kda <valor>`: Define o valor do ganho derivativo (Kd) para o primeiro motor.

- `kpb <valor>`: Define o valor do ganho proporcional (Kp) para o segundo motor.
- `kib <valor>`: Define o valor do ganho integral (Ki) para o segundo motor.
- `kdb <valor>`: Define o valor do ganho derivativo (Kd) para o segundo motor.

### Configuração do Setpoint:

- `set <valor>`: Define o valor do setpoint para ambos os motores.
- `sea <valor>`: Define o valor do setpoint para o primeiro motor.
- `seb <valor>`: Define o valor do setpoint para o segundo motor.

### Controle do Motor:

- `w`: Inicia os motores.
- `e`: Para os motores.

### Ações Adicionais:

- `r`: Reinicia o ESP32.
- `sa`: Grava as configurações na memória EEPROM e reinicia o ESP32.


