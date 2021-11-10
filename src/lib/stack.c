/* 
    src/lib/stack.c

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
#include "stack.h"

inline bool Stack_Empty(Stack_t* s) { return s->top == -1; }

inline bool Stack_Full(Stack_t* s) { return s->top == s->max_size - 1; }

void Stack_Init(Stack_t* s)
{
    s->max_size = _STACK_MAX_SIZE;
    s->top = -1;
}

inline uint8_t Stack_Peek(Stack_t* s) { return !Stack_Empty(s) ? s->data[s->top] : 0; }

inline uint8_t Stack_Pop(Stack_t* s) { return !Stack_Empty(s) ? s->data[s->top--] : 0; }

void Stack_Push(Stack_t* s, uint8_t val)
{
    if (!Stack_Full(s))
        s->data[++s->top] = val;
}