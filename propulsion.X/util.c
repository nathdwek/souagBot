#include "globals.h"

float abs(float number){
    if (number > 0)
        return number;
    else 
        return -number;
}

void accelerate(float* speed, float acceleration,
                float* accelerating, float maxSpeed){
    *speed = *speed+(*accelerating)*(acceleration)/REGUL_FCY;
    if (*speed > maxSpeed){
        *accelerating = 0.0;
    }
}