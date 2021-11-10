/*
  Blink
  
  Turns on an LED for half a second, then off for another, repeatedly.

  created 2021
  by kcjulio <https://github.com/kcjulio>

  This example code is in the public domain.
*/
#include "ffpic.h"  // FFPIC include file

/* IO pin mapping */
#define LED_TRIS    TRISAbits.TRISA0
#define LED         PORTAbits.RA0

/* Interrupt service routine (ISR) */
void ISR(void)
{
    /* TODO Check interrupt flag bits to determine the source of an interrupt */
}

/* Setup routine: runs once at startup */
void setup(void)
{
    LED_TRIS = OUTPUT;
    LED = LOW;
}

/* Infinite loop routine: runs repeatedly */
void loop(void)
{
    LED = !LED;     // Invert LED state;
    pause( 500 );
}