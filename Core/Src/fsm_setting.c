/*
 * fsm_setting.c
 *
 *  Created on: Nov 27, 2024
 *      Author: pc
 */

#include "fsm_setting.h"
#include "scheduler.h"
//void fsm_setting(){
//	switch(status){
//		case MODE_1:
//			status = INIT;
//			break;
//		case MODE_2:
//			displayLED7SEG(status, 1);
//			displayLED7SEG(adj_red, 0);
//			if(timer_flag[0]){
//				blinkingLed(status);
//				setTimer(0, 50);
//			}
//			if(isButtonPressed(0)){
//				status = MODE_3;
//				clearAllLed();
//				button_flag[0] = 0;
//			}
//			if(isButtonPressed(1)){
//				button_flag[1] = 0;
//				adj_red++;
//				if(adj_red == 100)
//					adj_red = 1;
//				displayLED7SEG(adj_red, 0);
//			}
//			if(isButtonPressed(2)){
//				button_flag[2] = 0;
//				if(adj_red > 2 && adj_red < 98){
//					amber = ((temp_green < adj_red) ? (adj_red - temp_green) : temp_amber);
//
//					if(green + amber < 100){
//						green = adj_red - amber;
//						red = adj_red;
//
//						temp_red = red;
//						temp_amber = amber;
//						temp_green = green;
//					}
//					else{
//						reTime();
//					}
//				}
//				else{
//					red = max_red;
//					amber = max_amber;
//					green = max_green;
//				}
//				clearAllLed();
//				status = RED_GREEN;
//				setTimer(1, green*100);
//				setTimer(0, 1);
//			}
//			break;
//		case MODE_3:
//			displayLED7SEG(status, 1);
//			displayLED7SEG(adj_amber, 0);
//			if(timer_flag[0]){
//				blinkingLed(status);
//				setTimer(0, 50);
//			}
//			if(isButtonPressed(0)){
//				status = MODE_4;
//				clearAllLed();
//				button_flag[0] = 0;
//			}
//			if(isButtonPressed(1)){
//				button_flag[1] = 0;
//				adj_amber++;
//				if(adj_amber == 100)
//					adj_amber = 1;
//				displayLED7SEG(adj_amber, 0);
//			}
//			if(isButtonPressed(2)){
//				button_flag[2] = 0;
//				green = ((adj_amber < temp_red) ? (temp_red - adj_amber) : temp_green);
//
//
//				if((green + adj_amber) < 100){
//					red = green + adj_amber;
//					amber = adj_amber;
//					temp_red = red;
//					temp_amber = amber;
//					temp_green = green;
//				}
//				else{
//					reTime();
//				}
//				clearAllLed();
//				status = RED_GREEN;
//				setTimer(1, green*100);
//				setTimer(0, 1);
//			}
//			break;
//		case MODE_4:
//			displayLED7SEG(status, 1);
//			displayLED7SEG(adj_green, 0);
//			if(timer_flag[0]){
//				blinkingLed(status);
//				setTimer(0, 50);
//			}
//			if(isButtonPressed(0)){
//				status = MODE_1;
//				clearAllLed();
//				button_flag[0] = 0;
//			}
//			if(isButtonPressed(1)){
//				button_flag[1] = 0;
//				adj_green++;
//				if(adj_green == 100)
//					adj_green = 1;
//				displayLED7SEG(adj_green, 0);
//			}
//			if(isButtonPressed(2)){
//				button_flag[2] = 0;
//				amber = ((adj_green < temp_red) ? (temp_red - adj_green) : temp_amber);
//
//				if(adj_green + amber < 100){
//					red = adj_green + amber;
//					green = adj_green;
//					temp_red = red;
//					temp_amber = amber;
//					temp_green = green;
//				}
//				else{
//					reTime();
//				}
//				clearAllLed();
//				status = RED_GREEN;
//				setTimer(1, green*100);
//				setTimer(0, 1);
//			}
//			break;
//		default:
//			break;
//	}
//}

void fsm_setting(){
    static int counter = 0;  // A simple counter to simulate time-based events

    switch(status){
        case MODE_1:
            status = INIT;
            break;
        case MODE_2:
            displayLED7SEG(status, 1);
            displayLED7SEG(adj_red, 0);

            // Replace timer-based blinking with a counter for periodic action
            if(counter >= 50) {
                blinkingLed(status);  // Assuming this function performs blinking
                counter = 0;  // Reset the counter after the action
            }

            // Button press handling
            if(isButtonPressed(0)){
                status = MODE_3;
                clearAllLed();
                button_flag[0] = 0;
            }
            if(isButtonPressed(1)){
                button_flag[1] = 0;
                adj_red++;
                if(adj_red == 100)
                    adj_red = 1;
                displayLED7SEG(adj_red, 0);
            }
            if(isButtonPressed(2)){
                button_flag[2] = 0;
                if(adj_red > 2 && adj_red < 98){
                    amber = ((temp_green < adj_red) ? (adj_red - temp_green) : temp_amber);

                    if(green + amber < 100){
                        green = adj_red - amber;
                        red = adj_red;

                        temp_red = red;
                        temp_amber = amber;
                        temp_green = green;
                    }
                    else{
                        reTime();
                    }
                }
                else{
                    red = max_red;
                    amber = max_amber;
                    green = max_green;
                }
                clearAllLed();
                status = RED_GREEN;
                // No setTimer call here, just directly proceed to RED_GREEN
            }
            break;
        case MODE_3:
            displayLED7SEG(status, 1);
            displayLED7SEG(adj_amber, 0);

            // Replace timer-based blinking with a counter for periodic action
            if(counter >= 50) {
                blinkingLed(status);  // Assuming this function performs blinking
                counter = 0;  // Reset the counter after the action
            }

            // Button press handling
            if(isButtonPressed(0)){
                status = MODE_4;
                clearAllLed();
                button_flag[0] = 0;
            }
            if(isButtonPressed(1)){
                button_flag[1] = 0;
                adj_amber++;
                if(adj_amber == 100)
                    adj_amber = 1;
                displayLED7SEG(adj_amber, 0);
            }
            if(isButtonPressed(2)){
                button_flag[2] = 0;
                green = ((adj_amber < temp_red) ? (temp_red - adj_amber) : temp_green);

                if((green + adj_amber) < 100){
                    red = green + adj_amber;
                    amber = adj_amber;
                    temp_red = red;
                    temp_amber = amber;
                    temp_green = green;
                }
                else{
                    reTime();
                }
                clearAllLed();
                status = RED_GREEN;
                // No setTimer call here, just directly proceed to RED_GREEN
            }
            break;
        case MODE_4:
            displayLED7SEG(status, 1);
            displayLED7SEG(adj_green, 0);

            // Replace timer-based blinking with a counter for periodic action
            if(counter >= 50) {
                blinkingLed(status);  // Assuming this function performs blinking
                counter = 0;  // Reset the counter after the action
            }

            // Button press handling
            if(isButtonPressed(0)){
                status = MODE_1;
                clearAllLed();
                button_flag[0] = 0;
            }
            if(isButtonPressed(1)){
                button_flag[1] = 0;
                adj_green++;
                if(adj_green == 100)
                    adj_green = 1;
                displayLED7SEG(adj_green, 0);
            }
            if(isButtonPressed(2)){
                button_flag[2] = 0;
                amber = ((adj_green < temp_red) ? (temp_red - adj_green) : temp_amber);

                if(adj_green + amber < 100){
                    red = adj_green + amber;
                    green = adj_green;
                    temp_red = red;
                    temp_amber = amber;
                    temp_green = green;
                }
                else{
                    reTime();
                }
                clearAllLed();
                status = RED_GREEN;
                // No setTimer call here, just directly proceed to RED_GREEN
            }
            break;
        default:
            break;
    }

    // Increment the counter to simulate a time-based event
    counter++;
}





