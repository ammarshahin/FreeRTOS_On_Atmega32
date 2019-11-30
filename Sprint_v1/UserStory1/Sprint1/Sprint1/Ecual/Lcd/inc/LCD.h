/*
 * LCD.h
 *
 *  Created on: 26-11-2019
 *      Author: Ammar Shahin
 */

#ifndef LCD_H_
#define LCD_H_

/************************************************************************/
/*                            Includes                                  */
/************************************************************************/
#include "Typedefs.h"
#include "LCD_cfg.h"

/************************************************************************/
/*                               Enums                                  */
/************************************************************************/
typedef enum {
	LCD_ERROR_OK					, 
	LCD_ERROR_NOT_OK				,
	LCD_ERROR_NOT_VALID				,
	LCD_ERROR_ALREADY_INITILIZED	,
}EnumLCDErrorState_type;

typedef enum {
	LCD_NOT_INITALIZED , 
	LCD_INITALIZED	   , 
}EnumLCDInitState_type;



/************************************************************************/
/*                            APIs Prototypes                           */
/************************************************************************/
/**
 * Function : LCD_Init
 * Description: this function is used to initialize the lcd
 * @return Status: of the initialization according to the Error handling Enum
 */
EnumLCDErrorState_type LCD_Init(void);

/**
 * Function : LCD_DisplayChar
 * Description: this function is to Display a char on the lcd
 * param Data: the character to be displayed
 * @return void                                                          
 */
void LCD_DisplayChar(char Data);

/**
 * Function : LCD_DisplayString
 * Description: this function is to Display a String of charters on the lcd
 * param DataString: A pointer to the String 
 * @return void                                                          
 */
void LCD_DisplayString(char* DataString);

/**
 * Function : LCD_DisplayNumber
 * Description: this function is to Display a Number on the lcd
 * param Number: the number to be Displayed the Max number to be enterd is 255 
 * @return void                                                          
 */
void LCD_DisplayNumber(uint8 Number);
//void LCD_DisplayNumber(uint16 Copy_u16Val);
/**
 * Function : LCD_GotoRowColumn
 * Description: this function is to Clear the LCD
 * @return void                        
 */
void LCD_Clear(void);

/**
 * Function : LCD_GotoRowColumn
 * Description: this function is to move the cursor of the lcd to a specific Location
 * param row: the row of the cursor should range is [0 to 1]
 * param col: the column of the cursor should range is [0 to 15]
 * @return void                                                          
 */
void LCD_GotoRowColumn(uint8 row , uint8 col);

#endif /* LCD_H_ */
