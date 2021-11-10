/*
  Square Wave

  Generates a square wave on RA0 pin using the Timer 0 module.
  The frequency is about ~500Hz/50% duty at 16MHz Fosc.

  created 2021
  by kcjulio <https://github.com/kcjulio>

  This example code is in the public domain.
*/
#include "ffpic.h"  // FFPIC include file

/* IO pin mapping */
#define CLK_OUT     PORTAbits.RA0

/* Interrupt service routine (ISR) */
void ISR(void)
{
    /* TODO Check interrupt flag bits to determine the source of an interrupt */

    if (TIMER0_Overflow()) {
        TIMER0_Reset(); // Clear Timer 0 interrupt flag and reload TMR0 register

        CLK_OUT = !CLK_OUT;    
    }
}

/* Setup routine: runs once at startup */
void setup(void)
{
    /* Configure I/O Direction (TRISx): 1nput | 0utput */
    TRISA = 0xFE;   // 0b11111110
    TRISB = 0xFF;
    
    /* Set I/O latches (PORTx or LATx): h1gh | l0w */
    PORTA = 0;
    PORTB = 0;

    TIMER0_Init(TIMER_MODE, PSA_TIMER);
    TIMER0_Prescaler(PS_TMR0_1TO16);
}

/* Infinite loop routine: runs repeatedly */
void loop(void)
{
    /* We don't need to do anything here in this case */
}