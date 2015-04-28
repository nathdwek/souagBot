#include <p33FJ128GP802.h>

#include "init.h"
#include "globals.h"
#include "uart.h"
#include "math.h"
#include "filter.h"
#include "ADC.h"

int main(void){  
    init();
    initUart();
    initFilter();
    initADC();
    
    T4CONbits.T32 = 1;
    PR4 = 65000;
    PR5 = 5000;
    IEC1bits.T5IE = 1;
    T4CONbits.TON = 0;

    while(1){

    }
}

void _ISR _T5Interrupt(void){
    IFS1bits.T5IF = 0;
    command = 0b0000000001100100;
    sendCommand();
}
