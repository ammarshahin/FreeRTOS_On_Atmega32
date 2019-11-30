/*
 * Tasks.h
 *
 * Created: 11/30/2019 2:42:06 PM
 *  Author: Ammar Shahin
 */ 


#ifndef TASKS_H_
#define TASKS_H_

#define  INIT_TASK_PRIORITY 4
#define  LCD_TASK_PRIORITY  3
#define  LEDS_TASK_PRIORITY 2


extern TaskHandle_t Init_Task_Handle;
extern TaskHandle_t Lcd_Task_Handle;
extern TaskHandle_t Led1_Task_Handle;
extern TaskHandle_t Led2_Task_Handle;
extern TaskHandle_t Led3_Task_Handle;


void Init_Task(void* pvParameters);

void Lcd_Task(void* pvParameters);

void Led1_Task(void* pvParameters);
void Led2_Task(void* pvParameters);
void Led3_Task(void* pvParameters);

#endif /* TASKS_H_ */