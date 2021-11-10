/* 
    src/core/timer.h

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
#ifndef TIMER0_H
#define TIMER0_H

/* Enable Timer 0 Overflow Interrupt */
#define _TIMER0_INT     // Comment this line to disable Timer 0 interrupts

extern uint8_t tmr0_reg;

enum _TMR0_Edge {
    T0SE_LOW_TO_HIGH = 0,
    T0SE_HIGH_TO_LOW
};

enum _TMRO_Mode {
    TIMER_MODE = 0,
    COUNTER_MODE
};

enum _TMR0_PS {
    PS_TMR0_1TO2 = 0,
    PS_TMR0_1TO4,
    PS_TMR0_1TO8,
    PS_TMR0_1TO16,
    PS_TMR0_1TO32,
    PS_TMR0_1TO64,
    PS_TMR0_1TO128,
    PS_TMR0_1TO256
};

enum _TMR0_PSA {
    PSA_TIMER = 0,
    PSA_WDT
};

#define TIMER0_Edge(e)              OPTION_REGbits.T0SE = e
#define TIMER0_Load(v)              TMR0 = tmr0_reg = v
#define TIMER0_Overflow()           INTCONbits.T0IF
#define TIMER0_Prescaler(p)         OPTION_REG = (OPTION_REG & 0xF8) | p
#define TIMER0_Reset()  \
    TMR0 = tmr0_reg;    \
    INTCONbits.T0IF = 0

/* Function Prototypes */
void TIMER0_Init(uint8_t mode, uint8_t psa);

/* Notes:
    Timer 0 Overflow Period and Frequency equations:
    T = (256 - TMR0) * tmr0_prescaler * (1 / (F_CPU / 4))

    Solving for tmr0_prescaler:
    tmr0_prescaler = T / (256 - TMR0) * (1 / (F_CPU / 4))

    Solving for TMR0:
    256 - TMR0 = T / (tmr0_prescaler * (1 / (F_CPU / 4)))
    - TMR0 = (T / (tmr0_prescaler * (1 / (F_CPU / 4)))) - 256
    TMR0 = 256 - (T / (tmr0_prescaler * (1 / (F_CPU / 4))))
 
    Frequency equation:
    f = 1 / T
 */

#endif