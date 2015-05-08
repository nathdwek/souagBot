#include <p33FJ128MC804.h>

#include "globals.h"
#include "decision.h"

#define BAUDRATE 9600
#define BRGH_COEFF 4
const int BRGVAL = ((PROC_FCY / BAUDRATE) / BRGH_COEFF) - 1;

char receiverState;
//0:Attend le début d'une nouvelle commande (0b11----00)
//1:Attend la fin d'une commande en cours (0b..----00)
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
    U1MODEbits.BRGH = 1;//16x speed mode.
    //Plus robuste et de toute façon notre baudrate est bien inférieur au max.
    U1BRG = BRGVAL;//Fixe le baud rate par la longueur du timer lié
    U1MODEbits.PDSEL = 0b01;//8bit data, bit de parité (paire)
    U1MODEbits.STSEL = 0;//1 stop bit.

    //Modes d'interruption
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
    //Si les valeurs sont 0 c'est probablement du debug
    U1MODEbits.UARTEN = 1;//Active l'uart 1
    U1STAbits.UTXEN = 1;//UART prend le controle des ports

    //Initialise le receiver software
    receiverState = 0;
}

char askRepeat(){
//Il y a eu une erreur. Demande de répéter une commande entière et état=>0.
    if (U1STAbits.UTXBF == 0){
        U1TXREG = 0b00000001;
    }
    return 0;
}

char handleParam1(char received){
//Le char reçu semble contenir la première partie du paramètre.
    if (receiverState == 0){
    //OK ça colle avec l'état du receiver.
        param = (received & 0b00111100)*4;
        //Les 4 bits du milieu => Les 4 MSBs du param
        return 1;
        //Passe à l'état 1 puisqu'on a reçu la première partie d'une commande.
    }else{
    //Erreur, on s'attendait à la fin d'une commande.
        return askRepeat();
    }
}

char handleParam2(char received){
//Le char reçu semble contenir la deuxième partie du paramètre et la commande.
    if (receiverState == 0){
    //Erreur, on a jamais reçu de première partie
        return askRepeat();
    }else{
    //OK, ça colle avec l'état du receiver.
        param = param + (received & 0b00111100)/4;
        //Les 4 bits du milieu => Les 4 LSBs du param
        unsigned char command = (received & 0b11000000)/64;
        //Les 2 bits du début => les 2 bits de commande
        interpretCommand(command, param);
        //Commande traitée.
        return 0;
        //Retourne à l'état 0 pour recevoir une nouvelle commande.
    }
}

void handleReceived(char received){
    if ((received & 0b00000011) == 0b00000000){
    //Deux derniers bits toujours nuls dans le cas d'une commande correcte.
        if ((received & 0b11000000) == 0b11000000){
        //Deux premiers bits sont 0b11 si première partie de commande
            receiverState = handleParam1(received);
        }else{
        //0b00,01,10:Deuxième partie de commande
            receiverState = handleParam2(received);
        }
    }else{
    //Erreur
        receiverState = askRepeat();
    }
}

void _ISR _U1RXInterrupt(void){
    IFS0bits.U1RXIF = 0;
    if ((U1STAbits.PERR || U1STAbits.FERR )== 0 ){
    //Check erreur de parité ou de formattage
        char received = U1RXREG;
        handleReceived(received);
    }else{
        char garbage = U1RXREG;
        receiverState = askRepeat();
    }
}
