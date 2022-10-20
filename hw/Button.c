#include "Button.h"

XGpio GPIO_BUTTON;

void Button_Init()
{
	XGpio_Initialize(&GPIO_BUTTON, XPAR_AXI_GPIO_1_DEVICE_ID);
	XGpio_SetDataDirection(&GPIO_BUTTON, CHANNEL_1, 0xff); //input 1, output 0
}

void Button_MakeInst(buttonInst* button, int buttonNum)
{
	button->prevState = RELEASED;
	button->buttonNum = buttonNum;
}

int Button_GetState(buttonInst* button)
{
	int curState = XGpio_DiscreteRead(&GPIO_BUTTON, CHANNEL_1) & (1 << button->buttonNum);

	if((curState != RELEASED) && (button->prevState == RELEASED)){
		usleep(20000);
		button->prevState = PUSHED;

		return FALSE;
	}
	else if((curState == RELEASED) && (button->prevState != RELEASED)){
		usleep(20000);
		button->prevState = RELEASED;

		return TRUE;
	}
	return FALSE;
}
