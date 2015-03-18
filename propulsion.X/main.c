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
    acceleratingLeft = 1;
    acceleratingRight = 1;
    leftConsigne = 0;
    rightConsigne = 0;
    while(1){
    }
}

