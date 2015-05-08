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
    }
}
