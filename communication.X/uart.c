#include <p33FJ128GP802.h>

#include "globals.h"

#define BAUDRATE 9600
#define BRGH_COEFF 4
const int BRGVAL = ((PROC_FCY / BAUDRATE) / BRGH_COEFF) - 1;

int command;
char senderState;

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
    U1MODEbits.BRGH = 1;//Standard speed mode
    //Plus robuste et de toute façon on a un baudrate ridicule.
    U1BRG = BRGVAL;//Fixe le baud rate par la longueur du timer lié
    U1MODEbits.PDSEL = 0b01;//8bit data, bit de parité (paire)
    U1MODEbits.STSEL = 0;//1 stop bit.

    //Modes d'interruption:
    IEC0bits.U1TXIE = 0;//Disable UART TX interrupt
    //Mais elle activée temporairement quand une trame FSK doit être envoyée
    //Donc il faut config la suite:
    U1STAbits.UTXISEL0 = 0;
    U1STAbits.UTXISEL1 = 0;//Déclenche une interruption dès qu'il est possible
                           //d'écrire dans le registre d'envoi
    U1STAbits.URXISEL = 0b00;//Déclenche une interruption à chaque trame reçue
    IEC0bits.U1RXIE = 1;//Enable UART RX interrupt

    //Polarité
    U1STAbits.UTXINV = 1;
    U1MODEbits.URXINV = 1;//tout actif à l'état haut

    //Pattes
    TRISBbits.TRISB7 = 1;
    RPINR18bits.U1RXR = 7;//RP7 est en input et U1RX est branché dessus
    RPOR3bits.RP6R = 0b00011;//RP6 est lié à U1TX

    //Start uart et ses composants
    U1MODEbits.UARTEN = 1;//Active l'uart 1
    U1STAbits.UTXEN = 1;//UART prend le controle des ports
}

void sendCommand(int newCommand){
    /*Renvoie la commande en cours si newCommand = 0xFF, sinon remplace la
     *commande est cours et envoie la nouvelle commande*/
    if (newCommand != 0xFF){
        command = newCommand;
    }
    IEC0bits.U1TXIE = 1;//Demande  à être interrompu dès qu'une transmission est
                        //possible
    if (U1STAbits.UTXBF == 0){//Si on peut déjà commencer à écrire
        //Envoie la première partie
        char part1 = (command & 0b0000000011110000)/4 + 0b11000000;//Construit
                                                          //la première partie
        U1TXREG = part1;//Envoie la première partie
        senderState = 1;//Etat passe à 1: première partie envoyée
    }else{
        //On peut encore rien faire
        senderState = 0;//Etat=0 Il reste tout à envoyer
    }
}

void handleReceived(char received){
    if (received == 1){
    //askRepeat effectué côté propulsion
        sendCommand(0xFF);
    }//nothing else so far
}

void _ISR _U1RXInterrupt(void){
    IFS0bits.U1RXIF = 0;
    if ((U1STAbits.PERR || U1STAbits.FERR )== 0 ){
        char received = U1RXREG;
        handleReceived(received);
    }//askRepeat ici aussi?
     //On a jamais eu de souci avec l'uart (2 fils sur 5 cm aussi) donc l'error
     //catching est assez rudimentaire
}

void _ISR _U1TXInterrupt(void){
    //On peut envoyer une partie de commande
    IFS0bits.U1TXIF = 0;

    //Envoyer la partie 1 ou 2 selon l'état, et switcher l'état
    if (senderState == 0){
        char part1 = (command & 0b0000000011110000)/4 + 0b11000000;
        U1TXREG = part1;
        senderState = 1;
    }else{
        char part2 = (command & 0b0000000000001111)*4
                 +(command & 0b0000001100000000)/4;
        U1TXREG = part2;
        IEC0bits.U1TXIE = 0;
        //Les deux parties ont été envoyées, plus besoin d'être interrompu
        //jusqu'à la prochaine commande à envoyer
    }
}