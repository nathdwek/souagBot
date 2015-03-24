#include <p33FJ128MC804.h>
#include "init.h"
#include "util.h"

void _ISR _QEI1Interrupt(void){//RIGHT
    if (QEI1CONbits.UPDN == 1){
        rightSpins = rightSpins + 1;
    }else{
        rightSpins = rightSpins - 1;
    }
    IFS3bits.QEI1IF = 0;
}

void _ISR _QEI2Interrupt(void){//LEFT
    IFS4bits.QEI2IF = 0;
    if (QEI2CONbits.UPDN == 0){
        leftSpins = leftSpins + 1;
    }else{
        leftSpins = leftSpins - 1;
    }
}


float leftPWM;//pour debugger
float rightPWM;
float thetaError;
float theta;
void _ISR _T1Interrupt(void){
    IFS0bits.T1IF = 0;
    float leftDistance = leftSpins * MAX2CNT + POS2CNT;
    float rightDistance = rightSpins * MAX1CNT + POS1CNT;
    float distance = 0.5*(leftDistance + rightDistance) * cmPerTick;
    theta = 0.5* (rightDistance - leftDistance) * cmPerTick*5.0/22.5;

    float distanceError = (distanceConsigne - distance);
    thetaError = (thetaConsigne - theta);

    leftPWM = 0.15 + kp * distanceError;
    rightPWM = 0.15 - kp * distanceError;

    if (thetaError < 0){
        rightPWM = rightPWM - angularKp * thetaError;
    }else{
        leftPWM = leftPWM - angularKp * thetaError;
    }

    OC1RS = rightPWM * PR2;
    OC2RS = leftPWM * PR2;

    distanceConsigne = distanceConsigne + speed/REGUL_FCY;
    thetaConsigne = thetaConsigne + angularSpeed/REGUL_FCY;
    accelerate(&speed, acceleration,
               &accelerating, maxSpeed);
    accelerate(&angularSpeed, angularAcceleration,
               &acceleratingAngular, maxAngularSpeed);
}

void accelerate(float* speed, float acceleration,
                int* accelerating, float maxSpeed){
    if (*accelerating==1){
        *speed = *speed+acceleration/REGUL_FCY;
        if (*speed > maxSpeed){
            *accelerating = 0;
        }
    }
}

