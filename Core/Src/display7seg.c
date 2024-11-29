/*
 * display7seg.c
 *
 *  Created on: Nov 27, 2024
 *      Author: pc
 */

#include "display7seg.h"

#define MODE 0
#define DUR 1

void displayLED7SEG(int number, int modify){
	int div = number / 10;
	int mod = number % 10;

	int arr1[4] = {0};
	int arr2[4] = {0};

	for(int i = 3; i >= 0; --i){
		arr1[i] = div % 2;
		div = div / 2;

		arr2[i] = mod % 2;
		mod = mod / 2;
	}

	if(modify == MODE){
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, arr1[3]);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, arr1[2]);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, arr1[1]);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, arr1[0]);

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, arr2[3]);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, arr2[2]);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_13, arr2[1]);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_14, arr2[0]);
	}
	if(modify == DUR){
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, arr1[3]);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, arr1[2]);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, arr1[1]);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, arr1[0]);

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, arr2[3]);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, arr2[2]);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, arr2[1]);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, arr2[0]);
	}
}
