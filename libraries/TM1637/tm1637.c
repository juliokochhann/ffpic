/* 
    libraries/tm1637.c

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
#include <stdlib.h>
#include <xc.h>
#include "arch.h"
#include "i2c.h"
#include "lut.h"
#include "tm1637.h"

void TM_Init(TM1637_t* tm, volatile uint8_t* tris, volatile uint8_t* port, 
             uint8_t scl_pin, uint8_t sda_pin)
{
    tm->cursor = 0;

    I2C_Init(&tm->i2c, tris, port, scl_pin, sda_pin);

    TM_Clear(tm);

    TM_Set_PWM(tm, PWM14_16);
}

void TM_Clear(TM1637_t* tm)
{
    tm->cursor = 0;

    for (uint8_t i = 0; i < 6; i++)
        TM_Print(tm, 0);

    tm->cursor = 0;
}

void TM_Print(TM1637_t* tm, uint8_t d)
{
    if (tm->cursor >= 4) return;
    
    /* Send data command */
    I2C_Start(&tm->i2c);
    I2C_Send(&tm->i2c, reverseBits(_DATA_COMMAND+_NORMAL_MODE+_FIX_ADDR+_DATA_WRITE));
    I2C_Stop(&tm->i2c);

    /* Send address command and display data */
    I2C_Start(&tm->i2c);
    I2C_Send(&tm->i2c, reverseBits(_ADDRESS_COMMAND + tm->cursor));
    I2C_Send(&tm->i2c, reverseBits(d));
    I2C_Stop(&tm->i2c);

    tm->cursor++;
}

void TM_Print_Chr(TM1637_t* tm, char c)
{
    TM_Print( tm, ASCII_To_SS(c) );
}

void TM_Print_Int(TM1637_t* tm, int16_t n, uint8_t base)
{
    char str[20];

    itoa(str, n, base);

    TM_Print_Str(tm, str);
}

void TM_Print_Str(TM1637_t* tm, char *s)
{
    char c;

    while ( *s ) {
        c = ASCII_To_SS(*s);
        s++;

        if (*s == '.') {
            c |= SS_DOT;
            s++;
        }

        TM_Print(tm, c);
    }
}

void TM_Set_PWM(TM1637_t* tm, uint8_t p)
{
    /* Send control command */
    I2C_Start(&tm->i2c);
    I2C_Send(&tm->i2c, reverseBits(_CONTROL_COMMAND + p));
    I2C_Stop(&tm->i2c);
}

inline void TM_Set_Cursor(TM1637_t* tm, uint8_t c) { tm->cursor = c; }

inline uint8_t TM_Get_Cursor(TM1637_t* tm) { return tm->cursor; }