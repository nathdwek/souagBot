/* 
 * File:   main.c
 * Author: labo
 *
 * Created on 4 mars 2015, 15:08
 */
#include <p33FJ128MC804.h>
#include <init.h>

void main() {
    configPWM();
    //configQEI();
    OC1RS=10000;//Pulse largeur 2ms
    OC2RS=5000;//Pulse largeur 1ms => tension = -Vcc mais moteur retourné=>OK
    while(1){
        
    }
}

