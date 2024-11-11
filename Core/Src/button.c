/*
 * button.c
 *
 *  Created on: Oct 30, 2024
 *      Author: pc
 */


#include "button.h"

int TimeOutForKeyPress;
int TimeOutForKeyDoublePress[NO_OF_BUTTONS];

int buttonFlags[NO_OF_BUTTONS];


static GPIO_PinState debounceButtonBuffer1[NO_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer2[NO_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer3[NO_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer4[NO_OF_BUTTONS];


static uint8_t flagForButtonPress1s[NO_OF_BUTTONS];
static uint16_t counterForButtonPress1s[NO_OF_BUTTONS];


#define INPUT_PORT GPIOB


void initButton(){
	//clear all buffers, counters and flags
	for(unsigned char i = 0; i < NO_OF_BUTTONS; i++){
		debounceButtonBuffer1[i] 		= BUTTON_IS_RELEASED;	//buffer level 1
		debounceButtonBuffer2[i] 		= BUTTON_IS_RELEASED;	//buffer level 2
		debounceButtonBuffer3[i] 		= BUTTON_IS_RELEASED;	//buffer level 3
		debounceButtonBuffer4[i] 		= BUTTON_IS_RELEASED;	//buffer level 4
		buttonFlags[i] 					= BUTTON_FLAG_CLEAR;	//button pressed flag
		flagForButtonPress1s[i] 		= BUTTON_FLAG_CLEAR;	//button hold flag
//		flagForButtonDoublePressed[i] 	= BUTTON_FLAG_CLEAR;	//button double pressed flag
//		TimeOutForKeyDoublePress[i]     = DOUBLE_PRESS_TIMEOUT;	//time interval double pressed
//		TimeOutForKeyPress[i]           = KEY_HOLD_TIMEOUT;
//		buttonWaitDoublePress[i]        = 0;					//button state wait for double pressed detection
		counterForButtonPress1s[i] 		= 0;					//counter for button hold detection
	}
}

void button_reading (void) {
	//checking for button pressed, hold more than 1 second and double pressed
	for(unsigned char i = 0; i < NO_OF_BUTTONS; i++){
		//propagate buffer stage 2 to stage 3
		debounceButtonBuffer3[i] = debounceButtonBuffer2[i];

		//propagate buffer stage 1 to stage 2
		debounceButtonBuffer2[i] = debounceButtonBuffer1[i];

		//update the lasted button state in buffer 1
		debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(Button_GPIO_Port, Button_Pin);

		//if the button state hold straight for around 40ms
		if((debounceButtonBuffer2[i] == debounceButtonBuffer1[i]) && (debounceButtonBuffer2[i] == debounceButtonBuffer3[i]))
		{
			//check for update buffer level 4
			if(debounceButtonBuffer3[i] != debounceButtonBuffer4[i])
			{
#ifdef RISING_EDGE
				/* Button trigger on rising edge section */
				if(debounceButtonBuffer3[i] == BUTTON_IS_RELEASED)
				{
					//buffer level 3 == button release, buffer level 4 == button Pressed, that mean LOW transistion
					//currently we need to wait 340 ms for button pressed to register because we need to check for button hold and double press
					if(counterForButtonPress1s[i] < DURATION_FOR_AUTO_INCREASING)
					{
						buttonFlags[i] = BUTTON_FLAG_SET;
					}

					//decide button state upon release
					if(buttonWaitDoublePress[i] == 0)
					{
						//start count down for double pressed
						TimeOutForKeyDoublePress[i] = DOUBLE_PRESS_TIMEOUT;
						buttonWaitDoublePress[i] = 1;
					} else {
						//if we get here again, mean that the key is double pressed in time
						//reset the button state and set the double pressed flag
						flagForButtonDoublePressed[i] = BUTTON_FLAG_SET;
						//clear buttonFlags, if it's set
						buttonFlags[i] = BUTTON_FLAG_CLEAR;
						//reset button wait state and button wait double press timeout
						buttonWaitDoublePress[i] = 0;
						TimeOutForKeyDoublePress[i] = 0;
						//clear counter for hold event to prevent unexpected hold button
						counterForButtonPress1s[i] = 0; //counting from 0 after double pressed for button hold event
					}
				}
#endif
				debounceButtonBuffer4[i] = debounceButtonBuffer3[i];
				if(debounceButtonBuffer4[i] == BUTTON_IS_PRESSED){
					/* Button trigger on */
					//set button press flags
					buttonFlags[i] = BUTTON_FLAG_SET;
					//ste the first hold time out for button hold flags
					counterForButtonPress1s[i] = BUTTON_HOLD_TIMEOUT;

				}
				else {
					//button buffer level 4 update state to button release
					//clear the counter and button hold flags
					counterForButtonPress1s[i] = 0;
					flagForButtonPress1s[i] = BUTTON_FLAG_CLEAR;
				}
			} else if(debounceButtonBuffer4[i] == BUTTON_IS_PRESSED){
				//buffer level 3 == buffer level 4 == BUTTON PRESSED

				//if button is still hold, increase counter
				counterForButtonPress1s[i]--;
				//if counter reach hold threshold, set hold 1s flag and continue counting
				//the counter only reset to 0 when the button is release;
				if (counterForButtonPress1s[i] == 0){
					flagForButtonPress1s[i] = BUTTON_FLAG_SET;
					counterForButtonPress1s[i] = AUTO_REPEAT_RATE;
					//with BUTTON HOLD TIMEOUT and AUTO REPEAT RATE,
					//button hold flags is raise after the first 3 second holding button and every 1 second later
				}

				//the release button if the button is hold more than 5 seconds
				//optional feature
//				TimeOutForKeyPress[i]--;
//				if(TimeOutForKeyPress[i] == 0){
//					debounceButtonBuffer4[i] = BUTTON_IS_RELEASED;
//				}
			}
			//if we get here mean that buffer level 3 and buffer level 4 is the same but their state are button release
			//do nothing
		}
#ifdef DOUBLE_PRESS
		//count down, wait for double press event
		if(buttonWaitDoublePress[i] == 1)
		{
			TimeOutForKeyDoublePress[i]--;
			if(TimeOutForKeyDoublePress[i] == 0)
			{
				buttonWaitDoublePress[i] = 0;
				//button double press timeout, only set button pressed flags
				//one option is to set button pressed flag here, but we can't distinguish
				//between button pressed and button hold, so the button hold will the the failed trigger button pressed
			}
		}
#endif
	}
}

unsigned char isButtonPressed(unsigned char index){
	if(index >= NO_OF_BUTTONS) return 0;
#ifdef DOUBLE_PRESS
	if(buttonFlags[index] == BUTTON_FLAG_SET && buttonWaitDoublePress[index] == 0){
		//clear button flags and return
		buttonFlags[index] = BUTTON_FLAG_CLEAR;
		return 1;
	} else return 0;
#else
	if(buttonFlags[index] == BUTTON_FLAG_SET){
		//clear button flags and return
		buttonFlags[index] = BUTTON_FLAG_CLEAR;
		return 1;
	} else return 0;
#endif
}

unsigned char isButtonPressed3s(unsigned char index){
	if(index >= NO_OF_BUTTONS) return 0;
	if(flagForButtonPress1s[index] == BUTTON_FLAG_SET){
		//clear button hold more than 3s flags and return
		flagForButtonPress1s[index] = BUTTON_FLAG_CLEAR;
		return 1;
	} else return 0;
}

#ifdef DOUBLE_PRESS
unsigned char isButtonDoublePressed(unsigned char index){
	if(index >= NO_OF_BUTTONS) return 0;
	if(flagForButtonDoublePressed[index] == BUTTON_FLAG_SET){
		//clear double press flag and return
		flagForButtonDoublePressed[index] = BUTTON_FLAG_CLEAR;
		return 1;
	} else return 0;
}
#endif
