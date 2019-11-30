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
#include "LCD.h"


TaskHandle_t Init_Task_Handle = FALSE;
TaskHandle_t Lcd_Task_Handle = FALSE;
TaskHandle_t Led1_Task_Handle = FALSE;
TaskHandle_t Led2_Task_Handle = FALSE;
TaskHandle_t Led3_Task_Handle = FALSE;


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

void Lcd_Task(void* pvParameters)
{	
	uint8 RandomStringindex = FALSE;
	char arrRandomStrings[10][10] = {
		"Ammar",
		"Walled",
		"Mohamed",
		"Yasen",
		"Mostafa",
		"Mohamed",
		"Amr",
		"Mazen",
		"Osman",
		"Mayer",
	};
	
	while(TRUE)
	{
		LCD_DisplayString(arrRandomStrings[RandomStringindex]);
		RandomStringindex++;
		vTaskDelay(1000);
	}
}


void Led1_Task(void* pvParameters)
{
	while(TRUE)
	{
		Led_Tog(LED0);
		vTaskDelay(100);
	}
}


void Led2_Task(void* pvParameters)
{
	while(TRUE)
	{
		Led_Tog(LED1);
		vTaskDelay(500);
	}
}

void Led3_Task(void* pvParameters)
{
	while(TRUE)
	{
		Led_Tog(LED2);
		vTaskDelay(1000);
	}
}
