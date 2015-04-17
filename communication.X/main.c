#include <p33FJ128GP802.h>

#include "init.h"
#include "globals.h"
#include "uart.h"

int main(void){
    init();
    initUart();
    T2CONbits.T32 = 1;
    PR2 = 65000;
    PR3 = 5000;
    IEC0bits.T3IE = 1;
    T2CONbits.TON = 1;
    while(1){
    }
}

void _ISR _T3Interrupt(void){
    IFS0bits.T3IF = 0;
    command = 0b0000000001100100;
    sendCommand();
}
