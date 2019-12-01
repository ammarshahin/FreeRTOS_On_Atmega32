/*
 * LCD.c
 *
 *  Created on: 26-11-2019
 *  Author: Ammar Shahin
 */
/************************************************************************/
/*                            Includes                                  */
/************************************************************************/
#include "Typedefs.h"
#include "Gpio.h"
#include "LCD.h"

/************************************************************************/
/*                            Command Macros                            */
/************************************************************************/
#define LCD_ClearScreen        0x01				// CLEAR THE SCREEN
#define LCD_CursorHome         0x02				// GET CURSOR AT THE TOP LEFT CORNER
#define LCD_IncOnShiOff        0x06		        // ENTRY MODE SET (THE CURSOR WILL MOVE INCREMENTALLY WITH NO SHIFT)
#define LCD_IncOnShiOn		   0x07             // ENTRY MODE SET (THE CURSOR WILL MOVE INCREMENTALLY WITH SHIFTING)
#define LCD_DecOnShiOff        0x04             // ENTRY MODE SET (THE CURSOR WILL MOVE DECREMENTALLY WITH NO SHIFT)
#define LCD_DisOnCurOnBliOff   0x0E				// GET THE DISPLAY ON, CURSOR ON AND THE BLINKING FOR THE CURSOR OFF (TURNING ON VISIABLE UNDERLINE CURSOR)
#define LCD_DisOnCurOnBliOn    0x0F				// GET THE DISPLAY ON, CURSOR ON AND THE BLINKING ON (TURNING ON VISIABLE BLINKING CURSOR)
#define LCD_DisOnCurOffBliOff  0x0C				// GET DISPLAY ON, CURSOR OFF, BLINKING OFF (MAKE THE CURSOR INVISABLE)
#define LCD_BlankDis           0x08             // GET DISPLAY OFF, CURSOR OFF, BLINKING OFF
#define LCD_CurL               0x10				// MOVE CURSOR ONE CHARACTER LEFT
#define LCD_CurR               0x14             // MOVE CURSOR ONE CHARACTER RIGHT
#define LCD_ScrR		  	   0x1E				// SCROLL ALL CHARACTER RIGH
#define LCD_ScrL			   0x18				// SCROLL ALL CHARACTER LEFT
#define LCD_Set8Bit2Lin        0x38             // FUN SET 8 BIT MODE, 2 LINES, 5x7
#define LCD_Set8Bit1Lin		   0x30				//FUN SET 8 BIT MODE, 1 LINE, 5x7
#define LCD_Set4Bit2Lin		   0x28				//FUN SET 4 BIT MODE, 2 LINES, 5x7
#define LCD_Set4Bit1lin        0x20				//FUN SET 4 BIT MODE, 1 LINE, 5x7

/************************************************************************/
/*                           Private Macros                             */
/************************************************************************/
#define NUMBER_TO_CHAR_FACTOR	48
#define NUMBER_HUNDRED			100
#define NUMBER_TEN				10

#define GOTO_ROW_COL_MASK1 0x80
#define GOTO_ROW_COL_MASK2 0x5

#define COMMON_DELAY_US 2
/************************************************************************/
/*                       Static(Private) variables                      */
/************************************************************************/
static EnumLCDInitState_type InitState = LCD_NOT_INITALIZED;


/************************************************************************/
/*               Static(Private) Functions Implementations              */
/************************************************************************/
/**
 * Function : LCD_SendCommand
 * Description: this function is used to Send Command to the lcd
 * Param Command: the Command to be sent
 * @return void
 */
static void LCD_SendCommand(uint8 Command)
{
	Gpio_PinWrite(LCD_PORT,LCD_RS, LOW);
	Gpio_PinWrite(LCD_PORT,LCD_RW, LOW);
		
	Gpio_PinWrite(LCD_PORT,BIT7,((Command>>7)&1) );
	Gpio_PinWrite(LCD_PORT,BIT6,((Command>>6)&1) );
	Gpio_PinWrite(LCD_PORT,BIT5,((Command>>5)&1) );
	Gpio_PinWrite(LCD_PORT,BIT4,((Command>>4)&1) );
	Gpio_PinWrite(LCD_PORT,LCD_EN,HIGH);
	
	

	Gpio_PinWrite(LCD_PORT,LCD_EN,LOW);
	
	Gpio_PinWrite(LCD_PORT,BIT7,((Command>>3)&1) );
	Gpio_PinWrite(LCD_PORT,BIT6,((Command>>2)&1) );
	Gpio_PinWrite(LCD_PORT,BIT5,((Command>>1)&1) );
	Gpio_PinWrite(LCD_PORT,BIT4,((Command>>0)&1) );
	Gpio_PinWrite(LCD_PORT,LCD_EN,HIGH);
	
	
	
	Gpio_PinWrite(LCD_PORT,LCD_EN,LOW);
}

/************************************************************************/
/*                          APIs Implementations                        */
/************************************************************************/
/**
 * Function : LCD_Init
 * Description: this function is used to initialize the lcd
 * @return Status: of the initialization according to the Error handling Enum
 */
EnumLCDErrorState_type LCD_Init(void)
{
	EnumLCDErrorState_type API_State = LCD_ERROR_OK;

	if( LCD_NOT_INITALIZED == InitState)
	{
		Gpio_PortDirection(LCD_PORT,SET_OUT);
		LCD_SendCommand(LCD_CursorHome);
		
		LCD_SendCommand(LCD_Set4Bit2Lin);
		
		LCD_SendCommand(LCD_DisOnCurOnBliOff);
		
		LCD_SendCommand(LCD_IncOnShiOff);
		InitState = LCD_INITALIZED;
	}
	else
	{
		API_State = LCD_ERROR_ALREADY_INITILIZED;
	}
	return API_State;
}

/**
 * Function : LCD_DisplayChar
 * Description: this function is to Display a char on the lcd
 * param Data: the character to be displayed
 * @return void                                                          
 */
void LCD_DisplayChar(char Data)
{
	if(InitState == LCD_INITALIZED)
	{
		Gpio_PinWrite(LCD_PORT,LCD_RS, HIGH);
		Gpio_PinWrite(LCD_PORT,LCD_RW, LOW);

		/* Send the Second Part of the Char */
		Gpio_PinWrite(LCD_PORT,BIT7,((Data>>7)&1));
		Gpio_PinWrite(LCD_PORT,BIT6,((Data>>6)&1));
		Gpio_PinWrite(LCD_PORT,BIT5,((Data>>5)&1));
		Gpio_PinWrite(LCD_PORT,BIT4,((Data>>4)&1));
			
		Gpio_PinWrite(LCD_PORT,LCD_EN, HIGH);
			
		/* Send the Second Part of the Char */
		Gpio_PinWrite(LCD_PORT,LCD_EN, LOW);

		// Write the Low 4-Bit
		Gpio_PinWrite(LCD_PORT,BIT7,((Data>>3)&1));
		Gpio_PinWrite(LCD_PORT,BIT6,((Data>>2)&1));
		Gpio_PinWrite(LCD_PORT,BIT5,((Data>>1)&1));
		Gpio_PinWrite(LCD_PORT,BIT4,((Data>>0)&1));

		// Send Pules
		Gpio_PinWrite(LCD_PORT,LCD_EN, HIGH);
		
		Gpio_PinWrite(LCD_PORT,LCD_EN, LOW);
	}
	else
	{
		// Do Nothing
	}
}

/**
 * Function : LCD_DisplayString
 * Description: this function is to Display a String of charters on the lcd
 * param DataString: A pointer to the String 
 * @return void                                                          
 */
void LCD_DisplayString(char* DataString)
{
	uint8 index = INITIAL_ZERO;
	if (InitState == LCD_INITALIZED)
	{
		while(DataString[index])
		{
			LCD_DisplayChar(DataString[index]);
			index++;
		}
	}
	else
	{
		//Do Nothing
	}
}

/**
 * Function : LCD_DisplayNumber
 * Description: this function is to Display a Number on the lcd
 * param Number: the number to be Displayed the Max number to be enterd is 255 
 * @return void                                                          
 */
void LCD_DisplayNumber(uint8 Number){

		uint8 tempVar;
		if ( Number >= NUMBER_HUNDRED )
		{
			tempVar =  Number / NUMBER_HUNDRED;
			LCD_DisplayChar( tempVar + NUMBER_TO_CHAR_FACTOR );
			
			Number = Number - (tempVar * NUMBER_HUNDRED);
			tempVar = Number / NUMBER_TEN;
			LCD_DisplayChar( tempVar + NUMBER_TO_CHAR_FACTOR );
			
			tempVar = Number - (tempVar * NUMBER_TEN);
			LCD_DisplayChar(tempVar+NUMBER_TO_CHAR_FACTOR);
		}
		else if (Number >= NUMBER_TEN)
		{
			tempVar = Number / NUMBER_TEN;
			LCD_DisplayChar(tempVar+NUMBER_TO_CHAR_FACTOR);
			tempVar = Number - (tempVar * NUMBER_TEN);
			LCD_DisplayChar(tempVar+NUMBER_TO_CHAR_FACTOR);
		}
		else
		{
			LCD_DisplayChar(Number+NUMBER_TO_CHAR_FACTOR);
		}
}

/**
 * Function : LCD_GotoRowColumn
 * Description: this function is to Clear the LCD
 * @return void                        
 */
void LCD_Clear(void)
{
	LCD_SendCommand(LCD_ClearScreen);
}

/**
 * Function : LCD_GotoRowColumn
 * Description: this function is to move the cursor of the lcd to a specific Location
 * param row: the row of the cursor should range is [0 to 1]
 * param col: the column of the cursor should range is [0 to 15]
 * @return void                                                          
 */
void LCD_GotoRowColumn(uint8 row , uint8 col)
{
	LCD_SendCommand( (GOTO_ROW_COL_MASK1) | ( col + (GOTO_ROW_COL_MASK2 * row ) ) );
}