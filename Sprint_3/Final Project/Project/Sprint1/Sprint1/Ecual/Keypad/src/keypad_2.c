/*
 * Keypad.c
 *
 * Created: 4/3/2014 3:02:35 PM
 *  Author: Mohamed Tarek
 */
#include "Typedefs.h"
#include "keypad_2.h"

uint8 KeyPad_getPressedKey(void)
{
	static uint8 KPad_Entry=0;
	uint8 key = INITIAL_ZERO;
	uint8 col,row;

	for(col=0;col<N_col;col++) /* loop for columns */
	{
		/* 
			* each time only one of the column pins will be output and 
			* the rest will be input pins include the row pins 
			*/ 
		KEYPAD_PORT_DIR = (0b00100000<<col); 
			
		/* 
			* clear the output pin column in this trace and enable the internal 
			* pull up resistors for the rows pins
			*/ 
		KEYPAD_PORT_OUT = (~(0b00100000<<col)); 
		for(row=0;row<N_row;row++) /* loop for rows */
		{
			if(BIT_IS_CLEAR(KEYPAD_PORT_IN,(row+2))) /* if the switch is press in this row */
			{
				KPad_Entry++;
				if(KPad_Entry == 50)  // debouning
				{                                    /* if the switch is press in this row */
					key = ((row * N_col)+col+1);
					KPad_Entry = 0 ;
				}
			}
		}
	}
	return key;
}
