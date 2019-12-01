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

/******** Init Task ******************/
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

/******** LCD_DisplayTask ******************/
	xReturned = xTaskCreate(Display_Task,
	"Display_Task",
	Display_TASK_STACK_SIZE,
	NULL,
	Display_TASK_PRIORITY,
	&Display_Handle
	);
	
	if( xReturned != pdPASS )
	{
		// Error Handling Code
	}
	
/******** TaskB ******************/
	xReturned = xTaskCreate(PB0_Task,
	"PB0_Task",
	PB0_TASK_STACK_SIZE,
	NULL,
	PB0_TASK_PRIORITY,
	&PB0_Handle
	);
	
	if( xReturned != pdPASS )
	{
		// Error Handling Code
	}
	
/******** TaskB ******************/
	xReturned = xTaskCreate(PB1_Task,
	"PB1_Task",
	PB1_TASK_STACK_SIZE,
	NULL,
	PB1_TASK_PRIORITY,
	&PB1_Handle
	);
	
	if( xReturned != pdPASS )
	{
		// Error Handling Code
	}
		
/******* Start Scheduler *********/
	vTaskStartScheduler();
}
