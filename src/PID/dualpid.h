#pragma once
#include <PID_v1.h>

// #define SinglePID // comente essa linha para usar o PID duplo

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
    static double setpoint1, setpoint2;

    void init();
    void deinit();
    void updatePID(int Input1);
    void updatePID(int input1, int input2);
    void setSetpoint1(double Setpoint);
    void setSetpoint2(double Setpoint);
    int getInput1();
    int getInput2();
    int getOutput1();
    int getOutput2();
    double getSetpoint1();
    double getSetpoint2();

    // Construtor: inicializa os membros da classe (tecnica "Construtores, Listas de inicializadores de membro")
    dualPID() : myPID1(&input1, &output1, &setpoint1, kp1, ki1, kd1, DIRECT),
                myPID2(&input2, &output2, &setpoint2, kp2, ki2, kd2, DIRECT)
    {
    }
};

// ====================================================================================================

// membros de dados estáticos de ponto flutuante não podem ser inicializados diretamente na classe
double dualPID::kp1, dualPID::ki1, dualPID::kd1;
double dualPID::kp2, dualPID::ki2, dualPID::kd2;
double dualPID::setpoint1, dualPID::setpoint2;
double dualPID::input1, dualPID::output1;
double dualPID::input2, dualPID::output2;

#ifdef SinglePID
void dualPID::init()
{
    myPID2.SetOutputLimits(220, 650); // PWM 10bits vai de 0 a 1023
    myPID2.SetMode(AUTOMATIC);
}
#else
void dualPID::init()
{
    myPID1.SetOutputLimits(150, 500); // PWM 10bits vai de 0 a 1023
    myPID2.SetOutputLimits(150, 500);
    myPID1.SetMode(AUTOMATIC);
    myPID2.SetMode(AUTOMATIC);
}
#endif

void dualPID::deinit()
{
    myPID1.SetMode(MANUAL);
    myPID2.SetMode(MANUAL);
    // output1 = 0;
    // output2 = 0;
}

void dualPID::updatePID(int Input1)
{
    myPID1.SetTunings(kp1, ki1, kd1);
    input1 = Input1;
    myPID1.Compute();
}

void dualPID::updatePID(int Input1, int Input2)
{
    myPID1.SetTunings(kp1, ki1, kd1);
    myPID2.SetTunings(kp2, ki2, kd2);
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
void dualPID::setSetpoint1(double Setpoint)
{
    setpoint1 = Setpoint;
}
void dualPID::setSetpoint2(double Setpoint)
{
    setpoint2 = Setpoint;
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
double dualPID::getSetpoint1()
{
    return setpoint1;
}
double dualPID::getSetpoint2()
{
    return setpoint2;
}
