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
long input[2];
float filterOut1[2];
float filterBuffer1[100];
char detected[2];

int main(void){
    init();
    initUart();
    initFilter();
    initADC();
    while(1){
    }
}
