/* 
    src/core/system.h

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
#ifndef SYSTEM_H
#define SYSTEM_H

/* Pre-defined oscillator options */
#define OSC_32KHz       32768
#define OSC_4MHz        4000000
#define OSC_8MHz        8000000
#define OSC_16MHz       16000000
#define OSC_20MHz       20000000

#define F_CPU           OSC_4MHz        // Define sys. osc here
#define _XTAL_FREQ      F_CPU
#define pause( n )      __delay_ms( n )
#define pause_us( n )   __delay_us( n )

/* Sys Prototypes */
#pragma inline(configure_oscillator)
void configure_oscillator(void);

#pragma inline(loop)
void loop(void);

#pragma inline(setup)
void setup(void);

void main(void);

#endif