/* 
    src/core/eeprom.c

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
#include <xc.h>
#include "eeprom.h"
#include "arch.h"

#ifdef __EEPROM

uint8_t EEPROM_Read(uint16_t addr)
{
    EEADR = (uint8_t)addr;
    EECON1bits.RD = 1;      // Start reading operation

    return EEDATA;
}

void EEPROM_Write(uint16_t addr, uint8_t val)
{
    di();

    // Configure EEPROM interrupts
    #ifdef _EEPROM_WR_INT
    INTCONbits.EEIE = 1;    // Enables the EEPROM Write Operation Interrupt
    #endif

    EEADR = (uint8_t)addr;
    EEDATA = val;
    EECON1bits.WREN = 1;    // Allow write cycles

    // Sequence to initiate the write operation
    EECON2 = 0x55;
    EECON2 = 0xAA;
    EECON1bits.WR = 1;      // Initiates the write cycle

    while (EECON1bits.WR);  // Wait until write process is finished

    EECON1bits.WREN = 0;
    
    ei();
}

bool EEPROM_Write_Verify(uint16_t addr, uint8_t val)
{
    EEPROM_Write(addr, val);

    return EEPROM_Read(addr) == val;
}

inline bool EEPROM_Write_Error(void) { return EECON1bits.WRERR; }

#endif