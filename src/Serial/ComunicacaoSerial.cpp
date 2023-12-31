
#include "ComunicacaoSerial.h"

ComunicacaoSerial::ComunicacaoSerial() {
    // Inicialize suas variáveis aqui se necessário
}

void ComunicacaoSerial::setup() {
    Serial.begin(9600);
}

void ComunicacaoSerial::atribuirValor(char *token, int &variavel) {
    if (token != nullptr) {
        variavel = atoi(token);
    }
}

void ComunicacaoSerial::atribuirValor(char *token, float &variavel) {
    if (token != nullptr) {
        variavel = atof(token);
    }
}

void ComunicacaoSerial::atribuirValor(char *token, bool &variavel) {
    if (token != nullptr) {
        variavel = atoi(token);
    }
}

template<typename T>
void ComunicacaoSerial::adicionarVariavel(T &variavel, char *token) {
    atribuirValor(token, variavel);
}

void ComunicacaoSerial::receberDados() {
    if (Serial.available() > 0) {
        String receivedData = Serial.readStringUntil('\n');
        char *token = strtok(const_cast<char*>(receivedData.c_str()), ",");

        int contador = 0;
        while (token != nullptr && contador < MAX_VARIAVEIS) {
            adicionarVariavel(variaveisInt[contador], token);
            token = strtok(nullptr, ",");
            contador++;
        }

        // Faça algo com as variáveis recebidas
        for (int i = 0; i < contador; i++) {
            Serial.print("Variavel ");
            Serial.print(i + 1);
            Serial.print(": ");

            if (i < contador) {
                Serial.println(variaveisInt[i]);
            }
        }
    }
}
