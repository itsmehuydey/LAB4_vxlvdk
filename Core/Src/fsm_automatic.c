/*
 * fsm_automatic.c
 *
 *  Created on: Nov 27, 2024
 *      Author: pc
 */

#include "fsm_automatic.h"

void run_traffic_light(){
	if(timer_flag[0]){
		blinkingLed(status);
		setTimer(0, 50);
	}
}
void fsm_automatic(){
	int amber_dummy;
	int green_dummy;
		if(timer_flag[2] ==1){
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
			setTimer(2, 100);
		}
	switch(status){
		case INIT:
			status = RED_GREEN;
			setTimer(1, 300);//300
			setTimer(0, 0);//0
			clearAllLed();
			red = max_red;
			amber = max_amber;
			green = max_green;
			temp_red = max_red;
			temp_amber = max_amber;
			temp_green = max_green;
			break;
		case RED_GREEN:
			led_red_green();
			if(timer_flag[0]){
				--red;
				--green;
				displayLED7SEG(red, 0);
				displayLED7SEG(green, 1);
				controlTime_led();
				setTimer(0, 100);
			}
			if(timer_flag[1]){
				status = RED_AMBER;
				clearAllLed();
				amber_dummy = amber*100;
				setTimer(1, amber_dummy);
			}
			if(isButtonPressed(1)){
				status = MAN_RED_GREEN;
				setTimer(1, 1000);
				clearAllLed();
				red = 10;
				green = 10;
				button_flag[1] = 0;
				setTimer(0, 1);
			}
			if(isButtonPressed(0)){
				status = MODE_2;
				clearAllLed();
				setTimer(0, 1);
				button_flag[0] = 0;
			}
			break;
		case RED_AMBER:
			led_red_amber();
			if(timer_flag[0]){
				--red;
				--amber;
				displayLED7SEG(red, 0);
				displayLED7SEG(amber, 1);


				controlTime_led();

				setTimer(0, 100);
			}
			if(timer_flag[1]){
				status = GREEN_RED;
				clearAllLed();
				green_dummy = green*100;
				setTimer(1, green_dummy);
			}
			if(isButtonPressed(1)){
				status = MAN_RED_AMBER;
				setTimer(1, 1000);
				clearAllLed();
				red = 10;
				amber = 10;
				button_flag[1] = 0;
				setTimer(0, 1);
			}
			if(isButtonPressed(0)){
				status = MODE_2;
				clearAllLed();
				setTimer(0, 1);
				button_flag[0] = 0;
			}
			break;
		case GREEN_RED:
			led_green_red();
			if(timer_flag[0]){
				--red;
				--green;
				displayLED7SEG(green, 0);
				displayLED7SEG(red, 1);
				controlTime_led();
				setTimer(0, 100);
			}
			if(timer_flag[1]){
				status = AMBER_RED;
				clearAllLed();
				amber_dummy = amber*100;
				setTimer(1, amber_dummy);
			}
			if(isButtonPressed(1)){
				status = MAN_GREEN_RED;
				red = 10;
				green = 10;
				clearAllLed();
				setTimer(1, 1000);
				button_flag[1] = 0;
				setTimer(0, 1);
			}
			if(isButtonPressed(0)){
				status = MODE_2;
				clearAllLed();
				setTimer(0, 1);
				button_flag[0] = 0;
			}
			break;
		case AMBER_RED:
			led_amber_red();
			if(timer_flag[0]){
				--red;
				--amber;
				displayLED7SEG(amber, 0);
				displayLED7SEG(red, 1);
				controlTime_led();
				setTimer(0, 100);
			}
			if(timer_flag[1]){
				status = RED_GREEN;
				clearAllLed();
				green_dummy = green*100;
				setTimer(1, green_dummy);
			}
			if(isButtonPressed(1)){
				status = MAN_AMBER_RED;
				red = 10;
				amber = 10;
				setTimer(1, 1000);
				clearAllLed();
				button_flag[1] = 0;
				setTimer(0, 1);
			}
			if(isButtonPressed(0)){
				status = MODE_2;
				clearAllLed();
				setTimer(0, 1);
				button_flag[0] = 0;
			}
			break;
		default: break;
	}
}


