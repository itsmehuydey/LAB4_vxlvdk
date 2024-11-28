/*
 * fsm_manual.c
 *
 *  Created on: Nov 27, 2024
 *      Author: pc
 */
#include "fsm_manual.h"
#include "scheduler.h"
//void fsm_manual(){
//	switch(status){
//		case MAN_RED_GREEN:
//			led_red_green();
//			if(timer_flag[1]){
//				status = RED_GREEN;
//				clearAllLed();
//				red = temp_red;
//				green = temp_green;
//				amber = temp_amber;
//				setTimer(1, green*100);
//			}
//			if(isButtonPressed(1)){
//				status = MAN_RED_AMBER;
//				red = 10;
//				amber = 10;
//				clearAllLed();
//				setTimer(1, 1000);
//				button_flag[1] = 0;
//			}
//			if(isButtonPressed(0)){
//				status = MODE_2;
//				clearAllLed();
//				setTimer(0, 1);
//				button_flag[0] = 0;
//			}
//			if(timer_flag[0]){
//				--red;
//				--green;
//				displayLED7SEG(red, 0);
//				displayLED7SEG(green, 1);
//				setTimer(0, 100);
//			}
//			break;
//		case MAN_RED_AMBER:
//			led_red_amber();
//			if(timer_flag[1]){
//				status = RED_GREEN;
//				clearAllLed();
//				red = temp_red;
//				green = temp_green;
//				amber = temp_amber;
//				setTimer(1, green*100);
//			}
//			if(timer_flag[0]){
//				--red;
//				--amber;
//
//				displayLED7SEG(red, 0);
//				displayLED7SEG(amber, 1);
//
//
//				setTimer(0, 100);
//			}
//			if(isButtonPressed(1)){
//				status = MAN_GREEN_RED;
//				setTimer(1, 1000);
//				clearAllLed();
//				red = 10;
//				green = 10;
//				button_flag[1] = 0;
//			}
//			if(isButtonPressed(0)){
//				status = MODE_2;
//				clearAllLed();
//				setTimer(0, 1);
//				button_flag[0] = 0;
//			}
//			break;
//		case MAN_GREEN_RED:
//			led_green_red();
//			if(timer_flag[0]){
//				--red;
//				--green;
//				displayLED7SEG(green, 0);
//				displayLED7SEG(red, 1);
//				setTimer(0, 100);
//			}
//			if(timer_flag[1]){
//				status = RED_GREEN;
//				clearAllLed();
//				red = temp_red;
//				green = temp_green;
//				amber = temp_amber;
//				setTimer(1, green*100);
//			}
//			if(isButtonPressed(1)){
//				status = MAN_AMBER_RED;
//				red = 10;
//				amber = 10;
//				setTimer(1, 1000);
//				clearAllLed();
//				button_flag[1] = 0;
//			}
//			if(isButtonPressed(0)){
//				status = MODE_2;
//				clearAllLed();
//				setTimer(0, 1);
//				button_flag[0] = 0;
//			}
//			break;
//		case MAN_AMBER_RED:
//			led_amber_red();
//			if(timer_flag[1]){
//				status = RED_GREEN;
//				clearAllLed();
//				red = temp_red;
//				green = temp_green;
//				amber = temp_amber;
//				setTimer(1, green*100);
//			}
//			if(timer_flag[0]){
//				--red;
//				--amber;
//				displayLED7SEG(amber, 0);
//				displayLED7SEG(red, 1);
//				controlTime_led();
//				setTimer(0, 100);
//			}
//			if(isButtonPressed(1)){
//				status = MAN_RED_GREEN;
//				setTimer(1, 1000);
//				clearAllLed();
//				red = 10;
//				green = 10;
//				button_flag[1] = 0;
//			}
//			if(isButtonPressed(0)){
//				status = MODE_2;
//				clearAllLed();
//				setTimer(0, 1);
//				button_flag[0] = 0;
//			}
//			break;
//		default: break;
//	}
//}

void fsm_manual(){
    static int counter = 0;  // A simple counter to simulate time-based events

    switch(status){
        case MAN_RED_GREEN:
            led_red_green();

            // Replace timer_flag with counter for periodic actions
            if(counter >= (green * 100)){
                status = RED_GREEN;
                clearAllLed();
                red = temp_red;
                green = temp_green;
                amber = temp_amber;
                counter = 0;  // Reset the counter after action
            }

            // Button press handling
            if(isButtonPressed(1)){
                status = MAN_RED_AMBER;
                red = 10;
                amber = 10;
                clearAllLed();
                counter = 0;  // Reset counter when switching mode
                button_flag[1] = 0;
            }

            if(isButtonPressed(0)){
                status = MODE_2;
                clearAllLed();
                counter = 0;  // Reset counter when switching mode
                button_flag[0] = 0;
            }

            // Simulate timer flag behavior with counter for decrementing red and green
            if(counter >= 100){
                --red;
                --green;
                displayLED7SEG(red, 0);
                displayLED7SEG(green, 1);
                counter = 0;  // Reset the counter after action
            }
            break;

        case MAN_RED_AMBER:
            led_red_amber();

            // Replace timer_flag with counter for periodic actions
            if(counter >= 100){
                status = RED_GREEN;
                clearAllLed();
                red = temp_red;
                green = temp_green;
                amber = temp_amber;
                counter = 0;  // Reset the counter after action
            }

            // Simulate timer flag behavior with counter for decrementing red and amber
            if(counter >= 100){
                --red;
                --amber;
                displayLED7SEG(red, 0);
                displayLED7SEG(amber, 1);
                counter = 0;  // Reset the counter after action
            }

            if(isButtonPressed(1)){
                status = MAN_GREEN_RED;
                red = 10;
                green = 10;
                clearAllLed();
                counter = 0;  // Reset counter when switching mode
                button_flag[1] = 0;
            }

            if(isButtonPressed(0)){
                status = MODE_2;
                clearAllLed();
                counter = 0;  // Reset counter when switching mode
                button_flag[0] = 0;
            }
            break;

        case MAN_GREEN_RED:
            led_green_red();

            // Simulate timer flag behavior with counter for decrementing red and green
            if(counter >= 100){
                --red;
                --green;
                displayLED7SEG(green, 0);
                displayLED7SEG(red, 1);
                counter = 0;  // Reset the counter after action
            }

            if(counter >= (green * 100)){
                status = RED_GREEN;
                clearAllLed();
                red = temp_red;
                green = temp_green;
                amber = temp_amber;
                counter = 0;  // Reset the counter after action
            }

            if(isButtonPressed(1)){
                status = MAN_AMBER_RED;
                red = 10;
                amber = 10;
                clearAllLed();
                counter = 0;  // Reset counter when switching mode
                button_flag[1] = 0;
            }

            if(isButtonPressed(0)){
                status = MODE_2;
                clearAllLed();
                counter = 0;  // Reset counter when switching mode
                button_flag[0] = 0;
            }
            break;

        case MAN_AMBER_RED:
            led_amber_red();

            // Simulate timer flag behavior with counter for decrementing red and amber
            if(counter >= 100){
                status = RED_GREEN;
                clearAllLed();
                red = temp_red;
                green = temp_green;
                amber = temp_amber;
                counter = 0;  // Reset the counter after action
            }

            if(counter >= 100){
                --red;
                --amber;
                displayLED7SEG(amber, 0);
                displayLED7SEG(red, 1);
                controlTime_led();  // Assuming this function adjusts time
                counter = 0;  // Reset the counter after action
            }

            if(isButtonPressed(1)){
                status = MAN_RED_GREEN;
                red = 10;
                green = 10;
                clearAllLed();
                counter = 0;  // Reset counter when switching mode
                button_flag[1] = 0;
            }

            if(isButtonPressed(0)){
                status = MODE_2;
                clearAllLed();
                counter = 0;  // Reset counter when switching mode
                button_flag[0] = 0;
            }
            break;

        default:
            break;
    }

    // Increment the counter to simulate a time-based event
    counter++;
}




