#include "globals.h"

//Constantes pour l'UART
#define BAUDRATE 9600
const int BRGVAL = ((PROC_FCY / BAUDRATE) / 16) - 1;

