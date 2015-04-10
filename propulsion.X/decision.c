#include <p33FJ128MC804.h>

#include "regul.h"
#include "globals.h"
#include "util.h"
#include "wheels.h"

//Persistantes qui définissent l'état du robot
float accelerating;
float acceleratingAngular;
float goalDistance;
float goalTheta;
int goingStraight;
int rotating;

void resetStateVariables(){
    speedConsigne = 0;
    angularSpeedConsigne = 0;
    goalDistance = 0;
    accelerating = 0.0;
    acceleratingAngular = 0.0;
    kp = 0.00006;
    angularKp = 0.0001;
    distanceConsigne = 0;
    thetaConsigne = 0;
    goingStraight = 0;
    rotating = 0;
}

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

void interpretCommand(unsigned char command, unsigned char param){
    switch (command){
        case 0:
            straight( (char) param );
            break;
        case 1:
            rotate(param, -1);
            break;
        case 2:
            rotate(param, 1);
            break;
    }
}
