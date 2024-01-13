#include "MotorDriver.h"

MotorDriver::MotorDriver(int enA_left, int in1_left, int in2_left, int enA_right, int in1_right, int in2_right)
{
    enA_left_pin = enA_left;
    in1_left_pin = in1_left;
    in2_left_pin = in2_left;
    enA_right_pin = enA_right;
    in1_right_pin = in1_right;
    in2_right_pin = in2_right;

    pinMode(enA_left_pin, OUTPUT);
    pinMode(in1_left_pin, OUTPUT);
    pinMode(in2_left_pin, OUTPUT);
    pinMode(enA_right_pin, OUTPUT);
    pinMode(in1_right_pin, OUTPUT);
    pinMode(in2_right_pin, OUTPUT);

    digitalWrite(in1_left_pin, LOW);
    digitalWrite(in2_left_pin, LOW);
    digitalWrite(in1_right_pin, LOW);
    digitalWrite(in2_right_pin, LOW);
}

void MotorDriver::setSpeed(int leftSpeed, int rightSpeed)
{
    setSpeedLeft(leftSpeed);
    setSpeedRight(rightSpeed);
}

void MotorDriver::setSpeedLeft(int speed)
{
    if (speed >= 0)
    {
        digitalWrite(in1_left_pin, HIGH);
        digitalWrite(in2_left_pin, LOW);
        analogWrite(enA_left_pin, speed); // Controla a velocidade usando PWM
    }
    else
    {
        digitalWrite(in1_left_pin, LOW);
        digitalWrite(in2_left_pin, HIGH);
        analogWrite(enA_left_pin, -speed); // Controla a velocidade usando PWM
    }
}

void MotorDriver::setSpeedRight(int speed)
{
    if (speed >= 0)
    {
        digitalWrite(in1_right_pin, HIGH);
        digitalWrite(in2_right_pin, LOW);
        analogWrite(enA_right_pin, speed); // Controla a velocidade usando PWM
    }
    else
    {
        digitalWrite(in1_right_pin, LOW);
        digitalWrite(in2_right_pin, HIGH);
        analogWrite(enA_right_pin, -speed); // Controla a velocidade usando PWM
    }
}

void MotorDriver::moveForward()
{
    setSpeed(255, 255); // Define a velocidade máxima dos dois motores para frente
}

void MotorDriver::moveForward(int speed)
{
    if (speed == 0)
    {
        stop(); // Para o carro se a velocidade for 0
    }
    else
    {
        setSpeed(speed, speed); // Define a velocidade específica para frente nos dois motores
    }
}

void MotorDriver::moveBackward()
{
    setSpeed(-255, -255); // Define a velocidade máxima dos dois motores para trás
}

void MotorDriver::moveBackward(int speed)
{

    if (speed == 0)
    {
        stop(); // Para o carro se a velocidade for 0
    }
    else
    {
        setSpeed(-speed, -speed); // Define a velocidade específica para frente nos dois motores
    }
}

void MotorDriver::stop()
{
    digitalWrite(in1_left_pin, LOW);
    digitalWrite(in2_left_pin, LOW);
    digitalWrite(in1_right_pin, LOW);
    digitalWrite(in2_right_pin, LOW);
    analogWrite(enA_left_pin, 0);  // Para o motor esquerdo
    analogWrite(enA_right_pin, 0); // Para o motor direito
}
