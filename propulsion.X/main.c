/* 
 * File:   main.c
 * Author: labo
 *
 * Created on 4 mars 2015, 15:08
 */
#include <p33FJ128MC804.h>

#include "init.h"
#include "decision.h"
#include "wheels.h"
#include "regul.h"
#include "uart.h"

int main() {
    init();
    configPWM();
    configQEI();
    configRegul();
    initUart();
    while(1){
        /*Voir la fonction T1Interrupt dans regul.c pour avoir une rapide idée
         de ce que fait le code.(+U1TXInterrupt in uart.c)*/
    }
}

