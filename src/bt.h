#include <BluetoothSerial.h>

BluetoothSerial SerialBT;
char lastCommand = '\0';

void startMotor();
void StopMotor();

void processCommand(char command)
{
    // Lógica para processar o comando recebido
    switch (command)
    {
    case 'S':
        Serial.println("Parar o robô");
        // Adicione aqui a lógica para parar o robô, se necessário
        StopMotor();
        
        break;
    case 'F':
        Serial.println("Mover o robô para frente");
        startMotor();

        break;
    case 'B':
        Serial.println("Mover o robô para trás");
        // Adicione aqui a lógica para mover o robô para trás, se necessário

        break;
    case 'L':
        Serial.println("Mover o robô para a esquerda");
        // Adicione aqui a lógica para mover o robô para a esquerda, se necessário
        break;
    case 'R':
        Serial.println("Mover o robô para a direita");
        // Adicione aqui a lógica para mover o robô para a direita, se necessário
        break;
    case 'I':
        Serial.println("Ação para I");
        // Adicione aqui a lógica para a letra 'I', se necessário
        break;
    case 'J':
        Serial.println("Ação para J");
        // Adicione aqui a lógica para a letra 'J', se necessário
        break;
    case 'H':
        Serial.println("Ação para H");
        // Adicione aqui a lógica para a letra 'H', se necessário
        break;
    case 'Z':
        Serial.println("Acionar a buzina");
        // Adicione aqui a lógica para acionar a buzina, se necessário
        break;
    default:
        Serial.println("Comando não reconhecido");
        // Adicione aqui a lógica para comandos não reconhecidos, se necessário
        break;
    }
}

void btsetup()
{
    SerialBT.begin("ESP32Bluetooth"); // Nome do dispositivo Bluetooth
}

void btloop()
{
    if (SerialBT.available())
    {
        char incomingByte = SerialBT.read();
        Serial.write(incomingByte);

        // Verificar se o caractere recebido é diferente do último comando
        if (incomingByte != lastCommand)
        {
            // Armazenar o último comando para a próxima verificação
            lastCommand = incomingByte;

            // Processar o comando
            processCommand(incomingByte);
        }
    }
}
