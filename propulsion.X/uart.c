#include <p33FJ128MC804.h>

#include "globals.h"
#include "decision.h"

unsigned char receiverState;
unsigned char param;

void initUart(void){
    //Config Générale
    U1MODEbits.USIDL = 0;//uart fonctionne quand uC
                         //en mode idle. Just in case, whatever.
    U1MODEbits.WAKE = 1;//Wake up si start bit détecté. Just in case, whatever.
    U1MODEbits.IREN = 0;//IRDA off.
    U1MODEbits.UEN = 0b00;//Seuls les ports U1TX et U1RX sont utilisés.
                          //=>Donc on s'en fout de RTSMD
    U1MODEbits.LPBACK = 0;//0:inter uC. 1: test uC vers lui même.
    U1MODEbits.ABAUD = 0;//Auto Baud off.
    U1MODEbits.BRGH = 0;//Standard speed mode
    U1BRG = BRGVAL;//Fixe le baud rate par la longueur du timer lié
    U1MODEbits.PDSEL = 0b01;//8bit data, bit de parité (paire)
    U1MODEbits.STSEL = 0;//1 stop bit.

    //Modes d'interruption:
    IEC0bits.U1TXIE = 0;//Disable UART TX interrupt
    //=>Osef des deux lignes suivantes:
    //U1STAbits.UTXISEL0 = 0;
    //U1STAbits.UTXISEL1 = 0;//Déclenche une interruption dès qu'il est possible
                           //d'écrire dans le registre d'envoi
    U1STAbits.URXISEL = 0b00;//Déclenche une interruption à chaque trame reçue
    IEC0bits.U1RXIE = 1;//Enable UART RX interrupt

    //Polarité
    U1STAbits.UTXINV = 1;
    U1MODEbits.URXINV = 1;//tout actif à l'état haut

    //Pattes
    TRISBbits.TRISB10 = 1;
    RPINR18bits.U1RXR = 10;//RP10 est en input et U1RX est branché dessus
    RPOR5bits.RP11R = 0b00011;//RP11 est lié à U1TX

    //Start uart et ses composants
    U1MODEbits.UARTEN = 1;//Active l'uart 1
    U1STAbits.UTXEN = 1;//UART prend le controle des ports

    //Initialise le receiver software
    receiverState = 0x00;
}

char askrepeat(){
    if (U1STAbits.UTXBF == 0){
        U1TXREG = 0b00000001;
    }else{
        //HOPE.LIKE.HELL.
    }
    return 0x00;
}

char handleParam1(char received){
    if (receiverState == 0x00){
        param = (received && 0b00111100)*4;
        return 0x01;
    }else{
        return askrepeat();
    }
}

char handleParam2(char received){
    if (receiverState == 0x00){
        return askrepeat();
    }else{
        param = param + (received && 0b00111100)/4;
        unsigned char command = (received && 0b11000000)/64;
        interpretCommand(command, param);
        return 0x00;
    }
}

void handleReceived(char received){
    if ((received && 0b00000011) == (0x00)){
        if ((received && 0b11000000) == 0b11000000){
            receiverState = handleParam1(received);
        }else{
            receiverState = handleParam2(received);
        }
    }else{
        receiverState = askrepeat();
    }
}

void _ISR _U1RXInterrupt(void){
    IFS0bits.U1RXIF = 0;
    if ((U1STAbits.PERR || U1STAbits.FERR )== 0 ){
        char received = U1RXREG;
        handleReceived(received);
    }
}
