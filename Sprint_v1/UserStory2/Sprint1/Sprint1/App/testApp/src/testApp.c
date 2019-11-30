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
	500, 
	NULL, 
	INIT_TASK_PRIORITY,
	&Init_Task_Handle
	);
	
	if( xReturned != pdPASS )
	{
		 // Error Handling Code
	}
	
	xReturned = xTaskCreate(Lcd_Task,
	"Lcd Displaying Task",
	500,
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
	configMINIMAL_STACK_SIZE,
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
	configMINIMAL_STACK_SIZE,
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
	configMINIMAL_STACK_SIZE,
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
