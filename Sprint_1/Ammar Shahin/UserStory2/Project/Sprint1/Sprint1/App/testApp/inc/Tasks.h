/*
 * Tasks.h
 *
 * Created: 11/30/2019 2:42:06 PM
 *  Author: Ammar Shahin
 */ 
#ifndef TASKS_H_
#define TASKS_H_

/************************************************************************/
/*								Defines  						        */
/************************************************************************/
#define  INIT_TASK_PRIORITY 4
#define  LCD_TASK_PRIORITY  3
#define  LEDS_TASK_PRIORITY 2


#define  INIT_TASK_STACK_SIZE 300
#define  LCD_TASK_STACK_SIZE  300
#define  LEDS_TASK_STACK_SIZE 50


/************************************************************************/
/*						Extern Global variables  				        */
/************************************************************************/
extern TaskHandle_t Init_Task_Handle;
extern TaskHandle_t Lcd_Task_Handle;
extern TaskHandle_t Led1_Task_Handle;
extern TaskHandle_t Led2_Task_Handle;
extern TaskHandle_t Led3_Task_Handle;



/************************************************************************/
/*					      OS Tasks Implementations				        */
/************************************************************************/
/**
 * Description: This Task is used to Init the System
 * @param port : input parameter to the Task
 * Return : void
 */
void Init_Task(void* pvParameters);

/**
 * Description: This Task is used to Display String on the LCD
 * @param port : input parameter to the Task
 * Return : void
 */
void Lcd_Task(void* pvParameters);

/**
 * Description: This Task is used to Toggle the the Leds
 * @param port : input parameter to the Task
 * Return : void
 */
void Led1_Task(void* pvParameters);

/**
 * Description: This Task is used to Toggle the the Leds
 * @param port : input parameter to the Task
 * Return : void
 */
void Led2_Task(void* pvParameters);

/**
 * Description: This Task is used to Toggle the the Leds
 * @param port : input parameter to the Task
 * Return : void
 */
void Led3_Task(void* pvParameters);

#endif /* TASKS_H_ */