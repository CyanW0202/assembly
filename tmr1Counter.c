#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <math.h>
#include <p18f4321.h>
#include <usart.h>
#include <string.h>
/*
 *Use timer1 as counter, pulling mode, generate a sqaure wave from portD bits 7.
 */

/*
 * 4ms period, need to toggle every 2ms.
 * T = 4/4M = 1micro second,  2ms/(1micros*8prescale) = 0.25k = 250 count
 * 250+1 = 251, 2^8 = 256, 255-251 = 4, the TMR1 = 0xFF04. 
 */

int main(){
    TRISDbits.TRISD7 = 0;//square wave output.
    T1CON = 0xB0; //1:8 prescaler
    PIR1bits.TMR1IF = 0;
    PIE1bits.TMR1IE = 1;
    TMR1 = 0xFF04; //16bits
    PORTDbits.RD7 = 0;
    while(1){
        T1CONbits.TMR1ON = 1;
        while(PIR1bits.TMR1IF = 0);
        T1CONbits.TMR1ON = 0;
        PORTDbits.RD7 = ~PORTDbits.RD7;
        TMR1IF = 0;
        TMR1 = 0xFF04; //16bits
    }   
}
