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

/******** TaskA ******************/
	xReturned = xTaskCreate(TaskA,
	"Task A",
	TASKA_TASK_STACK_SIZE,
	NULL,
	TASKA_TASK_PRIORITY,
	&TaskA_Handle
	);
	
	if( xReturned != pdPASS )
	{
		// Error Handling Code
	}
	
/******** TaskB ******************/
	xReturned = xTaskCreate(TaskB,
	"Task B",
	TASKB_TASK_STACK_SIZE,
	NULL,
	TASKB_TASK_PRIORITY,
	&TaskB_Handle
	);
	
	if( xReturned != pdPASS )
	{
		// Error Handling Code
	}
	
/******* Start Scheduler *********/
	vTaskStartScheduler();
}
