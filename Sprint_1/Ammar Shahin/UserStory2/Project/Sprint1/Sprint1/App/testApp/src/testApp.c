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


/************************************************************************/
/*				      Main Function Implementation			            */
/************************************************************************/
int main(void)
{
	BaseType_t xReturned = FALSE;

	xReturned = xTaskCreate(Init_Task, 
	"Initialization Task",
	INIT_TASK_STACK_SIZE, 
	NULL, 
	INIT_TASK_PRIORITY,
	&Init_Task_Handle
	);
	
	if( xReturned != pdPASS )
	{
		 // Error Handling Code
	}
	
	xReturned = xTaskCreate(Lcd_Task,
	"Lcd",
	LCD_TASK_STACK_SIZE,
	NULL,
	LCD_TASK_PRIORITY,
	&Lcd_Task_Handle
	);
	
	if( xReturned != pdPASS )
	{
		// Error Handling Code
	}
	
	xReturned = xTaskCreate(Led1_Task,
	"Led Plinking Task",
	LEDS_TASK_STACK_SIZE,
	NULL,
	LEDS_TASK_PRIORITY,
	&Led1_Task_Handle
	);
	
	if( xReturned != pdPASS )
	{
		// Error Handling Code
	}
	
	xReturned = xTaskCreate(Led2_Task,
	"Led Plinking Task",
	LEDS_TASK_STACK_SIZE,
	NULL,
	LEDS_TASK_PRIORITY,
	&Led2_Task_Handle
	);
	
	if( xReturned != pdPASS )
	{
		// Error Handling Code
	}
	
	xReturned = xTaskCreate(Led3_Task,
	"Led Plinking Task",
	LEDS_TASK_STACK_SIZE,
	NULL,
	LEDS_TASK_PRIORITY,
	&Led3_Task_Handle
	);
	
	if( xReturned != pdPASS )
	{
		// Error Handling Code
	}
	
	/* Start Scheduler */
	vTaskStartScheduler();
}
