/* 
    src/core/uart.h

    MIT License

    Copyright (c) 2021 Julio Cesar Kochhann

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
 */
#ifndef UART_H
#define UART_H

/* UART0 (software UART) settings */
#define _UART0_RX_DIR       TRISAbits.TRISA0
#define _UART0_TX_DIR       TRISAbits.TRISA1
#define _UART0_RX_PIN       PORTAbits.RA0
#define _UART0_TX_PIN       PORTAbits.RA1

/* UART1 settings */
#define _UART1_BAUD_RATE     9600   // Default baud rate in bps
#define _UART1_RX_INT   // Comment out this line to disable receive interrupts
//#define _UART1_TX_INT

/* UART2 settings */
#define _UART2_BAUD_RATE     9600
#define _UART2_RX_INT
//#define _UART1_TX_INT

typedef union {
    uint16_t buffer;
    struct {
        uint8_t lsb : 1, : 0;
        uint8_t : 1, msb : 1;
    } bits;
} UART_Packet_t;

enum _UART_Bit_Fields {
    _UART_START_BIT = 0,
    _UART_STOP_BIT
};

enum _UART_Modules {
    #ifdef __UART1
    UART1,
    #endif
    #ifdef __UART2
    UART2,
    #endif
    UART0
};

#define UART0_Send( str )           UART_Send( str, UART0 )
#define UART0_Print( str )          UART_Print( str, UART0 )
#define UART0_Println( str )        UART_Print( str "\n", UART0 )
#define UART1_Send( str )           UART_Send( str, UART1 )
#define UART1_Print( str )          UART_Print( str, UART1 )
#define UART1_Println( str )        UART_Print( str "\n", UART1 )
#define UART2_Send( str )           UART_Send( str, UART2 )
#define UART2_Print( str )          UART_Print( str, UART2 )
#define UART2_Println( str )        UART_Print( str "\n", UART2 )

/* Function Prototypes */
inline void UART0_Flush(void);
void UART0_Init(void);
#pragma inline(UART0_ISR)
void UART0_ISR(void);
uint8_t UART0_Data(void);
inline bool UART0_Data_Available(void);
void UART1_Init(void);
inline uint8_t UART1_Data(void);
inline bool UART1_Data_Available(void);

uint8_t UART_Send(uint8_t b, uint8_t uid);          // Sends a byte to the UART
uint8_t UART_Print(const char* str, uint8_t uid);   // Sends a string to the UART

#endif // #ifndef UART_H