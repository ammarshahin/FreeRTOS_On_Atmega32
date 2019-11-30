/*
 * testApp.c
 *
 * Created: 11/30/2019 2:42:20 PM
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
	configMINIMAL_STACK_SIZE, 
	NULL, 
	INIT_TASK_PRIORITY,
	&Init_Task_Handle
	);
	
	if( xReturned != pdPASS )
	{
		 // Error Handling Code
	}
	
	xReturned = xTaskCreate(Led_Task,
	"Led Plinking Task",
	configMINIMAL_STACK_SIZE,
	NULL,
	LED_TASK_PRIORITY,
	&Led_Task_Handle
	);
	
	if( xReturned != pdPASS )
	{
		// Error Handling Code
	}
	
	/* Start Scheduler */
	vTaskStartScheduler();
}
