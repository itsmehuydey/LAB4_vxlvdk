//#include "global.h"
//
//
//uint16_t pinBuffer[NUM_OF_BUTTONS];
//int postState[NUM_OF_BUTTONS]={1,1,1};//2 //000
//int preState[NUM_OF_BUTTONS]={1,1,1};//0 //000
//int currentState[NUM_OF_BUTTONS]={1,1,1};//1
//int buttonState [NUM_OF_BUTTONS]={1,1,1};
//int buttonCounter[NUM_OF_BUTTONS]={0,0,0};
//int button[NUM_OF_BUTTONS]={1,1,1};
//int flag_reset = 0;
//int flag_set = 0;
//int flag_change = 0;
//int flag_settime_mode = 0;
//int flag_holding = 0;
//int number_settime = 0;
//int mode = 0;
//
//uint8_t debounceCounter[NUM_OF_BUTTONS] = {0};
////GPIO_PinState postState[NUM_OF_BUTTONS];//2
////GPIO_PinState preState[NUM_OF_BUTTONS];//0
////GPIO_PinState currentState[NUM_OF_BUTTONS];//1
//void readButton(void) {
//    for (int i = 0; i < NUM_OF_BUTTONS; i++) {
//    	postState[i] = currentState[i];
//    	currentState[i] = preState[i];
//    	preState[i] = HAL_GPIO_ReadPin(portBuffer[i], pinBuffer[i]);
//        if((currentState[i] == postState[i])&&(currentState[i] == preState[i])){
//        	if (postState[i]!=buttonState[i])
//        		buttonState[i]=postState[i];
//        }
//                switch (button[i]) {
//                    case RELEASED:
//                    	button[i] = buttonState[i];
//                        break;
//                    case PRESSED:
//                        if (button[i] == PRESSED) {
//                            if (i == 0 && buttonCounter[0] == 0) {
//                                flag_reset = 1;
//                            } else if (i == 1 && buttonCounter[1] == 0) {
//                            	flag_settime_mode = 1;
//                            } else if (i == 2 && buttonCounter[2] == 0) {
//                                flag_set = 1;
//                            }
//                            if (buttonCounter[i] <= HOLDED) {
//                                buttonCounter[i]++;
//                            } else {
//                                buttonCounter[i] = 0;
//                                button[i] = INCREASE;
//                            }
//                        } else {
//                            buttonCounter[i] = 0;
//                            button[i] = RELEASED;
//                        }
//                        break;
//                    case INCREASE:
//                        if (buttonState[1] == PRESSED) {
//                            handleIncrease(i);
//                        } else {
//                            buttonCounter[i] = 0;
//                            button[i] = RELEASED;
//                        }
//                        break;
//
//                    default:
//                        break;
//                }
//            }
//    }
//
//int getButton(int index){
//	if(index >= NUM_OF_BUTTONS) return -1;
//	else return button[index];
//}
//
//
//
//
////void setFlags_HandleActions() {
////		if (flag_reset == 1) {
////		        reset();         // Perform the reset action
////		        mode++;          // Update the mode
////		        if (mode > 4) {
////		            mode = 1;
////		            retime();
////		        }
////		        number_settime = 0;
////		        flag_reset = 0;  // Reset the flag
////		    }
////}
//
//void handleIncrease(int i) {
//    if (buttonCounter[i] % 10 == 0) {
//        number_settime++;
//        if (number_settime > 99) number_settime = 0;
//    }
//    buttonCounter[i]++;
//}
//

#include "button.h"

int KeyReg0[N0_OF_BUTTONS] = {NORMAL_STATE};
int KeyReg1[N0_OF_BUTTONS] = {NORMAL_STATE};
int KeyReg2[N0_OF_BUTTONS] = {NORMAL_STATE};
int KeyReg3[N0_OF_BUTTONS] = {NORMAL_STATE};

int TimeOutForKeyPress = 500;
int button_flag[N0_OF_BUTTONS] = {0};
int button_long_pressed[N0_OF_BUTTONS] = {0};

int isButtonPressed(int index){
	if(button_flag[index] == 1)
		return 1;
	return 0;
}

int isButtonLongPressed(int index){
	if(button_long_pressed[index] == 1)
		return 1;
	return 0;
}

void getKeyInput(){
	static int longPressCounter[N0_OF_BUTTONS] = {0};
	for(int i = 0; i < N0_OF_BUTTONS; i++){
		KeyReg2[i] = KeyReg1[i];
		KeyReg1[i] = KeyReg0[i];
	}
	KeyReg0[0] = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6);
	KeyReg0[1] = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7);
	KeyReg0[2] = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8);

	for(int i = 0; i < N0_OF_BUTTONS; i++){
		if((KeyReg1[i] == KeyReg0[i]) && (KeyReg2[i] == KeyReg1[i])){
			if(KeyReg2[i] != KeyReg3[i]){
				KeyReg3[i] = KeyReg2[i];

				if(KeyReg3[i] == PRESSED_STATE){
					TimeOutForKeyPress = 500;
					button_flag[i] = 1;
				}
			}
			else{
				TimeOutForKeyPress--;
				if(TimeOutForKeyPress == 0){
					TimeOutForKeyPress = 500;

					if(KeyReg3[i] == PRESSED_STATE){
						button_flag[i] = 1;
					}
					//else release
				}
			}
			if(KeyReg3[i] == PRESSED_STATE){
			  	longPressCounter[i]++;
			  	if(longPressCounter[i] >= 200){
			  		button_flag[i] = 1;
			  		longPressCounter[i] = 190;
			  	}
			}
			else {
				longPressCounter[i] = 0;
			}
		}
	}
}


