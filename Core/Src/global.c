/*
 * global.c
 *
 *  Created on: Nov 28, 2024
 *      Author: pc
 */


#include "global.h"

int status = INIT;
int red = 5;
int amber = 2;
int green = 3;
int temp_red = 5;
int temp_amber = 2;
int temp_green = 3;
int max_red = 5;
int max_amber = 2;
int max_green = 3;
int adj_red = 1;
int adj_amber = 1;
int adj_green = 1;

void reTime(){
red = max_red;
amber = max_amber;
green = max_green;
temp_red = red;
temp_amber = amber;
temp_green = green;
}
