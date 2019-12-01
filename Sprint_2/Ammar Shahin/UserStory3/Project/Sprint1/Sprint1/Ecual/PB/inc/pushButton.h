/*
 * pushButton.h
 *
 * Created: NUMBER_TEN/22/2019 NUMBER_TEN:22:07 AM
 *  Author: Ammar Shahin
 */ 


#ifndef PUSHBUTTON_H_
#define PUSHBUTTON_H_


/************************************************************************/
/*                            Files Inculded                            */
/************************************************************************/
#include "pushButtonConfig.h"

/************************************************************************/
/*				            Functions Prototypes                         */
/************************************************************************/
/**
 * Description: Function to Initiate the Push Button.
 * @param push_Button the number of the pushButton [PUSH_BUTTON0,PUSH_BUTTON1]
 */
void pushButton_Init();


/**
 * Description: Function to get the status of the Push button(Value).
 * @param push_Button the number of the push button [PUSH_BUTTON0,PUSH_BUTTON1]
 * @return the value(state) of the push button
 */
uint8 pushButton_Get_Status(pushButton push_Button);

#endif /* PUSHBUTTON_H_ */