#ifndef ENCODER_READER_H
#define ENCODER_READER_H

#include <Arduino.h>

class EncoderReader {
public:
    EncoderReader(int encoderPin);
    void begin();
    void update();
    float getPulsesPerSecond();

private:
    int encoderPin;
    volatile int pulseCount;
    unsigned long prevMillis;
    float pulsesPerSecond;

    static EncoderReader* instance; // Referência para a instância do objeto

    static void handleInterrupt(); // Função estática para interrupção
};

#endif
