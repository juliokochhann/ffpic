/*
  TM1637 Display

  This program prints the value of a counter in two TM1637 display modules;
  One in decimal, another in hexadecimal.

  created 2021
  by kcjulio <https://github.com/kcjulio>

  This example code is in the public domain.
*/
#include "ffpic.h"  // FFPIC include file
#include "tm1637.h"

#define TM1_TRIS        &TRISC
#define TM1_PORT        &LATC
#define TM1_SCL_PIN     3
#define TM1_SDA_PIN     4
#define TM2_TRIS        &TRISC
#define TM2_PORT        &LATC
#define TM2_SCL_PIN     5
#define TM2_SDA_PIN     6

TM1637_t TM_Display1, TM_Display2;

int16_t counter1;

/* Interrupt service routine (ISR) */
void ISR(void)
{
    /* TODO Check interrupt flag bits to determine the source of an interrupt */
}

/* Setup routine: runs once at startup */
void setup(void)
{
    TM_Init(&TM_Display1, TM1_TRIS, TM1_PORT, TM1_SCL_PIN, TM1_SDA_PIN);
    TM_Init(&TM_Display2, TM2_TRIS, TM2_PORT, TM2_SCL_PIN, TM2_SDA_PIN);
    
    TM_Clear(&TM_Display1);
    TM_Set_PWM(&TM_Display1, PWM4_16);

    TM_Clear(&TM_Display2);
    TM_Set_PWM(&TM_Display2, PWM4_16);
}

/* Infinite loop routine: runs repeatedly */
void loop(void)
{
    TM_Display1.cursor = 0;
    TM_Print_Int(&TM_Display1, counter1, 10);

    TM_Display2.cursor = 0;
    TM_Print_Int(&TM_Display2, counter1, 16);

    counter1++;

    pause(1000);
}