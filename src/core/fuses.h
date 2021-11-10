/* 
    src/core/fuses.h

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
#ifndef FUSES_H
#define FUSES_H
/* #pragma config Settings */

/* MCU: PIC16F84A */
/* Register: CONFIG @ 0x2007 */
#ifdef _16F84A
#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config CP = OFF
/* Register: IDLOC0 @ 0x2000, IDLOC1 @ 0x2001, IDLOC2 @ 0x2002, IDLOC3 @ 0x2003 */
/* #pragma config IDLOC0 = 0x127
#pragma config IDLOC1 = 0x127
#pragma config IDLOC2 = 0x127
#pragma config IDLOC3 = 0x127 */
#endif

/* MCU: PIC16F628A */
/* Register: CONFIG @ 0x2007 */
#ifdef _16F628A
#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config MCLRE = ON
#pragma config BOREN = OFF
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config CP = OFF
/* Register: IDLOC0 @ 0x2000, IDLOC1 @ 0x2001, IDLOC2 @ 0x2002, IDLOC3 @ 0x2003 */
/* #pragma config IDLOC0 = 0x127
#pragma config IDLOC1 = 0x127
#pragma config IDLOC2 = 0x127
#pragma config IDLOC3 = 0x127 */
#endif

/* MCU: PIC16F1933 */
/* Register: CONFIG1 @ 0x8007*/
#ifdef _16F1933
#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config MCLRE = ON
#pragma config CP = OFF
#pragma config CPD = OFF
#pragma config BOREN = OFF
#pragma config CLKOUTEN = OFF
#pragma config IESO = ON
#pragma config FCMEN = ON
/* Register: CONFIG2 @ 0x8008 */
#pragma config WRT = OFF
#pragma config VCAPEN = OFF
#pragma config PLLEN = OFF
#pragma config STVREN = ON
#pragma config BORV = LO
#pragma config LVP = OFF
/* Register: IDLOC0 @ 0x8000, IDLOC1 @ 0x8001, IDLOC2 @ 0x8002, IDLOC3 @ 0x8003 */
/* #pragma config IDLOC0 = 0x127
#pragma config IDLOC1 = 0x127
#pragma config IDLOC2 = 0x127
#pragma config IDLOC3 = 0x127 */
#endif

#endif