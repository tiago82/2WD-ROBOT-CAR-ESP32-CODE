#pragma once
#include <PID_v1.h>

class dualPID
{
private:
    static double input1, output1;
    static double input2, output2;
    PID myPID1;
    PID myPID2;

public:
    static double kp1, ki1, kd1;
    static double kp2, ki2, kd2;
    static double setpoint;

    void init();
    void deinit();
    void updatePID(int input1, int input2);
    void setSetpoint(double Setpoint);
    int getInput1();
    int getInput2();
    int getOutput1();
    int getOutput2();
    int getSetpoint();

    // Construtor: inicializa os membros da classe (tecnica "Construtores, Listas de inicializadores de membro")
    dualPID() : myPID1(&input1, &output1, &setpoint, kp1, ki1, kd1, DIRECT),
                myPID2(&input2, &output2, &setpoint, kp2, ki2, kd2, DIRECT)
    {
    }
};

// ====================================================================================================

// membros de dados estáticos de ponto flutuante não podem ser inicializados diretamente na classe
double dualPID::kp1 = 30, dualPID::ki1 = 0.2, dualPID::kd1 = 1;
double dualPID::kp2 = 0, dualPID::ki2 = 5, dualPID::kd2 = 0;
double dualPID::setpoint = 100;
double dualPID::input1, dualPID::output1;
double dualPID::input2, dualPID::output2;

void dualPID::init()
{
    myPID1.SetOutputLimits(100, 500); // PWM 10bits vai de 0 a 1023
    myPID2.SetOutputLimits(100, 500);
    myPID1.SetMode(AUTOMATIC);
    myPID2.SetMode(AUTOMATIC);
}

void dualPID::deinit()
{
    myPID1.SetMode(MANUAL);
    myPID2.SetMode(MANUAL);
    output1 = 0;
    output2 = 0;
}

void dualPID::updatePID(int Input1, int Input2)
{
    input1 = Input1;
    input2 = Input2;
    myPID1.Compute();
    myPID2.Compute();
}

/**
 * Define o valor de referência para o controle PID.
 *
 * @param Setpoint O valor de referência desejado.
 */
void dualPID::setSetpoint(double Setpoint)
{
    setpoint = Setpoint;
}

/**
 * @brief Obtém o valor do primeiro input.
 *
 * Este método retorna o valor atual do primeiro input do controlador PID.
 *
 * @return Retorna um inteiro representando o valor do primeiro input.
 */
int dualPID::getInput1()
{
    return input1;
}

/**
 * @brief Obtém o valor do segundo input.
 *
 * Este método retorna o valor atual do segundo input do controlador PID.
 *
 * @return Retorna um inteiro representando o valor do segundo input.
 */
int dualPID::getInput2()
{
    return input2;
}

/**
 * @brief Obtém o valor do primeiro output.
 *
 * Este método retorna o valor atual do primeiro output do controlador PID.
 *
 * @return Retorna um inteiro representando o valor do primeiro output.
 */
int dualPID::getOutput1()
{
    return output1;
}

/**
 * @brief Obtém o valor do segundo output.
 *
 * Este método retorna o valor atual do segundo output do controlador PID.
 *
 * @return Retorna um inteiro representando o valor do segundo output.
 */
int dualPID::getOutput2()
{
    return output2;
}

/**
 * @brief Obtém o valor do setpoint.
 *
 * Este método retorna o valor atual do setpoint do controlador PID.
 *
 * @return Retorna um inteiro representando o valor do setpoint.
 */
int dualPID::getSetpoint()
{
    return setpoint;
}
