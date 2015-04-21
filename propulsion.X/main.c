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
    //initUart();
    rotate(90, 1);
    while(1){
    }
}

