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
    init();
    configPWM();
    configQEI();
    configRegul();
    OC1RS = 7500;
    OC2RS = 7500;
    accelerating = 1.0;
    acceleratingAngular = 0;
    distanceConsigne = 0;
    thetaConsigne = 0;
    goalDistance = 400;//cm
    while(1){
    }
}

