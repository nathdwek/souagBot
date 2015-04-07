#include <p33FJ128GP802.h>


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

void init(void) {
    PLLFBD = 30; // M=32
    CLKDIVbits.PLLPOST = 0; // N1=2
    CLKDIVbits.PLLPRE = 0; // N2=2
    __builtin_write_OSCCONH( 3 );
    __builtin_write_OSCCONL( 1 );
    // Wait for Clock switch to occur
    while (OSCCONbits.COSC != 0b011);
}

void initUart(void){
    //Config Générale
    U1MODEbits.UARTEN = 1;//Active l'uart 1
    U1MODEbits.USIDL = 0;//uart fonctionne quand uC
                         //en mode idle. Just in case, whatever.
    U1MODEbits.IREN = 0;//IRDA off.
    U1MODEbits.UEN = 0b00;//Seuls les ports U1TX et U1RX sont utilisés.
                          //=>Donc on s'en fout de RTSMD
    U1MODEbits.WAKE = 1;//Wake up si start bit détecté. Just in case, whatever.
    U1MODEbits.LPBACK = 0;//0:inter uC. 1: test uC vers lui même.
    U1MODEbits.ABAUD = 0;//Auto Baud off.
    U1MODEbits.URXINV = 0;//U1RX actif à l'état haut
    U1MODEbits.BRGH = 0;//Standard speed mode
    U1MODEbits.PDSEL = 0b01;//8bit data, bit de parité
    U1MODEbits.STSEL = 0;//1 stop bit.

    //Modes d'interruption:
    U1STAbits.UTXISEL0 = 0;
    U1STAbits.UTXISEL1 = 0;//Déclenche une interruption dès qu'il est possible
                           //d'écrire dans le registre d'envoi
    U1STAbits.URXISEL = 0b00;//Déclenche une interruption à chaque trame reçue

    //Polarité
    U1STAbits.UTXINV = 1;
    U1MODEbits.URXINV = 0;//tout actif à l'état haut
}
