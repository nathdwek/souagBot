#include <p33FJ128MC804.h>

#include "regul.h"
#include "globals.h"
#include "util.h"
#include "wheels.h"

//Persistantes qui définissent l'état du robot
float acceleration;
char acceleratingAngular;
char goalDistance;
char decelerationDistance;
float goalTheta;
char goingStraight;
char rotating;

void resetStateVariables(){
    speedConsigne = 0;
    angularSpeedConsigne = 0;
    goalDistance = 0;
    acceleration = 0;
    acceleratingAngular = 0;
    kp = 0.00006;
    angularKp = 0.0001;
    distanceConsigne = 0;
    decelerationDistance = DFLT_DECELERATION_DST;
    thetaConsigne = 0;
    goingStraight = 0;
    rotating = 0;
}

void stop(){
    resetMotors();
    resetPositionVariables();
    resetStateVariables();
}

void straight(char newGoalDistance){
    stop();
    kp = 0.002;
    angularKp = 0.2;
    acceleration = sgn(newGoalDistance)*ACCELERATION;
    goalDistance = newGoalDistance;
    decelerationDistance = goalDistance/3;
    if (decelerationDistance > DFLT_DECELERATION_DST){
        decelerationDistance = DFLT_DECELERATION_DST;
    }
    goingStraight = 1;
}

void rotate(char angleInDegrees, char way){
    stop();
    int signedAngleInDegrees = angleInDegrees * way;
    float angleInRadians = signedAngleInDegrees;
    angleInRadians = angleInRadians*3.141592/180.0;
    kp = 0.00006;
    angularKp = 0.005;
    acceleratingAngular = way;
    goalTheta  = angleInRadians;
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
