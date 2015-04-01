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
    rotate(1.0);
    accelerating = 0.0;
    acceleratingAngular = -1.0;
    distanceConsigne = 0;
    thetaConsigne = 0;
    while(1){
    }
}

