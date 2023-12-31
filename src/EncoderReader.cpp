#include "EncoderReader.h"

EncoderReader* EncoderReader::instance = nullptr;

EncoderReader::EncoderReader(int encoderPin) {
    this->encoderPin = encoderPin;
    pulseCount = 0;
    prevMillis = 0;
    pulsesPerSecond = 0.0;
    instance = this; // Atribui a instância atual à variável estática
}

void EncoderReader::begin() {
    pinMode(encoderPin, INPUT);
    attachInterrupt(digitalPinToInterrupt(encoderPin), handleInterrupt, RISING);
}

void EncoderReader::handleInterrupt() {
    if (instance != nullptr) {
        instance->pulseCount++;
    }
}

void EncoderReader::update() {
    unsigned long currentMillis = millis();
    if (currentMillis - prevMillis >= 1000) {
        pulsesPerSecond = pulseCount;
        pulseCount = 0;
        prevMillis = currentMillis;
    }
}

float EncoderReader::getPulsesPerSecond() {
    return pulsesPerSecond;
}
