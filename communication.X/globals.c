//Constantes du uC
#define PROC_FCY 40000000

//Constantes pour l'UART
#define BAUDRATE 9600
const int BRGVAL = ((PROC_FCY / BAUDRATE) / 16) - 1;

//debug
char received;
char sent = 0b00000000;
