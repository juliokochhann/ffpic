/* 
    src/lib/lut.h

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
#ifndef LUT_H
#define LUT_H

enum Seven_Segment_Char {
    SS_A = 0x77,            // A
    SS_B = 0x7C,            // B
    SS_C = 0x39,            // C
    SS_D = 0x5E,            // D
    SS_E = 0x79,            // E
    SS_F = 0x71,            // F
    SS_H = 0x76,            // H
    SS_I = 0x30,            // I
    SS_J = 0x0E,            // J
    SS_L = 0x38,            // L
    SS_O = 0x3F,            // O
    SS_P = 0x73,            // P
    SS_S = 0x6D,            // S
    SS_U = 0x3E,            // U
    SS_ZERO = 0x3F,         // 0
    SS_ONE = 0x06,          // 1
    SS_TWO = 0x5B,          // 2
    SS_THREE = 0x4F,        // 3
    SS_FOUR = 0x66,         // 4
    SS_FIVE = 0x6D,         // 5
    SS_SIX = 0x7D,          // 6
    SS_SEVEN = 0x07,        // 7
    SS_EIGHT = 0x7F,        // 8
    SS_NINE = 0x6F,         // 9
    SS_BLANK = 0x00,        // 
    SS_DOT = 0x80,          // .
    SS_DQUOTE = 0x22,       // "
    SS_EQUAL = 0x48,        // =
    SS_LBRACKET = 0x39,     // [
    SS_MINUS = 0x40,        // -
    SS_RBRACKET = 0x0F,     // ]
    SS_SQUOTE = 0x02,       // '
    SS_UNDERLINE = 0x08     // _
};

const uint8_t bcd_ss[10] = {SS_ZERO, SS_ONE, SS_TWO, SS_THREE, SS_FOUR, SS_FIVE, SS_SIX, SS_SEVEN, SS_EIGHT, SS_NINE};

const uint8_t ascii_ss[128] = {
                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                0, 0, SS_DQUOTE, 0, 0, 0, 0, SS_SQUOTE, 0, 0, 0, 0, 0, SS_MINUS, SS_DOT, 0,
                                SS_ZERO, SS_ONE, SS_TWO, SS_THREE, SS_FOUR, SS_FIVE, SS_SIX, SS_SEVEN, SS_EIGHT, SS_NINE, 0, 0, 0, SS_EQUAL, 0, 0,
                                0, SS_A, SS_B, SS_C, SS_D, SS_E, SS_F, 0, SS_H, SS_I, SS_J, 0, SS_L, 0, 0, SS_O,
                                SS_P, 0, 0, SS_S, 0, SS_U, 0, 0, 0, 0, 0, SS_LBRACKET, 0, SS_RBRACKET, 0, SS_UNDERLINE,
                                0, SS_A, SS_B, SS_C, SS_D, SS_E, SS_F, 0, SS_H, SS_I, SS_J, 0, SS_L, 0, 0, SS_O,
                                SS_P, 0, 0, SS_S, 0, SS_U, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                            };

#define ASCII_To_SS( bcd )      ascii_ss[ bcd ]

#endif