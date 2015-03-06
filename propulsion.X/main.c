/* 
 * File:   main.c
 * Author: labo
 *
 * Created on 4 mars 2015, 15:08
 */
#include <p33FJ128MC804.h>
#include "init.h"
#include "isrs.h"

void main() {
    int positionAbs = 0;
    configPWM();
    configQEI();
    OC1RS=10000;//Pulse largeur 2ms
    OC2RS=7500;//Pulse largeur 1ms => tension = -Vcc mais moteur retourné=>OK
    //MAX1CNT = 2000;
    //MAX2CNT = 2000;
    POS2CNT = 0;
    while(1){
        positionAbs = POS2CNT;
        if (POS2CNT > 2000){
            OC1RS=7500;
         }
    }
}

