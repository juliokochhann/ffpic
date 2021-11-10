/* 
    src/core/i2c.h

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
#ifndef I2C_H
#define I2C_H

/* The delay, in microseconds, between bit transition on the serial bus connected to the display */
#define _I2C_BIT_DELAY  100

enum _I2C_Bit_Fields {
    _I2C_ACK = 0,
    _I2C_NACK,
    _I2C_WRITE_BIT = 0,
    _I2C_READ_BIT
};

typedef struct {
    volatile uint8_t*   tris;
    volatile uint8_t*   port;
    uint8_t             scl_pin;
    uint8_t             sda_pin;
} I2C_t;

/* Function Prototypes */
void I2C_Init(I2C_t* i2c, volatile uint8_t* tris, volatile uint8_t* port, 
              uint8_t scl_pin, uint8_t sda_pin);
static void I2C_Clock(I2C_t* i2c);
uint8_t I2C_Send(I2C_t* i2c, uint8_t b);
void I2C_Start(I2C_t* i2c);
void I2C_Stop(I2C_t* i2c);

void I2C1_Init(void);
uint8_t I2C1_Send(uint8_t b);
inline void I2C1_Start(void);
inline void I2C1_Stop(void);

#endif
