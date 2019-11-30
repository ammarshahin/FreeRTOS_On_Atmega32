/*
 * Tasks.h
 *
 * Created: 11/30/2019 2:42:06 PM
 *  Author: Ammar Shahin
 */ 


#ifndef TASKS_H_
#define TASKS_H_

#define  INIT_TASK_PRIORITY 4
#define  LED_TASK_PRIORITY 2

extern TaskHandle_t Init_Task_Handle;
extern TaskHandle_t Led_Task_Handle;


void Init_Task(void);

void Led_Task(void);

#endif /* TASKS_H_ */