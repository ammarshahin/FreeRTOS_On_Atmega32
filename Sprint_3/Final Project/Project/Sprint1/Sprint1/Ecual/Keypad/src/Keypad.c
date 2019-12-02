/*
 * Keypad.c
 *
 * Created: 12/2/2019 3:52:29 PM
 *  Author: Ammar Shahin
 */

/************************************************************************/
/*								INCLUDES						        */
/************************************************************************/
#include "Keypad.h"
#include "Gpio.h"


/************************************************************************/
/*						Defines and private Macros 				        */
/************************************************************************/



/************************************************************************/
/*					     Global Private Variables				        */
/************************************************************************/
uint8 Key_Table [No_Of_Row][No_Of_Col] = {{'1' , '2' , '3' },

										  {'4' , '5' , '6' },

									      {'7' , '8' , '9' }};


static EnumKeypadInitStat_t InitAPI_State = Keypad_NotInit;




/************************************************************************/
/*					        API's Implementations				        */
/************************************************************************/
/**
 * Function : Keypad_Init
 * Description: this function is used to initialize the Keypad
 * @return Status: of the initialization according to the Error handling Enum
 */
EnumKeypadError_t Keypad_Init(void)
{

	static EnumKeypadError_t API_State = E_Keypad_OK;

	if (Keypad_NotInit == InitAPI_State)
	{
		
		Gpio_PinDirection(KEYPAD_PORT,C1,SET_OUT);
		Gpio_PinDirection(KEYPAD_PORT,C2,SET_OUT);
		Gpio_PinDirection(KEYPAD_PORT,C3,SET_OUT);
		
		Gpio_PinWrite(KEYPAD_PORT,C1,HIGH);
		Gpio_PinWrite(KEYPAD_PORT,C2,HIGH);
		Gpio_PinWrite(KEYPAD_PORT,C3,HIGH);
		
		Gpio_PinDirection(KEYPAD_PORT,R1,SET_IN);
		Gpio_PinDirection(KEYPAD_PORT,R2,SET_IN);
		Gpio_PinDirection(KEYPAD_PORT,R3,SET_IN);
		
		PORT_C |= ( (1<<2) | (1<<3) | (1<<4) );
		InitAPI_State = Keypad_InitOK;
	}
	else
	{
		InitAPI_State	 = Keypad_InitOK;
		API_State		= E_Keypad_NOK;
	}

	return API_State;
}


/**
 * Function : KEYPAD_GetPressedKey
 * Description: this function is used to get the pressed key on the Keypad
 * Param KeyValue is an Input parameter to the Function to set the value in it 
 * @return Status: of the initialization according to the Error handling Enum
 */
EnumKeypadError_t Keypad_GetPressedKey(uint8 * KeyValue)
{

	EnumKeypadError_t API_State = E_Keypad_OK ;

	const uint8 arrROW[No_Of_Row]	= {R1,R2,R3};
	const uint8 arrCol[No_Of_Col]	= {C1,C2,C3};

	//if (InitAPI_State == Keypad_InitOK)
	{
		uint8 Col				= INITIAL_ZERO;
		uint8 Row				= INITIAL_ZERO;
		uint8 PressedKey		= INITIAL_ZERO;
		uint8 Val				= INITIAL_ZERO;
		
		// loop on pressed col
		for (Col = INITIAL_ZERO ; Col < No_Of_Col ; Col++)
		{
			Gpio_PinDirection(KEYPAD_PORT,arrCol[Col],SET_OUT);
			Gpio_PortWrite(KEYPAD_PORT,(~(0b00100000<<arrCol[Col])));
			//Gpio_PinWrite(KEYPAD_PORT,arrCol[Col],LOW);
				// loop on pressed row
				for(Row = INITIAL_ZERO; Row < No_Of_Row; Row++)
				{
					Val = Gpio_PinRead(KEYPAD_PORT,arrROW[Row]);
					if( Val == LOW )
					{
						PressedKey = TRUE;
						* KeyValue = Key_Table[Row][Col];
						break;
					}
				}
				
				Gpio_PinDirection(KEYPAD_PORT,arrCol[Col],SET_IN);
		}

		if ( !PressedKey ){   // TO CHECK WETHER OR NOT YOU DID BREAK THE LOOP OR NOT

				* KeyValue = DEFAULT_KEY; // TO GET WHATEVER THE VALUE YOU WANT TO GET IT SHOWEN
		}
	}
	//else
	//{
		//API_State = E_Keypad_NotInit;
	//}

	return API_State;
}