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
    configRegul();
    while(1){
    }
}

