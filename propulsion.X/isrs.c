#include <p33FJ128MC804.h>
#include "init.h"

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

void _ISR _T1Interrupt(void){
    IFS0bits.T1IF = 0;
    leftDistance = leftSpins * MAX2CNT + POS2CNT;
    rightDistance = rightSpins * MAX1CNT + POS1CNT;
    /*float leftPWM = 0.15 + kp * (leftConsigne - leftDistance);
    if (leftPWM > 0.2 ){
        leftPWM = 0.2;
    }
    if (leftPWM <0.1){
        leftPWM = 0.1;
    }
    float rightPWM = 0.15 + kp * (rightConsigne - rightDistance);
    OC1RS = rightPWM * PR2;
    OC2RS = leftPWM * PR2;
    if (consigneIndex==80){
        accelerating = 0;
    }
    if (accelerating == 1){
        consigneIndex = consigneIndex+1;
        leftConsigne = accelConsigne[consigneIndex];
    }else{
        accelerating=2;
        leftConsigne = leftConsigne+0.4*0.01*ticksPerMeter;
        //leftConsigne = leftConsigne+100;
    }
    //rightConsigne = rightConsigneTable[consigneIndex];*/
}
