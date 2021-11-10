/* 
    src/common/strtof.c

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
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "strtof.h"

float strtof(char* str)
{
    char* cp = str;
    float f = 0.0;

    if (*cp == '-')
        cp++;

    while (isdigit(*cp)) {
        f *= 10.0;
        f += *cp - '0';
        cp++;
    }

    if (*cp++ == '.') {
        if (isdigit(*cp)) {
            f += (float)(*cp - '0') / 10.0;
        }
    }

    if (*str == '-')
        f *= -1;

    return f;
}