/*
  Software serial

  This program listens to the serial port 0 (virtual port) and echoes back 
  the received data.

  created 2021
  by kcjulio <https://github.com/kcjulio>

  This example code is in the public domain.
*/
#include "ffpic.h"  // FFPIC include file

/* Interrupt service routine (ISR) */
void ISR(void)
{
    /* TODO Check interrupt flag bits to determine the source of an interrupt */
    UART0_ISR();
}

/* Setup routine: runs once at startup */
void setup(void)
{
    /* Initialize Software UART at 9600 bps */
    UART0_Init();

    pause(100); // wait a bit until uart0 stabilizes

    UART0_Println("Software serial");
}

/* Infinite loop routine: runs repeatedly */
void loop(void)
{    
    // if data has arrived in the UART module
    if (UART0_Data_Available())
        UART0_Send( UART0_Data() ); // Echo back
}