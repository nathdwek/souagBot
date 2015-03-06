#include <p33FJ128MC804.h>

int PROC_FCY = 40000000;

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
    QEI1CONbits.QEIM=0b110;
    QEI2CONbits.QEIM=0b110;//MODE 4X sans remise a zero par l'index
    RPINR14bits.QEA1R = 0b11000;
    RPINR14bits.QEB1R = 0b11001;//QEI2=>EncRight
    RPINR16bits.QEA2R = 0b10011;
    RPINR16bits.QEB2R = 0b10100;//QEI1=>EncLeft
    /*Input mapping des QEI sur les pattes ou
    les encodeurs sont physiquement liés*/
    MAX1CNT = 60000;
    MAX2CNT = 60000;
    POS1CNT = MAX1CNT/2;
    POS2CNT = MAX2CNT/2;
}


int leftTicks = 0;
int rightTicks = 0;
int REGUL_FCY = 100;
void configRegul(){
    T1CONbits.TCKPS = 0b10;//Prescaler 64
    PR1=PROC_FCY/(REGUL_FCY*64);//100Hz
    IEC0bits.T1IE = 1;//active l'interruption
}
