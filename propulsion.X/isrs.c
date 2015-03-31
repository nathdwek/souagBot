#include <p33FJ128MC804.h>
#include "init.h"
#include "util.h"
#include "math.h"

void _ISR _QEI1Interrupt(void){//RIGHT
    IFS3bits.QEI1IF = 0;
    if (QEI1CONbits.UPDN == 1){
        rightSpins = rightSpins + 1;
    }else{
        rightSpins = rightSpins - 1;
    }
    
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
void _ISR _T1Interrupt(void){
    IFS0bits.T1IF = 0;
    float leftDistance = leftSpins * MAX2CNT - POS2CNT;
    float rightDistance = rightSpins * MAX1CNT + POS1CNT;
    float distance = 0.5*(leftDistance + rightDistance) * cmPerTick;
    
    float omega = (rightDistance - oldRightDistance
                  - (leftDistance - oldLeftDistance))*cmPerTick/22.5;

    theta = theta +omega;

    oldRightDistance = rightDistance;
    oldLeftDistance = leftDistance;

    float distanceError = (distanceConsigne - distance);
    thetaError = (thetaConsigne - theta);

    leftPWM = 0.15 + kp * distanceError;
    rightPWM = 0.15 - kp * distanceError;

    leftPWM = leftPWM - angularKp * thetaError;
    rightPWM = rightPWM - angularKp * thetaError;

    OC2RS = leftPWM * PR2;
    OC1RS = rightPWM * PR2;

    if (abs(goalDistance-distance)<16.0){
        accelerating = -1.0;
    }
    if (abs(goalDistance-distance)<5.0){
        accelerating = 0.0;
        speed = 0.0;
    }

    distanceConsigne = distanceConsigne + speed/REGUL_FCY;
    thetaConsigne = thetaConsigne + angularSpeed/REGUL_FCY;
    accelerate(&speed, acceleration,
               &accelerating, maxSpeed);
    accelerate(&angularSpeed, angularAcceleration,
               &acceleratingAngular, maxAngularSpeed);
}

void accelerate(float* speed, float acceleration,
                float* accelerating, float maxSpeed){
    *speed = *speed+(*accelerating)*(acceleration)/REGUL_FCY;
    if (*speed > maxSpeed){
        *accelerating = 0.0;
    }
}

