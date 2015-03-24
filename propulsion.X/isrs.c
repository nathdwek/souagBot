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
void _ISR _T1Interrupt(void){
    IFS0bits.T1IF = 0;
    leftDistance = (leftSpins * MAX2CNT + POS2CNT);
    leftDistance = leftDistance*cmPerTick;
    rightDistance = rightSpins * MAX1CNT + POS1CNT;
    rightDistance = rightDistance*cmPerTick;

    float leftError = (leftConsigne - leftDistance);
    float rightError = (rightConsigne - rightDistance);

    leftPWM = 0.15 + sgn(leftError)*zoneMorteLeft + kpLeft * leftError ;
    rightPWM = 0.15 - sgn (rightError)* zoneMorteRight  - kpRight * rightError;

    OC1RS = rightPWM * PR2;
    OC2RS = leftPWM * PR2;

    leftConsigne = leftConsigne + leftSpeed/REGUL_FCY;
    rightConsigne = rightConsigne + rightSpeed/REGUL_FCY;
    accelerate(&rightSpeed, &acceleratingRight);
    accelerate(&leftSpeed, &acceleratingLeft);
}

void accelerate(float* speed, int* accelerating){
    if (*accelerating==1){
        *speed = *speed+a/REGUL_FCY;
        if (*speed > maxSpeed){
            *accelerating = 0;
        }
    }
}

