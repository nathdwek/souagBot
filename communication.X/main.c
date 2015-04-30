#include <p33FJ128GP802.h>

#include "init.h"
#include "globals.h"
#include "uart.h"
#include "math.h"
#include "filter.h"
#include "ADC.h"

int l;
int m;
float sinus;
unsigned int input;
float filterOut1[2];
float filterBuffer1[100];

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
        sinus = sin(2*PI*900*l/FS);
        input = 500*sinus + 500;
        filterNewSample(input,filterOut1);
        filterBuffer[m] = filterOut1[0];
        l++;
        m++;
        if (l == 10000){
            l = 0;
        }
        if (m == 100){
            m = 0;
        }

    }
}

void _ISR _T5Interrupt(void){
    IFS1bits.T5IF = 0;
    command = 0b0000000001100100;
    sendCommand();
}
