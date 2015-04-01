#include <p33FJ128MC804.h>

#include "init.h"
#include "globals.h"

void stop(){
    resetMotors();
    resetPositionVariables();
    resetStateVariables();
}

void straight(float distance){
    stop();
    kp = MAIN_KP;
    angularKp = PERTURB_KP;
}

void rotate(float angle){
    stop();
    kp = PERTURB_KP;
    angularKp = MAIN_KP;
}