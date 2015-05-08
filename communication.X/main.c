#include <p33FJ128GP802.h>

#include "init.h"
#include "globals.h"
#include "uart.h"
#include "filter.h"
#include "ADC.h"
#include "peakDetector.h"

int main(void){
    init();
    initUart();
    initFilter();
    initADC();
    while(1){
        /*Voir la fonction ADC1Interrupt dans ADC.c pour avoir une rapide idée
        de ce que fait le code*/
    }
}
