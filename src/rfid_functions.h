// rfid_functions.h

#ifndef RFID_FUNCTIONS_H
#define RFID_FUNCTIONS_H
#include <MFRC522.h>


namespace RFID {
  typedef void (*FunctionPtr)();

  struct CardFunction {
    uint32_t cardId;
    FunctionPtr function;
  };

  void addCardFunction(MFRC522& mfrc522, uint32_t cardId, FunctionPtr function);
  void checkRFIDPresent(MFRC522& mfrc522);
}

#endif // RFID_FUNCTIONS_H