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
