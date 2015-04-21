#include <p33FJ128GP802.h>

#include "init.h"
#include "globals.h"
#include "uart.h"
#include "math.h"
#include "filter.h"
#include "filter.h"

int main(void){
    float sample;
    int j = 0;
    float result[1000];
    
    init();
    initUart();
    initFilter();
    T2CONbits.T32 = 1;
    PR2 = 65000;
    PR3 = 5000;
    IEC0bits.T3IE = 1;
    T2CONbits.TON = 1;
    int wave[1000];
    int i;
    for (i = 0; i < 1000; i++){
        sample = sin(2*3.14*900*i/27000);
        wave[i] = 2000 * sample;
    }
    while(1){
        if (j<1000){
            result[j] = filter(wave[j]);
            j++;
        }
    }
}

void _ISR _T3Interrupt(void){
    IFS0bits.T3IF = 0;
    command = 0b0000000001100100;
    sendCommand();
}
