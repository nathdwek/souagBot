#include <p33FJ128GP802.h>

#include "init.h"
#include "globals.h"
#include "uart.h"

int main(void){
    init();
    initUart();
    T1CONbits.TCKPS = 0b11;
    PR1=65535;
    IEC0bits.T1IE = 1;
    T1CONbits.TON = 1;
    while(1){
        if(U1STAbits.OERR == 1){
            char d = 'a';
        }
    }
}

void _ISR _T1Interrupt(void){
    IFS0bits.T1IF = 0;
    if (U1STAbits.UTXBF == 0){
        sent++;
        if (sent ==  0b11111111){
            sent=0b00000000;
        }
        U1TXREG = sent;
    }
}
