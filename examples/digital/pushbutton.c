/*
  Pushbutton

  Turns on and off a light emitting diode (LED) connected to digital pin RA0,
  when pressing a pushbutton attached to pin RB0.

  created 2021
  by kcjulio <https://github.com/kcjulio>

  This example code is in the public domain.
*/
#include "ffpic.h"  // FFPIC include file

/* IO pin mapping */
#define BTN_TRIS    &TRISB
#define BTN_PORT    &PORTB
#define BTN_PIN     0
#define LED         PORTAbits.RA0

/* Global Variables */
Button_t btn0 = {BTN_TRIS, BTN_PORT, BTN_PIN, ACTIVE_HIGH}; // Create a Button instance

/* Interrupt service routine (ISR) */
void ISR(void)
{
    /* TODO Check interrupt flag bits to determine the source of an interrupt */
}

/* Setup routine: runs once at startup */
void setup(void)
{    
    /* Configure I/O Direction (TRISx): 1nput | 0utput */
    TRISA = 0xFE;   // 0b11111110
    
    /* Set I/O latches (PORTx or LATx): h1gh | l0w */
    PORTA = 0;
}

/* Infinite loop routine: runs repeatedly */
void loop(void)
{
    if (Button_Press(&btn0)) {
        Button_Debounce(50);                // Debounce 50ms
        while ( Button_Press(&btn0) );      // While the button is not released

        LED = !LED;                         // Toggle LED
    }
}