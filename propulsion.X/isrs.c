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
