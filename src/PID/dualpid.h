#pragma once

#include <Arduino.h>

#include "MultiEncoder.h"
#include <PID_v1.h>


class dualPID{
    private:
        double input1, output1, setpoint=100;
        double input2, output2;
        double kp1=0,ki1=5,kd1=0;
        double kp2=0,ki2=5,kd2=0;
        PID myPID1;
        PID myPID2;

    public:
        
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
                    myPID2(&input2, &output2, &setpoint, kp2, ki2, kd2, DIRECT) {
        }

};

    void dualPID::init(){
        myPID1.SetOutputLimits(100, 500); // PWM 10bits vai de 0 a 1023
        myPID2.SetOutputLimits(100, 500);
        myPID1.SetMode(AUTOMATIC);
        myPID2.SetMode(AUTOMATIC);

    }
    void dualPID::deinit(){
        
        myPID1.SetMode(MANUAL);
        myPID2.SetMode(MANUAL);
        output1=0;
        output2=0;
    }
    


    void dualPID::updatePID(int Input1, int Input2){
        input1 = Input1;
        input2 = Input2;
        myPID1.Compute();
        myPID2.Compute();
    }

    int dualPID::getInput1(){
        return input1;
    }
    int dualPID::getInput2(){
        return input2;
    }
     int dualPID::getOutput1(){
        return output1;
    }
     int dualPID::getOutput2(){
        return output2;

    }
    int dualPID::getSetpoint(){
        return setpoint;

    }
     void dualPID::setSetpoint(double Setpoint){
        setpoint = Setpoint;
    }