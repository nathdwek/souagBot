#include <p33FJ128MC804.h>
#include "init.h"

void _ISR _QEI1Interrupt(void){
    OC1RS=7500;
    IFS3bits.QEI1IF = 0;
}

void _ISR _QEI2Interrupt(void){
    OC1RS=7500;
    IFS4bits.QEI2IF = 0;
}

void _ISR _T1Interrupt(void){
    int deltaLeft = POS1CNT - MAX1CNT/2;
    int deltaRight = POS2CNT - MAX2CNT/2;
    POS1CNT = MAX1CNT/2;
    POS2CNT = MAX2CNT/2;
    float vLeft = deltaLeft*REGUL_FCY;
    float vRight = deltaRight*REGUL_FCY;
    //USELESS CAR ON FAIT UNE REGULATION EN POSITION!
}
