#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <Arduino.h>

class MotorDriver {
public:
    MotorDriver(int enA_left, int in1_left, int in2_left, int enA_right, int in1_right, int in2_right);
    void setSpeed(int leftSpeed, int rightSpeed); // Define a velocidade dos dois motores (-255 a 255)
    void setSpeedLeft(int speed); // Define a velocidade do motor esquerdo (-255 a 255)
    void setSpeedRight(int speed); // Define a velocidade do motor direito (-255 a 255)
    void moveForward(); // Move o carro para frente
    void moveForward(int speed); // Move o carro para frente com velocidade específica
    void moveBackward(); // Move o carro para trás
    void moveBackward(int speed); // Move o carro para trás com velocidade específica
    void stop(); // Para o carro

private:
    int enA_left_pin;
    int in1_left_pin;
    int in2_left_pin;
    int enA_right_pin;
    int in1_right_pin;
    int in2_right_pin;
};

#endif
