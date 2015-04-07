#include <p33FJ128GP802.h>

int main(void){
    init();
    TRISAbits.TRISA0 = 0;
    LATAbits.LATA0 = 1;
    while(1){
    }
}
