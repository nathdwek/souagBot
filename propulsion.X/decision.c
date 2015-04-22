#include <p33FJ128MC804.h>

#include "globals.h"
#include "regul.h"
#include "globals.h"
#include "util.h"
#include "wheels.h"

//Persistantes qui définissent l'état du robot
float acceleration;
float angularAcceleration;
char goalDistance;
char decelerationDistance;
float goalTheta;
float decelerationTheta;
char goingStraight;
char rotating;

void resetStateVariables(){
    speedConsigne = 0;
    angularSpeedConsigne = 0;
    goalDistance = 0;
    acceleration = 0;
    angularAcceleration = 0;
    kp = 0.00006;
    angularKp = 0.0001;
    distanceConsigne = 0;
    decelerationDistance = DFLT_DECELERATION_DST;
    thetaConsigne = 0;
    decelerationTheta = DFLT_DECELERATION_THETA;
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
    if (decelerationDistance > goalDistance/3){
        decelerationDistance = goalDistance/3;
    }
    goingStraight = 1;
}

void rotate(unsigned char angleInDegrees, char sgn){
    stop();
    kp = 0.00006;
    angularKp = 0.05;
    angularAcceleration = sgn*ANGULAR_ACCELERATION;
    goalTheta = (PI/180.0 * (float)angleInDegrees * (float)sgn);
    if(decelerationTheta > goalTheta/3){
        decelerationTheta = goalTheta/3;
    }
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
