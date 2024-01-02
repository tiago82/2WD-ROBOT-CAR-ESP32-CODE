// rfid_functions.h

#ifndef RFID_FUNCTIONS_H
#define RFID_FUNCTIONS_H
#include <MFRC522.h>


namespace RFID {
  typedef void (*FunctionPtr)();

  // Estrutura para associar um ID de cartão a duas funções
  struct CardFunction {
    uint32_t cardId;
    FunctionPtr function1;
    FunctionPtr function2;
  };

  void addCardFunction(MFRC522& mfrc522, uint32_t cardId, FunctionPtr function);
  void addCardTwoFunctions(MFRC522& mfrc522, uint32_t cardId, FunctionPtr function1, FunctionPtr function2);

  void checkRFIDPresent(MFRC522& mfrc522);
    void checkRFIDPresent2(MFRC522& mfrc522);

}

#endif // RFID_FUNCTIONS_H