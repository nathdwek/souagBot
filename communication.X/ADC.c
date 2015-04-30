#include <p33FJ128GP802.h>
#include "ADC.h"
#include "filter.h"
#include "globals.h"

int j = 0;
int filterBuffer[100];
int  filteredReads[2];

void initADC(){
    AD1CON2bits.VCFG = 0b100;//On a pas de référence de tension extérieure.
    
    AD1PCFGLbits.PCFG12 = 0; //AN12 c'est la patte 23, celle qu'on met en analogique
    AD1CSSL = 0;//Une seule entrée => No scan
    AD1CHS0 = 12;//il va scanner la 12e entrée

    AD1CON3bits.ADCS = 10;//10 coups de clock générale = 1 coup de clock ADC
    AD1CON1bits.ASAM = 1;//start sampling quand la conversion est finie
    AD1CON1bits.SSRC = 0b010;//Timer 3 compare == 1 déclenche une conversion
    PR3 = PROC_FCY/(FS) - 1;//PR3 tq FS
    T3CONbits.TON = 1;//Lance le timer

    AD1CON1bits.AD12B = 0;//12bits
    AD1CON1bits.FORM = 0;//12 bits unsigned

    AD1CON2bits.SMPI = 0;//Interrupt après chaque conversion
    IFS0bits.AD1IF = 0;//Clear interrupt flag
    IEC0bits.AD1IE = 1;//Enable interrupt

    AD1CON1bits.ADON = 1;//Lance l'adc
    TRISAbits.TRISA0 = 0;
    LATAbits.LATA0 = 1;
}


void _ISR _ADC1Interrupt(void){
    IFS0bits.AD1IF = 0;
    filterNewSample(ADC1BUF0, filteredReads);
    filterBuffer[j] = filteredReads[1];
    j++;
    if (j==100){
        j = 0;
    }
    LATAbits.LATA0 = !LATAbits.LATA0;
}
