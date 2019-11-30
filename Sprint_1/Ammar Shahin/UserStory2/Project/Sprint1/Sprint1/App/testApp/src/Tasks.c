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
#include "Tasks.h"
#include "Led.h"
#include "LCD.h"

/************************************************************************/
/*						Defines and private Macros 				        */
/************************************************************************/
#define  MAX_RandomStringindex_VALUE	10
#define  TASK_DELAY_LED1_VALUE			100
#define  TASK_DELAY_LED2_VALUE			500
#define  TASK_DELAY_LED3_VALUE			1000
#define  TASK_DELAY_LCD_VALUE			1500
/************************************************************************/
/*					      Global Variables						        */
/************************************************************************/
TaskHandle_t Init_Task_Handle = FALSE;
TaskHandle_t Lcd_Task_Handle  = FALSE;
TaskHandle_t Led1_Task_Handle = FALSE;
TaskHandle_t Led2_Task_Handle = FALSE;
TaskHandle_t Led3_Task_Handle = FALSE;


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
	while(TRUE)
	{
		Led_Init(LED0);
		Led_Init(LED1);
		Led_Init(LED2);
		LCD_Init();
		vTaskSuspend(Init_Task_Handle);
	}
}

/**
 * Description: This Task is used to Display String on the LCD
 * @param port : input parameter to the Task
 * Return : void
 */
void Lcd_Task(void* pvParameters)
{	
	uint8 RandomStringindex = FALSE;
	char arrRandomStrings[MAX_RandomStringindex_VALUE][MAX_RandomStringindex_VALUE] = {
		"Amr",
		"Ammar",
		"Yasen",
		"Mazen",
		"Osman",
		"Mayer",
		"Walled",
		"Mohamed",
		"Mostafa",
		"Mohamed",
	};
	while(TRUE)
	{
		LCD_Clear();
		LCD_GotoRowColumn(INITIAL_ZERO,INITIAL_ZERO);
		LCD_DisplayString(arrRandomStrings[RandomStringindex]);
		RandomStringindex++;
		if (RandomStringindex > MAX_RandomStringindex_VALUE)
		{
			RandomStringindex = FALSE;
		}
		vTaskDelay(TASK_DELAY_LCD_VALUE);
	}
}

/**
 * Description: This Task is used to Toggle the the Leds
 * @param port : input parameter to the Task
 * Return : void
 */
void Led1_Task(void* pvParameters)
{
	while(TRUE)
	{
		Led_Tog(LED0);
		vTaskDelay(TASK_DELAY_LED1_VALUE);
	}
}

/**
 * Description: This Task is used to Toggle the the Leds
 * @param port : input parameter to the Task
 * Return : void
 */
void Led2_Task(void* pvParameters)
{
	while(TRUE)
	{
		Led_Tog(LED1);
		vTaskDelay(TASK_DELAY_LED2_VALUE);
	}
}

/**
 * Description: This Task is used to Toggle the the Leds
 * @param port : input parameter to the Task
 * Return : void
 */
void Led3_Task(void* pvParameters)
{
	while(TRUE)
	{
		Led_Tog(LED2);
		vTaskDelay(TASK_DELAY_LED3_VALUE);
	}
}
