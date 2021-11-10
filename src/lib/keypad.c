/* 
    src/lib/keypad.c

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
#include "arch.h"
#include "keypad.h"

char Keypad_Read(Keypad_t* k) {
    *k->port = 0;

    // Scan rows
    *k->tris = 0xF0;   // Set row pins as inputs
    k->matrix.row = ~(*k->port >> 4) & 0x0F;

    // Scan columns
    *k->tris = 0x0F;   // Set column pins as inputs 
    k->matrix.col = ~(*k->port) & 0x0F;

    if (k->matrix.row) {
        uint8_t log_row, log_col;
        log_row = log_col = 0;

        // Find integer log base 2 of an integer (aka the position of the highest bit set)
        while (k->matrix.row >>= 1)
            log_row++;

        while (k->matrix.col >>= 1)
            log_col++;

        return keypad_map[log_row][log_col];    // Return the key's ASCII code
    }

    return 0;
}