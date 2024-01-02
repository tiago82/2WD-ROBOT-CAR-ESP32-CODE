# Biblioteca Encoder

Esta biblioteca oferece funcionalidades para lidar com um encoder usando interrupções em placas Arduino.

## Métodos e Funções

### `void startEncoder(int pinEncoder)`

- Inicia o encoder associado ao pino especificado para contar pulsos.

#### Parâmetros

- `pinEncoder`: O número do pino ao qual o encoder está conectado.

### `void updateEncoder()`

- Atualiza e imprime a contagem de pulsos por segundo do encoder.

### `int getpulse()`

- Retorna o número atual de pulsos acumulados pelo encoder.

## Exemplo em .ino

```cpp
#include "Encoder.h"

#define encoderPin 2 // Defina o pino do encoder

void setup() {
  Serial.begin(9600);
  startEncoder(encoderPin);
}

void loop() {
  updateEncoder();

  int pulses = getpulse();
  Serial.print("Pulsos acumulados: ");
  Serial.println(pulses);

  // Outras operações...
}
