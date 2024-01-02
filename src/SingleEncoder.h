#ifndef Encoder_h
#define Encoder_h

#include <Arduino.h>

typedef void (*FuncPtr)(); // Define um tipo de ponteiro para função

void startEncoder(int pinEncoder);

void updateEncoder(); // Atualiza a contagem de pulsos 
void updateEncoder(FuncPtr func); // Atualiza a contagem de pulsos e executa uma função passada como parâmetro, Importante para chamar funcao que calcula PID.
void updateEncoderPrint(); // Atualiza a contagem de pulsos e imprime o valor por serial.
int getpulse(); // Retorna o número atual de pulsos por segundo .


#endif
