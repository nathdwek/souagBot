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
    configPWM();
    configQEI();
    configRegul();
    OC1RS = 7500;
    OC2RS = 7500;
    while(1){
    }
}

