/* 
    src/lib/queue.h

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
#ifndef Queue_H
#define Queue_H

// Define default queue
#define _QUEUE_MAX_SIZE     20  // Max. number of elements in the queue

/* Queue Data Structure */
typedef struct {
    uint8_t max_size;
    uint8_t data[_QUEUE_MAX_SIZE];
    uint8_t first;
    uint8_t last;
    uint8_t size;
} Queue_t;

/* Function Prototypes */
inline bool Queue_Empty(Queue_t* q);
inline bool Queue_Full(Queue_t* q);
void Queue_Init(Queue_t* q);
void Queue_Insert(Queue_t* q, uint8_t val);
uint8_t Queue_Retrieve(Queue_t* q);

#endif