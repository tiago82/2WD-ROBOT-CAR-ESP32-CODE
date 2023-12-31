// rfid_functions.cpp

#include "rfid_functions.h"
#include <Arduino.h>
#include <MFRC522.h>

namespace RFID {
  // Array dinâmico para armazenar as associações de cartões e funções
  CardFunction* cardFunctions = nullptr;
  int numCardFunctions = 0;

  void addCardFunction(MFRC522& mfrc522, uint32_t cardId, FunctionPtr function) {
    // Realoca o array para comportar mais uma associação de cartão e função
    cardFunctions = (CardFunction*)realloc(cardFunctions, (numCardFunctions + 1) * sizeof(CardFunction));
    cardFunctions[numCardFunctions] = {cardId, function};
    numCardFunctions++;
  }

  void checkRFIDPresent(MFRC522& mfrc522) {
    if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
      uint32_t cardId = *(uint32_t*)mfrc522.uid.uidByte;

      // Procura no array pela correspondência entre o cardId e a função associada
      for (int i = 0; i < numCardFunctions; i++) {
        if (cardFunctions[i].cardId == cardId) {
          // Executa a função, caso encontrada
          cardFunctions[i].function();
          break; // Sai do loop após encontrar a função correspondente
        }
      }

      Serial.print(F("Cartão detectado com ID: 0x"));
      Serial.print(cardId, HEX);
      Serial.println();
      mfrc522.PICC_HaltA();
      mfrc522.PCD_StopCrypto1();
    }
  }
}