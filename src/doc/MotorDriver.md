# MotorDriver

Este arquivo define a classe `MotorDriver` para controlar motores usando um Arduino.

## Métodos

### `MotorDriver(int enA_left, int in1_left, int in2_left, int enA_right, int in1_right, int in2_right)`

- **Descrição**: Construtor da classe `MotorDriver`.
- **Parâmetros**:
  - `enA_left`, `enA_right`: Pinos PWM para controlar a velocidade dos motores esquerdo e direito, respectivamente.
  - `in1_left`, `in2_left`, `in1_right`, `in2_right`: Pinos de controle de direção dos motores.

### `void setSpeed(int leftSpeed, int rightSpeed)`

- **Descrição**: Define a velocidade dos dois motores simultaneamente.
- **Parâmetros**:
  - `leftSpeed`: Velocidade do motor esquerdo (-255 a 255).
  - `rightSpeed`: Velocidade do motor direito (-255 a 255).

### `void setSpeedLeft(int speed)`

- **Descrição**: Define a velocidade do motor esquerdo.
- **Parâmetros**:
  - `speed`: Velocidade do motor esquerdo (-255 a 255).

### `void setSpeedRight(int speed)`

- **Descrição**: Define a velocidade do motor direito.
- **Parâmetros**:
  - `speed`: Velocidade do motor direito (-255 a 255).

### `void moveForward()`

- **Descrição**: Move o carro para frente com velocidade máxima nos dois motores.

### `void moveForward(int speed)`

- **Descrição**: Move o carro para frente com velocidade específica nos dois motores.
- **Parâmetros**:
  - `speed`: Velocidade desejada para os motores (-255 a 255).

### `void moveBackward()`

- **Descrição**: Move o carro para trás com velocidade máxima nos dois motores.

### `void moveBackward(int speed)`

- **Descrição**: Move o carro para trás com velocidade específica nos dois motores.
- **Parâmetros**:
  - `speed`: Velocidade desejada para os motores (-255 a 255).

### `void stop()`

- **Descrição**: Para o movimento dos motores, parando o carro.

## Exemplo de Uso

```cpp
#include <Arduino.h>
#include "MotorDriver.h"

int enA_left = 9;
int in1_left = 8;
int in2_left = 7;
int enA_right = 6;
int in1_right = 5;
int in2_right = 4;

MotorDriver motor(enA_left, in1_left, in2_left, enA_right, in1_right, in2_right);

void setup() {
  Serial.begin(9600);

  motor.stop(); // Garante que o carro inicie parado 
}

void loop() {
  motor.moveForward(150); // Move para frente com velocidade 150
  delay(2000);

  motor.moveBackward(200); // Move para trás com velocidade 200
  delay(2000);

  motor.stop(); // Para o carro
  delay(1000);
}
