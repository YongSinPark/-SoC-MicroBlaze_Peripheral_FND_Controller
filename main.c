/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include "main.h"

#define TICK_GENERATOR_DEV_BASE_ADDRESS 0x44A00000
#define TICK_DATA_REGISTER *(uint32_t*)TICK_GENERATOR_DEV_BASE_ADDRESS
XGpio GPIO_SWITCH;

int main()
{
    init_platform();

    int counter = 0;

    XGpio_Initialize(&GPIO_SWITCH, XPAR_AXI_GPIO_2_DEVICE_ID);
    XGpio_SetDataDirection(&GPIO_SWITCH, CHANNEL_1, 0xff);

    Led modeLed;
    Led upLed;
    Led downLed;
    Led blinkLed;

    buttonInst modeButton;
    buttonInst upButton;
    buttonInst downButton;

    Button_Init();
    Led_Init();

    Led_MakeInst(&modeLed, LED_0);
    Led_MakeInst(&upLed, LED_1);
    Led_MakeInst(&downLed, LED_2);
    Led_MakeInst(&blinkLed, LED_3);

    Button_MakeInst(&modeButton, BUTTON1);
    Button_MakeInst(&upButton, BUTTON2);
    Button_MakeInst(&downButton, BUTTON3);

    uint32_t prevCounterTick = 0;
//    int clear_state = 0;
//    int enable_state = 0;

    while(1)
    {

    	if((XGpio_DiscreteRead(&GPIO_SWITCH, CHANNEL_1) & (1 << 0)) == 1)
		{
			FND_CONTROL_REGISTER = 1 << 0;
			if((FND_CONTROL_REGISTER && 1 << 0) == 1) counter = -1;
		}

    	if((XGpio_DiscreteRead(&GPIO_SWITCH, CHANNEL_1) && (1 << 1)) == 1)
		{
    		FND_CONTROL_REGISTER = 1 << 1;
		}
    	else FND_CONTROL_REGISTER = 0 << 1;

    	if(TICK_DATA_REGISTER - prevCounterTick >= 100)
		{
    		prevCounterTick = TICK_DATA_REGISTER;
    		if(counter == 9999)
    		{
    			counter = 0;
    		}
    		else counter++;
            FND_VALUE_REGISTER = counter;
		}

    	if(Button_GetState(&modeButton) == 1)
    	{
			FND_CONTROL_REGISTER = 1 << 0;
			if(FND_CONTROL_REGISTER && (1 << 0) == 1)
			{
				counter = -1;

			}
//    		else if(!clear_state)
//    		{
//    			FND_CONTROL_REGISTER = 0 << 0;
//    		}
    	}
    	if(Button_GetState(&upButton) == 1)
    	{
    		FND_CONTROL_REGISTER = 1 << 1;
    	}
    }
    cleanup_platform();
    return 0;
}
