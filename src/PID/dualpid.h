#pragma once

#include <Arduino.h>

#include "MultiEncoder.h"
#include <PID_v1.h>


class dualPID{
    private:


        double input1, output1, setpoint=1500;
        double input2, output2;
        double kp1=0.2,ki1=0.5,kd1=0;
        double kp2=0.2,ki2=0.5,kd2=0;

        PID myPID1;
        PID myPID2;

    public:
        void setup();
        void updatePID();

        void updatePID(int input1, int input2);
        int getInput1();
        int getInput2();
        int getOutput1();
        int getOutput2();
        int getSetpoint();

        void setInput1(double input);
        void setInput2(double input);
        void setSetpoint(double Setpoint);


        // Construtor: inicializa os membros da classe (tecnica "Construtores, Listas de inicializadores de membro")
        dualPID() : myPID1(&input1, &output1, &setpoint, kp1, ki1, kd1, DIRECT),
                    myPID2(&input2, &output2, &setpoint, kp2, ki2, kd2, DIRECT) {
        }

};

    void dualPID::setup(){
        
        myPID1.SetMode(AUTOMATIC);
        myPID2.SetMode(AUTOMATIC);
        myPID1.SetOutputLimits(0, 500);
        myPID2.SetOutputLimits(0, 500);
    }
    
    void dualPID::updatePID(){
        myPID1.Compute();
        myPID2.Compute();

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


    void dualPID::setInput1(double input){
        input1 = input;
    }
    void dualPID::setInput2(double input){
        input2 = input;
    }
     void dualPID::setSetpoint(double Setpoint){
        setpoint = Setpoint;
    }