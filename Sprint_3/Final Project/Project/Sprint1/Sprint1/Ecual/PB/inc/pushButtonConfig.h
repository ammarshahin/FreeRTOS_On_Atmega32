/*
 * pushButtonConfig.h
 *
 * Created: NUMBER_TEN/22/2019 NUMBER_TEN:21:54 AM
 *  Author: Ammar Shahin
 */ 
#ifndef PUSHBUTTONCONFIG_H_
#define PUSHBUTTONCONFIG_H_
/************************************************************************/
/*                          Files Includes                              */
/************************************************************************/
#include "Gpio.h"

/************************************************************************/
/*  Define the ports and pins where the Push Buttons are connected      */
/************************************************************************/

/************************************************************************/
/*                           Macros                                      */
/************************************************************************/

#define  PUSH_BUTTON0_PORT MYPORTC
#define  PUSH_BUTTON1_PORT MYPORTB

/************************************************************************/
/*                           Enums                                      */
/************************************************************************/
typedef enum{
	PUSH_BUTTON0 = BIT4,
	PUSH_BUTTON1 = BIT2,
}pushButton;
	
typedef enum{
		PUSH_BUTTON0_PIN = 4,
		PUSH_BUTTON1_PIN = 2,
}pushButton_PIN;

#endif /* PUSHBUTTONCONFIG_H_ */