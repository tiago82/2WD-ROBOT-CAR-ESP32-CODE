#include <Arduino.h>
#include "Functions.h"
#include "Pins.h"


#ifdef __has_include
    #if __has_include("keys.h")
        #include "keys.h"
    #else // Se arquivo local não encontrado
        #warning "Arquivo local de keys.h não encontrado, continuando a compilação sem ele. a senha do Wifi para conecxao será definida abaixo"
        const char *ssid = "SeuWifi"; // Seu SSID de rede (nome)
        const char *password = "suasenha"; // Sua senha de rede
      
    #endif
#endif




MotorDriver motor(EN1, IN2, IN1, EN2, IN3, IN4);// EN1 IN1, IN2, EN2, IN3, IN4) (LEFT, RIGHT)
EncoderReader encoderM1(M1_S1);
//EncoderReader encoderM2(M2_S1);
//BluetoothSerial SerialBT;



void setup() {
Serial.begin(115200);

  
}



void loop() {
   

 
}

