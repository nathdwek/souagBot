#include "globals.h"

//Constantes pour l'UART
#define BAUDRATE 9600
#define BRGH_COEFF 4
const int BRGVAL = ((PROC_FCY / BAUDRATE) / BRGH_COEFF) - 1;

