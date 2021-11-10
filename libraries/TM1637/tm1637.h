/* 
    libraries/tm1637.h

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
#ifndef TM1637_H
#define TM1637_H

#include "i2c.h"

enum _TM_CMD1 {
    _DATA_COMMAND = 0100,
    _NORMAL_MODE = 0,
    _TEST_MODE = 8,
    _AUTO_INC = 0,
    _FIX_ADDR = 4,
    _DATA_WRITE = 0,
    _DATA_READ = 2
};

enum _TM_CMD2 {
    _ADDRESS_COMMAND = 0300
};

enum _TM_CMD3 {
    _CONTROL_COMMAND = 0200,
    PWM_OFF = 0,
    PWM1_16 = 010,
    PWM2_16,
    PWM4_16,
    PWM10_16,
    PWM11_16,
    PWM12_16,
    PWM13_16,
    PWM14_16
};

typedef struct {
    I2C_t i2c;
    uint8_t cursor;
} TM1637_t;

void TM_Init(TM1637_t* tm, volatile uint8_t* tris, volatile uint8_t* port, 
             uint8_t scl_pin, uint8_t sda_pin);
void TM_Clear(TM1637_t* tm);
void TM_Print(TM1637_t* tm, uint8_t d);
void TM_Print_Chr(TM1637_t* tm, char c);
void TM_Print_Int(TM1637_t* tm, int16_t n, uint8_t base);
void TM_Print_Str(TM1637_t* tm, char *s);
void TM_Set_PWM(TM1637_t* tm, uint8_t p);
inline void TM_Set_Cursor(TM1637_t* tm, uint8_t c);
inline uint8_t TM_Get_Cursor(TM1637_t* tm);

#endif