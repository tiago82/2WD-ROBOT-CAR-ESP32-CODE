# EncoderReader

Este arquivo define a classe `EncoderReader` para leitura de um encoder utilizando um Arduino.

## Classe `EncoderReader`

A classe `EncoderReader` oferece métodos para ler pulsos de um encoder e calcular a frequência de pulsos por segundo.

### Construtor

#### `EncoderReader(int encoderPin)`

- **Descrição**: Construtor da classe `EncoderReader`.
- **Parâmetros**:
  - `encoderPin`: Pino do Arduino conectado ao encoder.

### Métodos

#### `void begin()`

- **Descrição**: Inicializa o encoder para leitura.

#### `void update()`

- **Descrição**: Atualiza o contador de pulsos do encoder.

#### `float getPulsesPerSecond()`

- **Descrição**: Retorna a frequência de pulsos por segundo do encoder.

### Variáveis

#### `int encoderPin`

- **Descrição**: Pino do Arduino conectado ao encoder.

#### `volatile int pulseCount`

- **Descrição**: Contador de pulsos do encoder.

#### `unsigned long prevMillis`

- **Descrição**: Armazena o tempo da última atualização do contador de pulsos.

#### `float pulsesPerSecond`

- **Descrição**: Frequência de pulsos por segundo do encoder.

#### `static EncoderReader* instance`

- **Descrição**: Referência para a instância do objeto da classe `EncoderReader`.

### Funções

#### `static void handleInterrupt()`

- **Descrição**: Função estática utilizada como interrupção para atualizar o contador de pulsos do encoder.

## Exemplo de Uso

```cpp
#include <Arduino.h>
#include "EncoderReader.h"

int encoderPin = /* Pino do encoder */;

EncoderReader encoder(encoderPin);

void setup() {
  Serial.begin(9600);
  
  encoder.begin();
}

void loop() {
  encoder.update();

  float pulsesPerSecond = encoder.getPulsesPerSecond();
  Serial.print("Pulsos por segundo: ");
  Serial.println(pulsesPerSecond);

  delay(1000); // Aguarda 1 segundo
}
