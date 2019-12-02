/*
 * Keypad.h
 *
 * Created: 12/2/2019 3:53:03 PM
 *  Author: Ammar Shahin
 */
#ifndef KEYPAD_H_
#define KEYPAD_H_

/************************************************************************/
/*								INCLUDES						        */
/************************************************************************/
#include "Typedefs.h"
#include "Gpio.h"

/************************************************************************/
/*						Defines and Macros		 				        */
/************************************************************************/
/* THE DEFAULT KEY FOR NOT PRESSING A KEY */
#define DEFAULT_KEY '#'

#define No_Of_Row 	3
#define No_Of_Col 	3
#define KEYPAD_PORT MYPORTC


#define R1 BIT2
#define R2 BIT3
#define R3 BIT4
#define C1 BIT5
#define C2 BIT6
#define C3 BIT7



/************************************************************************/
/*                               Enums                                  */
/************************************************************************/
typedef enum {
	Keypad_InitOK, 
	Keypad_NotInit
	} EnumKeypadInitStat_t;


typedef enum {
	E_Keypad_OK, 
	E_Keypad_NOK, 
	E_Keypad_NotInit 
	} EnumKeypadError_t;


/************************************************************************/
/*                            APIs Prototypes                           */
/************************************************************************/
/**
 * Function : KEYPAD_Init
 * Description: this function is used to initialize the Keypad
 * @return Status: of the initialization according to the Error handling Enum
 */
EnumKeypadError_t Keypad_Init(void);

/**
 * Function : KEYPAD_GetPressedKey
 * Description: this function is used to get the pressed key on the Keypad
 * Param KeyValue is an Input parameter to the Function to set the value in it 
 * @return Status: of the initialization according to the Error handling Enum
 */
EnumKeypadError_t Keypad_GetPressedKey(uint8 * KeyValue);



#endif /* KEYPAD_H_ */