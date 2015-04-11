#include <p33FJ128MC804.h>

#include "globals.h"
#include "decision.h"
#include "wheels.h"
#include "util.h"

//coeffs de la régul
float kp;
float angularKp;

//consignes. Globales car sont le résultats d'une intégrale
float distanceConsigne;
float thetaConsigne;
//Consignes intermédiaires (sont uniquement intégrées pour obtenir les consignes
//de position.
float speedConsigne;
float angularSpeedConsigne;

void configRegul(){
    //Timer de la régulation
    T1CONbits.TCKPS = 0b10;//Prescaler 64
    PR1=PROC_FCY/(REGUL_FCY*64);
    IEC0bits.T1IE = 1;//active l'interruption
    T1CONbits.TON = 1;//lance le timer
    //Crée des consignes qui mettent le robot à l'arrêt.
    resetStateVariables();
}

void accelerate(float* speed, float acceleration,
                char* accelerating, float maxSpeed){
    *speed = *speed+(*accelerating)*(acceleration)/REGUL_FCY;
    if (fabs(*speed) > maxSpeed && sgn(*accelerating) == sgn(goalDistance)){
        *accelerating = 0;
    }
}


void updateConsignes(void){
    distanceConsigne = distanceConsigne + speedConsigne/REGUL_FCY;
    thetaConsigne = thetaConsigne + angularSpeedConsigne/REGUL_FCY;
    accelerate(&speedConsigne, ACCELERATION,
               &accelerating, MAX_SPEED);
    accelerate(&angularSpeedConsigne, ANGULAR_ACCELERATION,
               &acceleratingAngular, MAX_ANGULAR_SPEED);
}

void setPWMs(float distance){
    float distanceError = (distanceConsigne - distance);
    float thetaError = (thetaConsigne - theta);

    float leftPWM = 0.15 + kp * distanceError;
    float rightPWM = 0.15 - kp * distanceError;

    leftPWM = leftPWM - angularKp * thetaError;
    rightPWM = rightPWM - angularKp * thetaError;

    OC2RS = leftPWM * PR2;
    OC1RS = rightPWM * PR2;
}

void checkTerminalConditions(){
    if (goingStraight == 1){
        if (fabs(sgn(goalDistance)*(goalDistance-distanceConsigne) - 16) < 1){
            accelerating = -sgn(goalDistance);
        }
        else if (fabs(goalDistance - distanceConsigne) < 1){
            accelerating = 0.0;
            speedConsigne = 0.0;
        }
    }
    else if (rotating == 1){
        if (fabs(fsgn(goalTheta)*(goalTheta-thetaConsigne) - 1.5) < 0.05){
            acceleratingAngular = -fsgn(goalTheta);
        }
        else if (fabs(goalTheta - thetaConsigne) < 0.05){
            acceleratingAngular = 0.0;
            angularSpeedConsigne = 0.0;
        }
    }
}

void _ISR _T1Interrupt(void){
    IFS0bits.T1IF = 0;

    float distance=readDistances();

    setPWMs(distance);

    checkTerminalConditions();
    updateConsignes();
}