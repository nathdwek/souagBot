/* 
 * File:   main.c
 * Author: labo
 *
 * Created on 4 mars 2015, 15:08
 */
#include <p33FJ128MC804.h>
#include "init.h"
#include "isrs.h"
#include "stateDefiners.h"

int main() {
    init();
    configPWM();
    configQEI();
    configRegul();
    rotate(1.57);
    while(1){
    }
}

