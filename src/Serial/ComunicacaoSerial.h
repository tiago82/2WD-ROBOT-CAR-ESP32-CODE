#ifndef ComunicacaoSerial_h
#define ComunicacaoSerial_h

#include <Arduino.h>

class ComunicacaoSerial {
public:
    ComunicacaoSerial();
    void setup();
    void receberDados();

private:
    void atribuirValor(char *token, int &variavel);
    void atribuirValor(char *token, float &variavel);
    void atribuirValor(char *token, bool &variavel);

    template<typename T>
    void adicionarVariavel(T &variavel, char *token);

    // Adicione aqui a quantidade máxima de variáveis
    static const int MAX_VARIAVEIS = 50;
    int variaveisInt[MAX_VARIAVEIS];
    float variaveisFloat[MAX_VARIAVEIS];
    bool variaveisBool[MAX_VARIAVEIS];
};

#endif
