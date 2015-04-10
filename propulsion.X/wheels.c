#include <p33FJ128MC804.h>

#include "globals.h"

void resetMotors(){
    OC1RS = 0.15*PR2;
    OC2RS = 0.15*PR2;
}

void configPWM(){
    RPOR6bits.RP13R = 0b10010;//Lie la patte rightPWM à l'OC1
    RPOR9bits.RP18R = 0b10011;//Lie la patte leftPWM à l'OC2
    OC1CONbits.OCM=0b110;//Mode PWM no fault protection
    OC2CONbits.OCM=0b110;//Mode PWM no fault protection
    T2CONbits.TCKPS=0b01;//Prescaler 8
    PR2=50000;//Periode du timer 2=50000*(1/40*1000000)*8=1/100s
    OC1CONbits.OCTSEL=0;
    OC2CONbits.OCTSEL=0;//Les deux Output compare utilisent le timer 2
    T2CONbits.TON =1;//Lance Timer2
    resetMotors();
}

//Persistantes pour calculer les distances et angles
int leftSpins;
int rightSpins;
float oldRightDistance;
float oldLeftDistance;
float theta;

void resetPositionVariables(){
    leftSpins = 0;
    rightSpins = 0;
    POS1CNT = 0;
    POS2CNT = 0;
    oldRightDistance = 0;
    oldLeftDistance= 0;
    theta = 0;
}

void configQEI(){
    QEI1CONbits.QEIM=0b111;
    QEI2CONbits.QEIM=0b111;//MODE 4X sans remise a zero par l'index

    /*Input mapping des QEI sur les pattes ou
    les encodeurs sont physiquement liés*/
    RPINR14bits.QEA1R = 0b11000;
    RPINR14bits.QEB1R = 0b11001;//QEI1=>EncRight
    RPINR16bits.QEA2R = 0b10011;
    RPINR16bits.QEB2R = 0b10100;//QEI2=>EncLeft

    //activation des interruptions quand POSXCNT overflow
    IEC3bits.QEI1IE = 1;
    IEC4bits.QEI2IE = 1;

    //Un tour de roue = unité de comptage
    MAX1CNT = 360;
    MAX2CNT = 360;//max = 65536
    
    resetPositionVariables();
}

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

//Interface avec la regul
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