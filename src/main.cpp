#include <Arduino.h>
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


#define EN1 21
#define IN1 32
#define IN2 33
#define EN2 22
#define IN3 25
#define IN4 26
#define M1_S1 16
#define M2_S1 3

MotorDriver motor(EN1, IN2, IN1, EN2, IN3, IN4);// EN1 IN1, IN2, EN2, IN3, IN4) (LEFT, RIGHT)
EncoderReader encoderM1(M1_S1);
//EncoderReader encoderM2(M2_S1);
//BluetoothSerial SerialBT;



void setup() {
Serial.begin(115200);

  
}



void loop() {
   

 
}

