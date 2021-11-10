/* 
    src/core/i2c.c

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
#include "i2c.h"
#include "io.h"
#include "system.h"

void I2C_Init(I2C_t* i2c, volatile uint8_t* tris, volatile uint8_t* port, 
              uint8_t scl_pin, uint8_t sda_pin)
{
    i2c->tris = tris;
    i2c->port = port;
    i2c->scl_pin = scl_pin;
    i2c->sda_pin = sda_pin;

    SET_BIT(*i2c->tris, i2c->scl_pin);
    SET_BIT(*i2c->tris, i2c->sda_pin);
    CLEAR_BIT(*i2c->port, i2c->scl_pin);
    CLEAR_BIT(*i2c->port, i2c->sda_pin);
}

static void I2C_Clock(I2C_t* i2c)
{
    /* The data on the SDA line must be stable during the HIGH period of the clock. The HIGH
    or LOW state of the data line can only change when the clock signal on the SCL line is
    LOW. One clock pulse is generated for each data bit transferred. */
    TOGGLE_BIT(*i2c->tris, i2c->scl_pin);
    pause_us(_I2C_BIT_DELAY);
}

uint8_t I2C_Send(I2C_t* i2c, uint8_t b)
{
    /* After the START condition (S), a slave address is sent. This address is seven bits long
    followed by an eighth bit which is a data direction bit (R/W) — a ‘zero’ indicates a transmission (WRITE),
    a ‘one’ indicates a request for data (READ) */
    for (int8_t i = MSB; i >= LSB; i--) {
        I2C_Clock(i2c);

        if ( GET_BIT(b, i) )
            SET_BIT(*i2c->tris, i2c->sda_pin);
        else
            CLEAR_BIT(*i2c->tris, i2c->sda_pin);

        pause_us(_I2C_BIT_DELAY);

        I2C_Clock(i2c);
    }

    I2C_Clock(i2c);
    
    /* Release SDA line to receive the ACK bit */
    SET_BIT(*i2c->tris, i2c->sda_pin);
    pause_us(_I2C_BIT_DELAY);

    I2C_Clock(i2c);

    return GET_BIT(*i2c->port, i2c->sda_pin);
}

void I2C_Start(I2C_t* i2c)
{
    /* A HIGH to LOW transition on the SDA line while SCL is HIGH defines a START condition. */
    CLEAR_BIT(*i2c->tris, i2c->sda_pin);
    pause_us(_I2C_BIT_DELAY);
}

void I2C_Stop(I2C_t* i2c)
{
    /* A LOW to HIGH transition on the SDA line while SCL is HIGH defines a STOP condition. */
    I2C_Clock(i2c);

    CLEAR_BIT(*i2c->tris, i2c->sda_pin);
    pause_us(_I2C_BIT_DELAY);

    I2C_Clock(i2c);

    SET_BIT(*i2c->tris, i2c->sda_pin);
    pause_us(_I2C_BIT_DELAY);
}

#ifdef __I2C1
void I2C1_Init(void)
{
    SSPCON1bits.SSPEN = 1;      // Enable synchronous serial port
    SSPADD = 99;
    SSPCON |= 0x08;             // I2C master mode
}

uint8_t I2C1_Send(uint8_t b)
{
    PIR1bits.SSPIF = 0;

    SSPBUF = b;                 // Load SSPBUF with the byte
    while (SSPSTATbits.BF)      // Wait until all bits are shifted out
    ;

    while (!PIR1bits.SSPIF)
    ;

    return SSPCON2bits.ACKSTAT;
}

inline void I2C1_Start(void)
{
    SSPCON2bits.SEN = 1;        // Generate start condition
    while (SSPCON2bits.SEN)     // Wait until start sequence completes
    ;
}

inline void I2C1_Stop(void)
{
    SSPCON2bits.PEN = 1;        // Initiate stop condition
    while (SSPCON2bits.PEN)
    ;
}
#endif