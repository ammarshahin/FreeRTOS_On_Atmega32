/************************************************************************/
/*								INCLUDES						        */
/************************************************************************/
#include "Typedefs.h"
#include "FreeRTOS.h"
#include "task.h"
#include "Tasks.h"



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
