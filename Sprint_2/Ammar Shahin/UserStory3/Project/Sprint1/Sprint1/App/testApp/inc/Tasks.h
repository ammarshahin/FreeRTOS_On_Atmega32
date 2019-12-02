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
#define  INIT_TASK_PRIORITY			4
#define  Display_TASK_PRIORITY		1
#define  PB0_TASK_PRIORITY			3

#define  TIME_OUT				(TickType_t) 0

#define  INIT_TASK_STACK_SIZE		100
#define  Display_TASK_STACK_SIZE	400
#define  PB0_TASK_STACK_SIZE		400


/************************************************************************/
/*						Extern Global variables  				        */
/************************************************************************/
extern TaskHandle_t Init_Task_Handle;
extern TaskHandle_t Display_Handle;
extern TaskHandle_t PB0_Handle;

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
 * Description: This Task is used to Display String of Characters on the LCD
 * @param port : input parameter to the Task
 * Return : void
 */
void Display_Task(void* pvParameters);

/**
 * Description: This Task is used to Display String of numbers on the LCD
 * @param port : input parameter to the Task
 * Return : void
 */
void PB0_Task(void* pvParameters);

#endif /* TASKS_H_ */