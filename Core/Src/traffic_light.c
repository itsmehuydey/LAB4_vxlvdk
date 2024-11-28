#include "traffic_light.h"
#include "scheduler.h"

void clearAllLed(){
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, RESET);//RED1
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, RESET);//RED2

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, RESET);//YEL1
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, RESET);//YEL2

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, RESET);//GREEN1
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, RESET);//GREEN2
}
void led_red_green(){
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, SET);//RED1
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, SET);//GREEN2
}
void led_red_amber(){
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, SET);//RED1
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, SET);//YEL2
}
void led_green_red(){
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, SET);//RED2
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, SET);//GREEN1
}
void led_amber_red(){
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, SET);//RED2
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, SET);//YEL1
}
void init_traffic_light() {
    // Add tasks for LED control with desired periods
    schedulerAddTask(led_red_green, 50, 50);   // 50 * 10 ms = 500 ms period
    schedulerAddTask(led_red_amber, 51, 100);  // 1 second period task

    // If you need more tasks, you can add them here
    // Example: schedulerAddTask(led_green_amber, 52, 150);
    // or any other LED function as needed.
}
void controlTime_led(){
	if(red <= 0)
		red = temp_red;
	if(green <= 0)
		green = temp_green;
	if(amber <= 0)
		amber = temp_amber;
}
void blinkingLed(int mode){
	switch(mode){
		case MODE_2:
			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);//RED1
			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1);//RED2
			break;
		case MODE_3:
			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_2);//YEL1
			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);//YEL2
			break;
		case MODE_4:
			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_4);//GREEN1
			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_5);//GREEN2
			break;
		default: break;
	}
}



