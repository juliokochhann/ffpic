/* 
    src/core/uart.c

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
#include <stdbool.h>
#include <stdint.h>
#include <xc.h>
#include "arch.h"
#include "io.h"
#include "system.h"
#include "timer.h"
#include "uart.h"

UART_Packet_t _rx_packet, _rx_data, _tx_packet;

inline void UART0_Flush(void) { _rx_packet.buffer = 0; }

void UART0_Init(void)
{
    /* Set-up timer 0 for generating the required baudrate */
    TIMER0_Init(TIMER_MODE, PSA_TIMER);

    switch (F_CPU) {
        case OSC_4MHz:
            TIMER0_Prescaler(PS_TMR0_1TO4);
            TIMER0_Load(235);
            break;
        case OSC_8MHz:
            TIMER0_Prescaler(PS_TMR0_1TO8);
            TIMER0_Load(233);
            break;
        case OSC_16MHz:
            TIMER0_Prescaler(PS_TMR0_1TO16);
            TIMER0_Load(231);
            break;
        case OSC_20MHz:
            TIMER0_Prescaler(PS_TMR0_1TO32);
            TIMER0_Load(195);
            break;
        default:
            break;
    }

    _UART0_RX_DIR = INPUT;
    _UART0_TX_DIR = OUTPUT;
    _UART0_TX_PIN = HIGH;
}

void UART0_ISR(void)
{
    if (TIMER0_Overflow()) {
        TIMER0_Reset();

        _rx_packet.buffer |= !(_UART0_RX_PIN);
        SHIFT_LEFT(_rx_packet.buffer, 1);

        if (_rx_packet.bits.msb == _UART_STOP_BIT) {
            _rx_data = _rx_packet;    // copy packet
            _rx_packet.buffer = 0;
        }

        if (_tx_packet.buffer) {
            _UART0_TX_PIN = _tx_packet.bits.lsb;

            SHIFT_RIGHT(_tx_packet.buffer, 1);
        }
    }
}

uint8_t UART0_Data(void)
{
    _rx_data.bits.msb = 0;

    return ~reverseBits( (uint8_t)(_rx_data.buffer >> 1) );
}

inline bool UART0_Data_Available(void) { return _rx_data.bits.msb; }

#ifdef __UART1

void UART1_Init(void)
{
    /* USART Baud Rate Generator (BRG) */
    SPBRG = (uint8_t)((F_CPU / _UART1_BAUD_RATE) / 16.0 - 1);

    /* Configurations for the RCSTA - RECEIVE STATUS AND CONTROL REGISTER (ADDRESS: 18h) */
    RCSTAbits.SPEN = 1; // Serial Port Enable bit: 1 - Serial port enabled
    RCSTAbits.RX9 = 0;  // 9-bit Receive Enable bit: 0 - Selects 8-bit reception
    RCSTAbits.CREN = 1; // Continuous Receive Enable bit: 1 - Enables continuous receive
    RCSTAbits.FERR = 0; // Framing Error bit: 0 - No framing error
    RCSTAbits.OERR = 0; // Overrun Error bit: 0 - No overrun error

    /* Configurations for the TXSTA - TRANSMIT STATUS AND CONTROL REGISTER (ADDRESS: 98h) */
    TXSTAbits.TX9 = 0;  // 9-bit Transmit Enable bit: 0 - Selects 8-bit transmission
    TXSTAbits.TXEN = 1; // Transmit Enable bit: 1 - Transmit enabled
    TXSTAbits.SYNC = 0; // USART Mode Select bit: 0 - Asynchronous mode
    TXSTAbits.BRGH = 1; // High Baud Rate Select bit: 1 - High speed

    #ifdef _UART1_RX_INT
    PIE1bits.RCIE = 1;
    INTCONbits.PEIE = 1;
    ei();
    #endif
    
    #ifdef _UART1_TX_INT
    PIEbits.TXIE = 1;
    INTCONbits.PEIE = 1;
    ei();
    #endif
}

/* Return the UART Reception flag bit */
inline bool UART1_Data_Available(void) { return PIR1bits.RCIF; }

/* Return the first byte from the RCREG FIFO (RCIF is automatically cleared) */
inline uint8_t UART1_Data(void) { return RCREG; }

#endif // __UART1

uint8_t UART_Send(uint8_t b, uint8_t uid)
{
    switch (uid) {
        case UART0:
            _tx_packet.bits.lsb = _UART_START_BIT;
            _tx_packet.buffer |= (uint16_t) b << 1U; // align byte in buffer
            _tx_packet.bits.msb = _UART_STOP_BIT;

            while (_tx_packet.buffer)    // wait until buffer is empty
                continue;
            break;
        #ifdef __UART1
        case UART1:
            while (!TXSTAbits.TRMT)     // wait until the transmit register is empty
                continue;
            TXREG = b;                  // load tx buffer
            break;
        #endif
        #ifdef __UART2
        case UART2:
            break;
        #endif
    }

    return 1;
}

uint8_t UART_Print(const char* str, uint8_t uid)
{
    uint8_t sent = 0;

    while (*str)
        sent += UART_Send((uint8_t)*str++, uid);

    return sent;
}