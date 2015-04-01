#include "globals.h"
#include "init.h"

float fabs(float number){
    if (number > 0)
        return number;
    else 
        return -number;
}

int sgn(float number){
    if (number<0)
        return -1;
    else if (number>0)
        return 1;
    else
        return 0;
}

void accelerate(float* speed, float acceleration,
                float* accelerating, float maxSpeed){
    *speed = *speed+(*accelerating)*(acceleration)/REGUL_FCY;
    if (fabs(*speed) > maxSpeed && sgn(*accelerating) == sgn(goalDistance)){
        *accelerating = 0.0;
    }
}
