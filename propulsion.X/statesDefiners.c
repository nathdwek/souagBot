#include <p33FJ128MC804.h>

#include "init.h"
#include "globals.h"
#include "util.h"

void stop(){
    resetMotors();
    resetPositionVariables();
    resetStateVariables();
}

void straight(float targetDistance){
    stop();
    kp = 0.002;
    angularKp = 0.2;
    accelerating = sgn(targetDistance);
    goalDistance = targetDistance;
    goingStraight = 1;
}

void rotate(float angle){
    stop();
    kp = 0.00006;
    angularKp = 0.005;
    acceleratingAngular = sgn(angle);
    goalTheta  = angle;
    rotating = 1;
}