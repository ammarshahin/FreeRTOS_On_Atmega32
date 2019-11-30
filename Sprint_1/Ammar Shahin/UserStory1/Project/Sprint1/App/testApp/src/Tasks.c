/*
 * Tasks.c
 *
 * Created: 11/30/2019 2:42:20 PM
 *  Author: Ammar Shahin
 */ 

/************************************************************************/
/*								INCLUDES						        */
/************************************************************************/
#include "FreeRTOS.h"
#include "task.h"
#include "Typedefs.h"
#include "Tasks.h"
#include "Led.h"

/************************************************************************/
/*								Defines  						        */
/************************************************************************/
#define  TASK_DELAY_SYSTICK 1000

/************************************************************************/
/*					      Global Variables						        */
/************************************************************************/
TaskHandle_t Init_Task_Handle = FALSE;
TaskHandle_t Led_Task_Handle = FALSE;

/************************************************************************/
/*					      OS Tasks Implementations				        */
/************************************************************************/
/**
 * Description: This Task is used to Init the System [Leds]
 * @param port : input parameter to the Task
 * Return : void
 */
void Init_Task(void* pvParameters)
{
	while(TRUE)
	{
		Led_Init(LED0);
		vTaskSuspend(Init_Task_Handle);
	}
}

/**
 * Description: This Task is used to Toggle the the Leds
 * @param port : input parameter to the Task
 * Return : void
 */
void Led_Task(void* pvParameters)
{
	while(TRUE)
	{
		Led_Tog(LED0);
		vTaskDelay(TASK_DELAY_SYSTICK);
	}
}
