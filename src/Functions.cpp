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

//#define RFID_SDA 5
#define RFID_SCK 18
#define RFID_MOSI 23
#define RFID_MISO 19
//#define RFID_RST 22




 


MotorDriver motor(EN1, IN2, IN1, EN2, IN3, IN4);// EN1 IN1, IN2, EN2, IN3, IN4) (LEFT, RIGHT)
EncoderReader encoderM1(M1_S1);
//EncoderReader encoderM2(M2_S1);
MFRC522 mfrc522(SS_RFID_PIN, RST_RFID_PIN);
BluetoothSerial SerialBT;

//==============Protótipos==========
void myFunction1();
void myFunction2();
void acenderLED() ;
void ledSetup();
void acenderLed();
void piscarLed(int numPiscadas);
void piscarLed(int numPiscadas, int rate);

//=================Test-WIFI=================


void wifiSetup(){


}

void wifiLoop(){

//=====================Test Motor===============================================

}

void testMotor(int speed){
  motor.setSpeed(speed, speed);
}

void testMotor(int speed1,int speed2){
  motor.setSpeed(speed1, speed2);
}

//=========================Test-RFID===========================================
void cardSetup(){


  SPI.begin(RFID_SCK, RFID_MISO, RFID_MOSI); // para poder funcionar a HSPI
    
  mfrc522.PCD_Init(); // Inicializa o MFRC522 

  // Adicione funções para cartões específicos
  RFID::addCardFunction(mfrc522, 0x10602403, myFunction1);
  RFID::addCardFunction(mfrc522, 0x104A4913, myFunction2);
}

void cardLoop(){
// Verifique a presença de um cartão RFID
  RFID::checkRFIDPresent(mfrc522);
}

void myFunction1(){
// Implemente a lógica desejada para este cartão
Serial.print("funcao 1");

}
void myFunction2(){
// Implemente a lógica desejada para este cartão
Serial.print("funcao 2");
piscarLed(4,100);
}

//===========================Test-Bluetooth=========================================
void btSetup(String BTName){
  
  SerialBT.begin(BTName); // Nome do dispositivo Bluetooth
  Serial.println("Espere a conexão Bluetooth...");
}

void btLoop(){

   if (SerialBT.available()) {
    char incomingByte = SerialBT.read();
    Serial.print("Received: ");
    Serial.println(incomingByte);
  }
  
  delay(500);
}
//====================================================================






