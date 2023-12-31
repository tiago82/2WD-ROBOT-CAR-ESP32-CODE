# RFID Functions

Este arquivo contém funções para lidar com cartões RFID usando a biblioteca MFRC522.

## Estruturas e Tipos

### `RFID::FunctionPtr`

- Tipo de ponteiro para função. Usado para representar funções associadas a cartões RFID.

### `RFID::CardFunction`

- Estrutura representando uma função associada a um cartão RFID.
  - `cardId`: ID do cartão.
  - `function`: Ponteiro para a função associada.

## Funções

### `void addCardFunction(MFRC522& mfrc522, uint32_t cardId, RFID::FunctionPtr function)`

Adiciona uma função associada a um cartão específico ao leitor RFID.

- `mfrc522`: Referência para o objeto MFRC522.
- `cardId`: ID do cartão RFID.
- `function`: Ponteiro para a função associada ao cartão.

### `void checkRFIDPresent(MFRC522& mfrc522)`

Verifica a presença de um cartão RFID no leitor.

- `mfrc522`: Referência para o objeto MFRC522.

## Uso

Para utilizar estas funções, é necessário incluir a biblioteca MFRC522 e chamar as funções apropriadas, como mostrado no exemplo abaixo:

```cpp
#include <MFRC522.h>
#include "rfid_functions.h"

#define RST_PIN 9   // Define o pino RST do MFRC522
#define SS_PIN 10   // Define o pino SDA do MFRC522

MFRC522 mfrc522(;/*configurações do pino*/ // Cria o objeto MFRC522

void myFunction() {
  // Implemente a lógica desejada para este cartão
}

void setup() {
  // Inicialize o MFRC522 e outros componentes
  mfrc522.PCD_Init();

  // Adicione funções para cartões específicos
  RFID::addCardFunction(mfrc522, /*id do cartão(Ex: 0x13494a10)*/, myFunction);
}

void loop() {
  // Verifica a presença de um cartão RFID
  RFID::checkRFIDPresent(mfrc522);

  // Outras operações do loop
}
