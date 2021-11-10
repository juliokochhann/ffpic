/* 
    src/lib/queue.c

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
#include "queue.h"

inline bool Queue_Empty(Queue_t* q) {
    return !q->size;
}

inline bool Queue_Full(Queue_t* q) {
    return q->last == q->max_size;
}

void Queue_Insert(Queue_t* q, uint8_t val) {
    if ( Queue_Full(q) )
        q->last = 0;

    q->data[q->last++] = val;
    q->size++;
}

void Queue_Init(Queue_t* q)
{
    q->max_size = _QUEUE_MAX_SIZE;
    q->first = 0;
    q->last = 0;
    q->size = 0;
}

uint8_t Queue_Retrieve(Queue_t* q) {
    uint8_t val = 0;

    if ( Queue_Empty(q) )
        return val;
    
    val = q->data[q->first++];
    q->size--;

    if (q->first == q->max_size) q->first = 0;

    return val;
}