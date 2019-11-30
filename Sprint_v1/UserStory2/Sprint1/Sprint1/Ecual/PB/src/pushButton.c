/*
 * pushButton.c
 *
 * Created: 10/22/2019 10:21:42 AM
 *  Author: Ammar Shahin
 */ 

/************************************************************************/
/*                            Includes                                  */
/************************************************************************/
#include "Typedefs.h"
#include "Gpio.h"
#include "pushButton.h"


/************************************************************************/
/*                         APIs Implementations                         */
/************************************************************************/
/**
 * Description: Function to Initiate the Push Button.
 * @param push_Button the number of the pushButton [PUSH_BUTTON0,PUSH_BUTTON1]
 */
void pushButton_Init()
{
	Gpio_PinDirection(PUSH_BUTTON0_PORT,PUSH_BUTTON0_PIN,SET_IN);
	Gpio_PinDirection(PUSH_BUTTON1_PORT,PUSH_BUTTON1_PIN,SET_IN);
}

/**
 * Description: Function to get the status of the Push button(Value).
 * @param push_Button the number of the push button [PUSH_BUTTON0,PUSH_BUTTON1]
 * @return the value(state) of the push button
 */
uint8 pushButton_Get_Status(pushButton push_Button)
{
	uint8 PB_FinalState = INITIAL_ZERO;
	static uint8 PB0_CheckCounter = INITIAL_ZERO, PB1_CheckCounter = INITIAL_ZERO;
	static uint8 PB0_State0 = INITIAL_ZERO, PB0_State1 = INITIAL_ZERO;
	static uint8 PB1_State0 = INITIAL_ZERO, PB1_State1 = INITIAL_ZERO;
	switch(push_Button)
	{
		case PUSH_BUTTON0 :
			switch(PB0_CheckCounter)
			{
				case INITIAL_ZERO:
					PB0_State0 = Gpio_PinRead(PUSH_BUTTON0_PORT,PUSH_BUTTON0_PIN);
					PB0_CheckCounter++;
					break;
				case INITIAL_ONE:
					PB0_State1 = Gpio_PinRead(PUSH_BUTTON0_PORT,PUSH_BUTTON0_PIN);
					if(PB0_State0 == PB0_State1)
					{
						PB_FinalState = PB0_State1;
						PB0_State0 = INITIAL_ZERO;
						PB0_State1 = INITIAL_ZERO;
					}else
					{
						PB_FinalState = INITIAL_ZERO;
					}
					PB0_CheckCounter = INITIAL_ZERO;
					break;
				default:
					break;
			}
			break;
		case PUSH_BUTTON1 :
			switch(PB1_CheckCounter)
			{
				case INITIAL_ZERO:
				PB1_State0 = Gpio_PinRead(PUSH_BUTTON1_PORT,PUSH_BUTTON1_PIN);
				PB1_CheckCounter++;
				//return PB_FinalState;
				break;
				case INITIAL_ONE:
				PB1_State1 = Gpio_PinRead(PUSH_BUTTON1_PORT,PUSH_BUTTON1_PIN);
				if(PB1_State0 == PB1_State1)
				{
					PB_FinalState = PB1_State1;
					PB1_State0 = INITIAL_ZERO;
					PB1_State1 = INITIAL_ZERO;
				}
				else
				{
					// Do Nothing
				}
				PB1_CheckCounter = INITIAL_ZERO;
				break;
				default:
				break;
			}
			break;
		default:
			break;
	}
	return PB_FinalState;
}