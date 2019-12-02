/*
 * testApp.c
 *
 * Created: 11/30/2019 2:42:06 PM
 *  Author: Ammar Shahin
 */ 

/************************************************************************/
/*								INCLUDES						        */
/************************************************************************/
#include "Typedefs.h"
#include "FreeRTOS.h"
#include "task.h"
#include "Tasks.h"
#include "Keypad_2.h"
#include "Led.h"

/************************************************************************/
/*				      Main Function Implementation			            */
/************************************************************************/
int main(void)
{
	uint8 PressedKey;
	//Keypad_Init();
	
	Led_Init(LED0);
	Led_Init(LED1);
	Led_Init(LED2);
	
	
	Led_Off(LED0);
	Led_Off(LED1);
	Led_Off(LED2);
	LCD_Init();
	while(TRUE)
	{
		PressedKey = KeyPad_getPressedKey();
		
		if ( (PressedKey != 0)  )
		{
			switch(PressedKey)
			{
				case 1:
					Led_Tog(LED0);
					break;
				case 2:
					Led_Tog(LED1);
					break;
				case 3:
					Led_Tog(LED2);
					break;
				default:
					break;
			}
			PressedKey = INITIAL_ZERO;
		}
		else
		{

		}
	}
	
	//BaseType_t xReturned = FALSE;
//
///******** Init Task ******************/
	//xReturned = xTaskCreate(Init_Task, 
	//"Initialization Task",
	//INIT_TASK_STACK_SIZE, 
	//NULL, 
	//INIT_TASK_PRIORITY,
	//&Init_Task_Handle
	//);
	//
	//if( xReturned != pdPASS )
	//{
		 //// Error Handling Code
	//}
//
///******** LCD_DisplayTask ******************/
	//xReturned = xTaskCreate(Display_Task,
	//"Display_Task",
	//Display_TASK_STACK_SIZE,
	//NULL,
	//Display_TASK_PRIORITY,
	//&Display_Handle
	//);
	//
	//if( xReturned != pdPASS )
	//{
		//// Error Handling Code
	//}
	//
///******** TaskPB0 ******************/
	//xReturned = xTaskCreate(PB0_Task,
	//"PB0_Task",
	//PB0_TASK_STACK_SIZE,
	//NULL,
	//PB0_TASK_PRIORITY,
	//&PB0_Handle
	//);
	//
	//if( xReturned != pdPASS )
	//{
		//// Error Handling Code
	//}
//
///******* Start Scheduler *********/
	//vTaskStartScheduler();
}
