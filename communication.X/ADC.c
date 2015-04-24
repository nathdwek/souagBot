
#include "ADC.h"

void initADC(){
    AD1CON1bits.AD12B = 1;
    AD1CON2bits.VCFG = 0b100;
    AD1CON3bits.ADCS = 105;
    AD1PCFGL = 0xFFFF; //on met tout en digital
    AD1PCFGLbits.PCFG12 = 0; //AN12 c'est la patte 23, celle qu'on met en analogique

}
