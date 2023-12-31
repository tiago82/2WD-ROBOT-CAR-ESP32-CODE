#include "Functions.h"

MFRC522 mfrc522(2);


void myFunction1();
void myFunction2();



void wifisetup(){


}

void wifiloop(){



}

void motordriver(){



}

void cardsetup(){
    // Inicializa o MFRC522 
  mfrc522.PCD_Init();

  // Adicione funções para cartões específicos
  RFID::addCardFunction(mfrc522, 0x13494a10, myFunction1);
  RFID::addCardFunction(mfrc522, 0x03246010, myFunction2);

}

void cardloop(){
// Verifique a presença de um cartão RFID
  RFID::checkRFIDPresent(mfrc522);


}

void myFunction1(){
// Implemente a lógica desejada para este cartão


}
void myFunction2(){
// Implemente a lógica desejada para este cartão


}