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
#include "event_groups.h"
#include "Tasks.h"
#include "Led.h"
#include "LCD.h"
#include "SSD.h"
#include "pushButton.h"

/************************************************************************/
/*						Defines and private Macros 				        */
/************************************************************************/
#define  TASK_DELAY_DISPLAY_VALUE				100
#define  TASK_DELAY_PB0_VALUE					100 
#define  TASK_DELAY_PB1_VALUE					100

#define TASK_DELAY_CORRECT_ENTER_VALUE			2000
#define TASK_DELAY_INCORRECT_ENTER_VALUE		3000
#define TASK_DELAY_LONG_PRESSING_VALUE			1000

#define  ARRAY_SIZE								5
#define  TICK_TO_WAIT							100
#define	 NUMBER_TO_CHAR							48
#define  MAX_SSD_NUMBER							10

#define SHORT_PRESSING_BIT BIT0
#define LONG_PRESSING_BIT BIT1
#define LONG_LONG_PRESSING_BIT BIT2

/************************************************************************/
/*					      Global Variables						        */
/************************************************************************/
TaskHandle_t Init_Task_Handle	= FALSE;
TaskHandle_t Display_Handle		= FALSE;
TaskHandle_t PB0_Handle			= FALSE;
TaskHandle_t PB1_Handle			= FALSE;

EventGroupHandle_t xCreatedEventGroup = NULL;
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
	/* AtMaskCarriert to create the event group. */
    xCreatedEventGroup = xEventGroupCreate();

    /* Was the event group created successfully? */
    if( xCreatedEventGroup == NULL )
    {
        /* The event group was not created because there was insufficient
        FreeRTOS heap available. */
    }
    else
    {
        /* The event group was created. */
    }
	
	/* Suspend all other tasks before initializing */
	vTaskSuspend(Display_Handle);
	vTaskSuspend(PB0_Handle);
	
	/* initializing the Leds */
	Led_Init(LED0);
	Led_Init(LED1);
	Led_Init(LED2);
	
	/* initializing the pushButtons */
	pushButton_Init(PUSH_BUTTON0);
	
	/* initializing the Seven Segment */
	SSD_Init_BCD(ssd1);
	
	/* initializing the LCD */
	LCD_Init();

	/* Resume all other tasks before initializing */
	vTaskResume(Display_Handle);
	vTaskResume(PB0_Handle);

	/* Suspend the Init Task */
	vTaskSuspend(Init_Task_Handle);
	
	while(TRUE){}
}

/**
 * Description: This Task is used to Display String of Characters on the LCD
 * @param port : input parameter to the Task
 * Return : void
 */
void Display_Task(void* pvParameters)
{
	uint8 row = FIRST_ROW,col = FIRST_COLUMN;
	uint8 Number_Passward[ARRAY_SIZE]		= {1,2,3,3,2};
	uint8 Number_LCD[ARRAY_SIZE]			= {INITIAL_ZERO};
	uint8 Number_Index						= INITIAL_ZERO;
	uint8 Number_SSD						= INITIAL_ZERO;
	uint8 Success_Password					= FALSE;	
	EventBits_t uxBits						= FALSE;
	const TickType_t xTicksToWait			= TICK_TO_WAIT / portTICK_PERIOD_MS;

	while(TRUE)
	{
		/* Wait a maximum of 100ms for either bit 0 or bit 4 to be set within
		the event group.  Clear the bits before exiting. */
		uxBits = xEventGroupWaitBits(
				xCreatedEventGroup,		/* The event group being tested. */
				( SHORT_PRESSING_BIT | LONG_PRESSING_BIT | LONG_LONG_PRESSING_BIT ),	/* The bits within the event group to wait for. */
				pdTRUE,					/* BITs should be cleared before returning. */
				pdFALSE,			    /* Don't wait for both bits, either bit will do. */
				xTicksToWait );		    /* Wait a maximum of 100ms for either bit to be set. */
		
		if( ( uxBits & ( SHORT_PRESSING_BIT | LONG_PRESSING_BIT | LONG_LONG_PRESSING_BIT ) ) == ( SHORT_PRESSING_BIT | LONG_PRESSING_BIT | LONG_LONG_PRESSING_BIT ) )
		{
			for(Number_Index = INITIAL_ZERO ; Number_Index < ARRAY_SIZE ; Number_Index++)
			{
				if (Number_LCD[Number_Index] == Number_Passward[Number_Index])
				{
					Success_Password = TRUE;
				}
				else
				{
					Success_Password = FALSE;
					break;
				}
			}
			if (Success_Password)
			{
				LCD_GotoRowColumn(FIRST_ROW,FIRST_COLUMN);
				LCD_DisplayString("Correct Password!!!");
				Led_On(LED0);
				vTaskDelay(TASK_DELAY_CORRECT_ENTER_VALUE);
				Led_Off(LED0);
				LCD_Clear();
			}
			else
			{
				LCD_GotoRowColumn(FIRST_ROW,FIRST_COLUMN);
				LCD_DisplayString("Incorrect Password!!!");
				Led_On(LED1);

				vTaskDelay(TASK_DELAY_INCORRECT_ENTER_VALUE);
				Led_Off(LED1);
				LCD_Clear();
			}
			/* return to the Home curser */
			row = FIRST_ROW;
			col = FIRST_COLUMN;
			
			/* Clear the variable that holds the Bit masking */
			uxBits = xEventGroupClearBits(
			xCreatedEventGroup,		 /* The event group being updated. */
			LONG_LONG_PRESSING_BIT);
			uxBits = FALSE;					/* The bits being cleared. */
		}
		else if( ( uxBits & ( SHORT_PRESSING_BIT | LONG_PRESSING_BIT ) ) == ( SHORT_PRESSING_BIT | LONG_PRESSING_BIT ) )
		{
			/* Display the Number to the LCD */
			LCD_GotoRowColumn(row,col++);
			LCD_DisplayChar(Number_SSD+NUMBER_TO_CHAR);
			
			/* Set the Number to the Array to check later */
			Number_LCD[Number_Index] = Number_SSD;
			Number_Index++;
			
			/* Display the Number Zero to the SSD */
			Number_SSD = INITIAL_ZERO;
			SSD_Display_BCD(Number_SSD);
			
			/* Clear the Bits 0 and 1 */
			uxBits = xEventGroupClearBits(
			xCreatedEventGroup,			/* The event group being updated. */
			( SHORT_PRESSING_BIT | LONG_PRESSING_BIT ));			/* The bits being cleared. */
		}
		else if( ( uxBits & SHORT_PRESSING_BIT ) == SHORT_PRESSING_BIT)
		{
			/* xEventGroupWaitBits() returned because just BIT_0 was set. */
			Number_SSD++;
			if (Number_SSD < MAX_SSD_NUMBER)
			{
				SSD_Display_BCD(Number_SSD);
			}
			else
			{
				Number_SSD = INITIAL_ZERO;
				SSD_Display_BCD(Number_SSD);
			}
			/* Clear bit 0 and bit 4 in xEventGroup. */
			uxBits = xEventGroupClearBits(
			xCreatedEventGroup,  /* The event group being updated. */
			SHORT_PRESSING_BIT);/* The bits being cleared. */
		} 
		else
		{
			//Do Nothing
		}
		uxBits = FALSE;
		vTaskDelay(TASK_DELAY_DISPLAY_VALUE);
	}
}

/**
 * Description: This Task is used to Check for the Switch 0 
 * @param port : input parameter to the Task 
 * Return : void
 */
void PB0_Task(void* pvParameters)
{	
	uint8 MaskCarrier	= FALSE;
	
	while(TRUE)
	{
		if(Gpio_PinRead(PUSH_BUTTON0_PORT,PUSH_BUTTON0_PIN))
		{
			MaskCarrier |= SHORT_PRESSING_BIT;
			vTaskDelay(TASK_DELAY_LONG_PRESSING_VALUE);
			if(Gpio_PinRead(PUSH_BUTTON0_PORT,PUSH_BUTTON0_PIN))
			{
				MaskCarrier |= LONG_PRESSING_BIT;
				vTaskDelay(TASK_DELAY_LONG_PRESSING_VALUE);
				if(Gpio_PinRead(PUSH_BUTTON0_PORT,PUSH_BUTTON0_PIN))
				{
					MaskCarrier |= LONG_LONG_PRESSING_BIT;
				}
			}
			xEventGroupSetBits(
			xCreatedEventGroup,    /* The event group being updated. */
			MaskCarrier);/* The bits being set. */
			vTaskDelay(TASK_DELAY_LONG_PRESSING_VALUE);			
		}
		MaskCarrier = FALSE;
		vTaskDelay(TASK_DELAY_PB0_VALUE);
	}
}