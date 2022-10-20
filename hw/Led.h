#ifndef SRC_HW_LED_H_
#define SRC_HW_LED_H_

#include <stdio.h>
#include "xil_printf.h"
#include "xparameters.h"
#include "xgpio.h"
#include "sleep.h"

#define CHANNEL_1 1

#define LED_0 0
#define LED_1 1
#define LED_2 2
#define LED_3 3

XGpio GPIO_LED;

typedef struct _ledInst{
	int ledNum;
}Led;

void Led_Init();
void Led_MakeInst(Led* led, int ledNum);
void Led_On(Led* led);
void Led_Off(Led* led);
void Led_Toggle(Led* led);
void Led_ShiftRight();
void Led_ShiftLeft();

#endif /* SRC_HW_LED_H_ */
