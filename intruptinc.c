#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <math.h>
#include <p18f4321.h>//remeber to modify
#include <usart.h>


void Do_Init();
void __interrupt (high_priority)High_IRS(void);
void __interrupt (low_priority)Low_IRS(void);
void INT1_ISR();
void INT2_ISR();
void display();

int INT0_flag = 0;
int INT1_flag = 0;
int INT2_flag = 0;
int val = 0;

void Do_Init() // Initialize the ports
{
    
    OSCCON = 0x60; //0110
     ADCON1= 0x0F; //1111 as Digital input
 // programming of ADCON1
    OSCCON=0x70; // Set oscillator to 8 MHz
    TRISB = 0xFF; // 111
    TRISC = 0xF0;//1111_0000
    TRISD = 0xF0;//1111_0000
 //x that all the INTx pins are
 // inputs
    TRISD = 0x00;
    
    INTCON3bits.INT1IF = 0; // Clear INT0IF
    INTCON3bits.INT1IP=1; // Set INT0 IE
    INTCON3bits.INT1IE =1;
    
    
    INTCON3bits.INT2IF = 0; // Clear INT0IF
    INTCON3bits.INT2IE =1; // Set INT0 IE
    INTCON3bits.INT2IP=0; // Set the Global Interrupt Enable
    PORTD = 0;
//    INTCONbits.GIE=1; 
//    INTCONbits.INT0IF = 0; // Clear INT0IF
//    INTCONbits.INT0IE =1; // Set INT0 IE
//    
    RCONbits.IPEN = 1;
    INTCONbits.GIEH=1; // Set the Global Interrupt Enable
    INTCONbits.GIEL=1; // Set the Global Interrupt Enable
    
    PORTD = 0;
  
    
}



void __interrupt (high_priority)High_IRS(void){
    display();
    INTCON3bits.INT1IF = 0;
}

void __interrupt (low_priority)Low_IRS(void){
    display();
    INTCON3bits.INT2IF = 0;
}

void main()
{
    Do_Init(); // Initialization
    val = 0;
    while(1){
        display();
    }
    
} 
void display(){
    if(INTCON3bits.INT1IF == 1){
        val = val+1;
    }else if(INTCON3bits.INT2IF ==1){
        val = val-1; 
    }
    if(val > 99){
        val = 99;
    }
    PORTC = 0xF0+(val/10); //98->0xF9(input 1001 for first 4 bits)->9)
    PORTD = 0xF0+(val%10); //98->0xF8, got 8 as result.
    return ;
}

