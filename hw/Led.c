#include "Led.h"

void Led_MakeInst(Led* led, int ledNum)
{
	led->ledNum = ledNum;
}

void Led_Init()
{
	XGpio_Initialize(&GPIO_LED, XPAR_AXI_GPIO_0_DEVICE_ID);
	XGpio_SetDataDirection(&GPIO_LED, CHANNEL_1, 0x00);
}

void Led_On(Led* led)
{
	int ledState = XGpio_DiscreteRead(&GPIO_LED, CHANNEL_1);
	XGpio_DiscreteWrite(&GPIO_LED, CHANNEL_1, ledState | (1 << led->ledNum));
}

void Led_Off(Led* led)
{
	int ledState = XGpio_DiscreteRead(&GPIO_LED, CHANNEL_1);
	XGpio_DiscreteWrite(&GPIO_LED, CHANNEL_1, ledState & ~(1 << led->ledNum));
}

void Led_Toggle(Led* led)
{
	int ledState = XGpio_DiscreteRead(&GPIO_LED, CHANNEL_1);
	XGpio_DiscreteWrite(&GPIO_LED, CHANNEL_1, ledState ^ (1 << led->ledNum));
}

void Led_ShiftLeft()
{
	for(int i = 0; i < 8; i++)
	{
		XGpio_DiscreteWrite(&GPIO_LED, CHANNEL_1, 1 << i);
		usleep(300000);
		XGpio_DiscreteWrite(&GPIO_LED, CHANNEL_1, 0 << i);
	}
}

void Led_ShiftRight()
{
	for(int i = 0; i < 8; i++)
	{
		XGpio_DiscreteWrite(&GPIO_LED, CHANNEL_1, 128 >> i);
		usleep(300000);
		XGpio_DiscreteWrite(&GPIO_LED, CHANNEL_1, (0 & (128 >> i)));
	}
}
