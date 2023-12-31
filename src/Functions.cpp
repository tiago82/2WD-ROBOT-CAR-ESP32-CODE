#include "Functions.h"

#ifdef __has_include
    #if __has_include("keys.h")
        #include "keys.h"
    #else // Se arquivo local não encontrado
        #warning "Arquivo local de keys.h não encontrado, continuando a compilação sem ele. a senha do Wifi para conecxao será definida abaixo"
        const char *ssid = "SeuWifi"; // Seu SSID de rede (nome)
        const char *password = "suasenha"; // Sua senha de rede
      
    #endif
#endif

MFRC522 mfrc522(SS_RFID_PIN, RST_RFID_PIN);



//==============Protótipos==========
void myFunction1();
void myFunction2();
//==================================


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