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
    PR2=PROC_FCY/(REGUL_FCY*8)-1;
    OC1CONbits.OCTSEL=0;
    OC2CONbits.OCTSEL=0;//Les deux Output compare utilisent le timer 2
    T2CONbits.TON =1;//Lance Timer2
    resetMotors();
}

//Persistantes pour calculer les distances,
int leftSpins;
int rightSpins;
//La vitesse angulaire,
float oldRightDistance;
float oldLeftDistance;
//et theta
float theta;

void resetPositionVariables(){//Explicite
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
    //Incrémente ou décrémente le compteur de tour selon le sens de rotation
    IFS3bits.QEI1IF = 0;
    if (QEI1CONbits.UPDN == 1){
        rightSpins = rightSpins + 1;
    }else{
        rightSpins = rightSpins - 1;
    }

}

void _ISR _QEI2Interrupt(void){//LEFT
    //cf QEI1Interrupt
    IFS4bits.QEI2IF = 0;
    if (QEI2CONbits.UPDN == 1){
        leftSpins = leftSpins - 1;
    }else{
        leftSpins = leftSpins +1;
    }
}

//Interface avec la regul
float readDistances(){
    //Distance totale parcourue par les roues jusqu'à présent
    float leftDistance = leftSpins * (float)MAX2CNT - (float)POS2CNT;
    float rightDistance = rightSpins * (float)MAX1CNT + (float)POS1CNT;

    //Distance totale parcourue par le centre de l'axe des roues du robot
    float distance = 0.5*(leftDistance + rightDistance) * CM_PER_TICK;

    //Vitesse angulaire instantanée autour de ce point
    float omega = (rightDistance - oldRightDistance
                   - (leftDistance - oldLeftDistance))*CM_PER_TICK/22.5;
    //Intégration
    theta = theta + omega;

    //Tick temporel
    oldRightDistance = rightDistance;
    oldLeftDistance = leftDistance;
    return distance;
}
