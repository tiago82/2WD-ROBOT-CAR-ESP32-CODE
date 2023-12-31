#include <Arduino.h>

#include "WIFI/WiFiConfig.h"
#include "MotorDriver.h"
#include "EncoderReader.h"
//#include <BluetoothSerial.h>





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

void motorSetup(); // prototipo
void Bluetoothsetup();
void WIFIsetup();
void encodersetup();



void setup() {

  Serial.begin(115200);

  WIFIsetup();
 
  encodersetup();
 // SerialBT.begin("ESP32_BT_Test"); // Set the name for the Bluetooth device

  
}


   

void loop() {
   
void encoderloop();

//btSerial.sendMessage("Olá do ESP32!\n");

delay(1000);

  // if (SerialBT.available()) {
  //   char command = SerialBT.read(); // Ler o comando recebido via Bluetooth
    
  //   if (command == '1') {
  //     motor.moveForward(50);
  //     SerialBT.println("MOTOR ON");
  //     delay(2000);
  //     motor.stop();
  //   }
  // }

 
}

//================================================================
void encodersetup(){

encoderM1.begin();

}

// void encoderloop(){

//   encoderM1.update();
//   float pulsesPerSecond = encoderM1.getPulsesPerSecond();
//   Serial.print("Pulsos por segundo: ");
//   Serial.println(pulsesPerSecond);
// SerialBT.println(pulsesPerSecond);

//   delay(100); // Ajuste o intervalo conforme necessário


// }




void WIFIsetup(){

  // Configuração do IP estático
  IPAddress ip(192, 168, 5, 170); // IP estático desejado
  IPAddress gateway(192, 168, 5, 1); // Endereço de gateway
  IPAddress subnet(255, 255, 255, 0); // Máscara de sub-rede

  WifiInit(ssid, password, ip, gateway, subnet);



}