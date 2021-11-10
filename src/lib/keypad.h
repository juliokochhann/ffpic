/* 
    src/lib/keypad.h

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
#ifndef KEYPAD_H
#define KEYPAD_H

// Keypad key map
const char keypad_map[4][4] = {{'D', '.', '0', '*'},
                               {'C', '9', '8', '7'},
                               {'B', '6', '5', '4'},
                               {'A', '3', '2', '1'}};

struct Keypad_Matrix_s {
    uint8_t row : 4;
    uint8_t col : 4;
};

typedef struct {
    volatile uint8_t* tris;
    volatile uint8_t* port;
    struct Keypad_Matrix_s matrix;
} Keypad_t;

/* Function Prototypes */
char Keypad_Read(Keypad_t* k);

#endif