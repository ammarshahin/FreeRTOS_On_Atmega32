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
#define  LED_TASK_PRIORITY 2


/************************************************************************/
/*						Extern Global variables  				        */
/************************************************************************/
extern TaskHandle_t Init_Task_Handle;
extern TaskHandle_t Led_Task_Handle;

/************************************************************************/
/*					      OS Tasks Implementations				        */
/************************************************************************/
/**
 * Description: This Task is used to Init the System [Leds]
 * @param port : input parameter to the Task
 * Return : void
 */
void Init_Task(void* pvParameters);

/**
 * Description: This Task is used to Toggle the the Leds
 * @param port : input parameter to the Task
 * Return : void
 */
void Led_Task(void* pvParameters);


#endif /* TASKS_H_ */