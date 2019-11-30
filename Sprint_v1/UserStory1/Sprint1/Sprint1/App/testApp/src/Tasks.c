/*
 * Tasks.c
 *
 * Created: 11/30/2019 2:42:20 PM
 *  Author: Ammar Shahin
 */ 
#include "FreeRTOS.h"
#include "task.h"
#include "Typedefs.h"
#include "Tasks.h"
#include "Led.h"


TaskHandle_t Init_Task_Handle = FALSE;
TaskHandle_t Led_Task_Handle = FALSE;


void Init_Task(void)
{
	while(TRUE)
	{
		Led_Init(LED0);
		vTaskSuspend(Init_Task_Handle);
	}
}


void Led_Task(void)
{
	while(TRUE)
	{
		Led_Tog(LED0);
		vTaskDelay(1000);
	}
}
