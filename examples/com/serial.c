/*
  Serial

  This program listens to the serial port and echoes back the received data
  every five seconds. This example uses a physical UART. In case the
  microcontroller you're using doesn't have one, check out the software_serial.c
  example.

  created 2021
  by kcjulio <https://github.com/kcjulio>

  This example code is in the public domain.
*/
#include "ffpic.h"  // FFPIC include file

/* Global Variables */
uint8_t rx_data;    // Holds the received byte
Queue_t uart_queue; // Create a queue to buffer the received data

/* Interrupt service routine (ISR) */
void ISR(void)
{
    /* TODO Check interrupt flag bits to determine the source of an interrupt */

    if (UART1_Data_Available()) {           // If data has arrived in the UART module
        rx_data = UART1_Data();             // Retrieve the data
        Queue_Insert(&uart_queue, rx_data); // Insert the data into the queue
    }
}

/* Setup routine: runs once at startup */
void setup(void)
{
    Queue_Init(&uart_queue);    // Initialize queue !important

    /* Initialize UART at the default Baud Rate (9600 bps) */
    UART1_Init();

    UART1_Println("Serial Echo:");
}

/* Infinite loop routine: runs repeatedly */
void loop(void)
{
    do {
        // Disable interrupts to prevent concurrent access to shared resources
        di();

        // Pop a byte from the queue (If empty, 0 is returned)
        rx_data = Queue_Retrieve(&uart_queue);

        ei();           // Re-enable interrupts

        if (rx_data)    // If data is available
            UART1_Send(rx_data);    // Echo back the received data
    }while (rx_data);   // While there are bytes in the queue

    pause( 5000 );
}

