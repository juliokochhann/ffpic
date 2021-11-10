/* 
    src/core/arch.h

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
#ifndef ARCH_H
#define ARCH_H

#if defined(_PIC12) || defined(_PIC12E) || defined(_PIC12IE)
#define _PIC_BASELINE   // PIC12 (12-bit instruction Baseline Family)
#endif
#if defined(_PIC14) || defined(_PIC14E) || defined(_PIC14EX)
#define _PIC_MIDRANGE   // PIC14 (14-bit instruction Mid-range Family)
#endif

/* Not Architecture-specific */
#define MSB                         7
#define LSB                         0
/* Bitwise Macros */
#define SET_BIT(value, bit)         (value |= (1U << bit))
#define CLEAR_BIT(value, bit)       (value &= (~(1U << bit)))
#define TOGGLE_BIT(value, bit)      (value ^= (1U << bit))
#define GET_BIT(value, bit)         ((value >> bit) & 1U)
#define IS_BIT_SET(value, bit)      GET_BIT(value, bit)
#define SHIFT_RIGHT(value, bits)    (value >>= bits)
#define SHIFT_LEFT(value, bits)     (value <<= bits)

/* Bit swapping macro */
#define BIT_SWAP(b, n1, n2)             \
    do {                                \
        uint8_t tmp  = b.bits.b##n1;    \
        b.bits.b##n1 = b.bits.b##n2;    \
        b.bits.b##n2 = tmp;             \
    } while(0)

/* Byte type definition */
typedef union {
    uint8_t value;
    struct {
        uint8_t b0 : 1;
        uint8_t b1 : 1;
        uint8_t b2 : 1;
        uint8_t b3 : 1;
        uint8_t b4 : 1;
        uint8_t b5 : 1;
        uint8_t b6 : 1;
        uint8_t b7 : 1;
    } bits;
} Byte_t;

/* Prototypes */
uint8_t reverseBits(uint8_t value);

/* Architecture-specific hardware */
#ifdef _PIC_BASELINE

#endif // End _PIC_BASELINE

#ifdef _PIC_MIDRANGE

#ifdef EECON1
#define __EEPROM
#endif
#if defined(TMR0)
#define __TIMER0
#endif
#if defined(TXREG)
#define __UART1
#endif

#endif // End _PIC_MIDRANGE

#ifdef _PIC18

#endif

#endif // End _PIC18