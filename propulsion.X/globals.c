#include "globals.h"

//Constantes pour l'UART
#define BAUDRATE 9600
#define BRGH_COEFF 4
const int BRGVAL = ((PROC_FCY / BAUDRATE) / BRGH_COEFF) - 1;

//Constantes de la régulation
const int REGUL_FCY = 100;
const float CM_PER_TICK = 0.08;
const float ACCELERATION = 50;//cm par seconde au carré
const float ANGULAR_ACCELERATION = 4.44;//radians par seconde au carré
const float MAX_SPEED = 40;// cm par seconde
const float MAX_ANGULAR_SPEED = 3.55;//radians par seconde
