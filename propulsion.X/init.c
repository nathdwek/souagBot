#include <p33FJ128MC804.h>

#include "init.h"
//  BITS DE CONFIGURATION
///////////////////////////////////////////////////////////////////////////////
// disables the watchdog
_FWDT(FWDTEN_OFF);

// The dsPIC will be clocked by the primary oscillator with a 10MHz crystal.
// We want to use the PLL to obtain Fosc = 80MHz ( <=> 40MIPS ).
// Problem : with a 10MHz crystal, PLL constraints are not met with the
// default parameter.
// Solution :
//	- boot using the internal FRC oscillator as clock source,
//	- set the right PLL parameters to obtain Fosc = 80MHz, without violating
//	  the PLL constraints,
//	- switch the clock source to the PLL
//	- wait for the end of the clock switch
//
// Select internal FRC oscillator as clock source
_FOSCSEL(FNOSC_FRC);
// enables clock switching and configure the primary oscillator for a 10MHz crystal
_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_XT);


long PROC_FCY = 40000000;


void init(void) {
    PLLFBD = 30; // M=32
    CLKDIVbits.PLLPOST = 0; // N1=2
    CLKDIVbits.PLLPRE = 0; // N2=2
    __builtin_write_OSCCONH( 3 );
    __builtin_write_OSCCONL( 1 );
    // Wait for Clock switch to occur
    while (OSCCONbits.COSC != 0b011);
}


void configPWM(){
    RPOR6bits.RP13R = 0b10010;//Lie la patte rightPWM à l'OC1
    RPOR9bits.RP18R = 0b10011;//Lie la patte leftPWM à l'OC2
    OC1CONbits.OCM=0b110;//Mode PWM no fault protection
    OC2CONbits.OCM=0b110;//Mode PWM no fault protection
    T2CONbits.TCKPS=0b01;//Prescaler 8
    PR2=50000;//Periode du timer 2=50000*(1/40*1000000)*8=1/100s
    OC1CONbits.OCTSEL=0;
    OC2CONbits.OCTSEL=0;//Les deux Output compare utilisent le timer 2
    T2CONbits.TON =1;//Lance Timer2
}

void configQEI(){
    QEI1CONbits.QEIM=0b111;
    QEI2CONbits.QEIM=0b111;//MODE 4X sans remise a zero par l'index
    RPINR14bits.QEA1R = 0b11000;
    RPINR14bits.QEB1R = 0b11001;//QEI1=>EncRight
    RPINR16bits.QEA2R = 0b10011;
    RPINR16bits.QEB2R = 0b10100;//QEI2=>EncLeft
    /*Input mapping des QEI sur les pattes ou
    les encodeurs sont physiquement liés*/
    IEC3bits.QEI1IE = 1;
    IEC4bits.QEI2IE = 1;//activation des interruptions quand POSXCNT ol
}


int REGUL_FCY = 100;

int leftSpins;
int rightSpins;
float kp;
float ticksPerMeter;
float accelConsigne[80];
float leftConsigne;
float rightConsigne;
int consigneIndex;
int accelerating;
int leftDistance;
int rightDistance;
void configRegul(){
    T1CONbits.TCKPS = 0b10;//Prescaler 64
    PR1=PROC_FCY/(REGUL_FCY*64);
    IEC0bits.T1IE = 1;//active l'interruption
    T1CONbits.TON = 1;//lance le timer
    leftSpins = 0;
    rightSpins = 0;
    POS1CNT = 0;
    POS2CNT = 0;
    MAX1CNT = 360;
    MAX2CNT = 360;//max = 65536
    rightDistance = 0;
    leftDistance = 0;
    ticksPerMeter = 1145.9156;
    kp = 1/ticksPerMeter;//8.49 1/m
    /*float a = 0.0000025*ticksPerMeter;
    float v = 0;
    float ticks = 0;
    int i;
    for (i =0; i<80; i++){
        v = v + a;
        ticks = ticks + v ;
        accelConsigne[i]=ticks;
    }
    leftConsigne = 0;
    rightConsigne = 0;
    consigneIndex = 0;
    accelerating = 1;*/
}


