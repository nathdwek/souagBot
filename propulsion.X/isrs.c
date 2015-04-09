#include <p33FJ128MC804.h>

#include "init.h"
#include "util.h"
#include "globals.h"

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
    if (QEI2CONbits.UPDN == 1){
        leftSpins = leftSpins - 1;
    }else{
        leftSpins = leftSpins +1;
    }
}

float readDistances(){
    float leftDistance = leftSpins * (float)MAX2CNT - (float)POS2CNT;
    float rightDistance = rightSpins * (float)MAX1CNT + (float)POS1CNT;
    float distance = 0.5*(leftDistance + rightDistance) * CM_PER_TICK;

    float omega = (rightDistance - oldRightDistance
                   - (leftDistance - oldLeftDistance))*CM_PER_TICK/22.5;
    theta = theta + omega;

    oldRightDistance = rightDistance;
    oldLeftDistance = leftDistance;
    return distance;
}

void updateConsignes(void){
    distanceConsigne = distanceConsigne + speedConsigne/REGUL_FCY;
    thetaConsigne = thetaConsigne + angularSpeedConsigne/REGUL_FCY;
    accelerate(&speedConsigne, ACCELERATION,
               &accelerating, MAX_SPEED);
    accelerate(&angularSpeedConsigne, ANGULAR_ACCELERATION,
               &acceleratingAngular, MAX_ANGULAR_SPEED);
}

void setPWMs(float distance){
    float distanceError = (distanceConsigne - distance);
    float thetaError = (thetaConsigne - theta);

    float leftPWM = 0.15 + kp * distanceError;
    float rightPWM = 0.15 - kp * distanceError;

    leftPWM = leftPWM - angularKp * thetaError;
    rightPWM = rightPWM - angularKp * thetaError;

    OC2RS = leftPWM * PR2;
    OC1RS = rightPWM * PR2;
}

void checkTerminalConditions(){
    if (goingStraight == 1){
        if (fabs(sgn(goalDistance)*(goalDistance-distanceConsigne) - 16) < 1){
            accelerating = -sgn(goalDistance);
        }
        else if (fabs(goalDistance - distanceConsigne) < 1){
            accelerating = 0.0;
            speedConsigne = 0.0;
        }
    }
    else if (rotating == 1){
        if (fabs(sgn(goalTheta)*(goalTheta-thetaConsigne) - 1.5) < 0.05){
            acceleratingAngular = -sgn(goalTheta);
        }
        else if (fabs(goalTheta - thetaConsigne) < 0.05){
            acceleratingAngular = 0.0;
            angularSpeedConsigne = 0.0;
        }
    }
}

void _ISR _T1Interrupt(void){
    IFS0bits.T1IF = 0;

    float distance=readDistances();
    //theta est en variable globale car il est l'intégrale de omega donc il
    //doit persister
    

    setPWMs(distance);

    checkTerminalConditions();
    updateConsignes();
}

void _ISR _U1RXInterrupt(void){
    IFS0bits.U1RXIF = 0;
    if ((U1STAbits.PERR || U1STAbits.FERR )== 0 ){
        received = U1RXREG;
    }
}
