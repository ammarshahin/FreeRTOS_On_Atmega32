/*
 * Tasks.c
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
#include "semphr.h"
#include "Tasks.h"
#include "Led.h"
#include "LCD.h"


/************************************************************************/
/*						Defines and private Macros 				        */
/************************************************************************/
#define  MAX_RandomStringindex_VALUE	10
#define  TASK_DELAY_TASKA_VALUE			500 
#define  TASK_DELAY_TASKB_VALUE			1000


/************************************************************************/
/*					      Global Variables						        */
/************************************************************************/
TaskHandle_t Init_Task_Handle	= FALSE;
TaskHandle_t TaskA_Handle		= FALSE;
TaskHandle_t TaskB_Handle		= FALSE;



SemaphoreHandle_t Semaphore_Handler = NULL;

/************************************************************************/
/*					      OS Tasks Implementations				        */
/************************************************************************/
/**
 * Description: This Task is used to Init the System
 * @param port : input parameter to the Task
 * Return : void
 */
void Init_Task(void* pvParameters)
{
	vTaskSuspend(TaskA_Handle);
	vTaskSuspend(TaskB_Handle);
	/* Create a mutex type semaphore. */
   Semaphore_Handler = xSemaphoreCreateMutex();

   if( Semaphore_Handler == NULL )
   {
       /* The semaphore wasn't created successfully Error handling should by executed. */
   }
   
	while(TRUE)
	{
	Led_Init(LED0);
	Led_Init(LED1);
	LCD_Init();
	vTaskResume(TaskA_Handle);
	vTaskResume(TaskB_Handle);
	vTaskSuspend(Init_Task_Handle);
	}
}

/**
 * Description: This Task is used to Display String of Characters on the LCD
 * @param port : input parameter to the Task
 * Return : void
 */
void TaskA(void* pvParameters)
{	
	uint8 RandomStringindex = INITIAL_ZERO,SemFlag = FALSE;
	char arrRandomStrings[MAX_RandomStringindex_VALUE][MAX_RandomStringindex_VALUE] = {
		"Amr    ",
		"Ammar  ",
		"Yasen  ",
		"Mazen  ",
		"Osman  ",
		"Mayer  ",
		"Walled ",
		"Mohamed",
		"Mostafa",
		"Diana  ",
	};
	while(TRUE)
	{	
		if( Semaphore_Handler != NULL )
		{
			/* See if we can obtain the semaphore.  If the semaphore is not
			available wait 10 ticks to see if it becomes free. */
			if( SemFlag || (xSemaphoreTake( Semaphore_Handler, TIME_OUT ) == pdTRUE) )
			{
				Led_On(LED0);
				/* We were able to obtain the semaphore and can now access the
				shared resource. */
				SemFlag = pdTRUE;
				LCD_GotoRowColumn(FIRST_ROW,FIRST_COLUMN);
				LCD_DisplayString(arrRandomStrings[RandomStringindex]);
				RandomStringindex++;
	
				if (RandomStringindex > MAX_RandomStringindex_VALUE)
				{
					RandomStringindex = FALSE;
					SemFlag = pdFALSE;
					LCD_Clear();
					Led_Off(LED0);
					/* We have finished accessing the shared resource.  Release the
					semaphore. */
					xSemaphoreGive( Semaphore_Handler );
					vTaskDelay(TASK_DELAY_TASKA_VALUE);
				}
				else
				{
					// Do Nothing
				}
			}
			vTaskDelay(TASK_DELAY_TASKA_VALUE);
		}
	}
}




/**
 * Description: This Task is used to Display String of numbers on the LCD
 * @param port : input parameter to the Task
 * Return : void
 */
void TaskB(void* pvParameters)
{	
	uint8 RandomStringindex = INITIAL_ZERO,SemFlag = FALSE;
	char arrRandomStrings[MAX_RandomStringindex_VALUE][MAX_RandomStringindex_VALUE] = {
		"ONE  ",
		"TOW  ",
		"THREE",
		"FOUR ",
		"FIFE ",
		"SIX  ",
		"SEVEN",
		"NINE ",
		"TEN  ",
	};
	
	while(TRUE)
	{	
		if( Semaphore_Handler != NULL )
		{
			/* See if we can obtain the semaphore.  If the semaphore is not
			available wait 10 ticks to see if it becomes free. */
			if( SemFlag || (xSemaphoreTake( Semaphore_Handler, TIME_OUT ) == pdTRUE) )
			{
				Led_On(LED1);
				/* We were able to obtain the semaphore and can now access the
				shared resource. */
				SemFlag = pdTRUE;
				LCD_GotoRowColumn(FIRST_ROW,FIRST_COLUMN);
				LCD_DisplayString(arrRandomStrings[RandomStringindex]);
				RandomStringindex++;
	
				if (RandomStringindex > MAX_RandomStringindex_VALUE)
				{
					RandomStringindex = FALSE;
					SemFlag = pdFALSE;
					LCD_Clear();
					Led_Off(LED1);
					/* We have finished accessing the shared resource.  Release the
					semaphore. */
					xSemaphoreGive( Semaphore_Handler );
					vTaskDelay(TASK_DELAY_TASKB_VALUE);
				}
				else
				{
					// Do Nothing
				}
			}
			vTaskDelay(TASK_DELAY_TASKB_VALUE);
		}
	}
}
