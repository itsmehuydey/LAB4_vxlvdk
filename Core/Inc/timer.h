///*
// * timer.h
// *
// *  Created on: Oct 4, 2024
// *      Author: pc
// */
#include "global.h"

#define MAXTM 10

extern int timer_flag[MAXTM];
extern int timer_counter[MAXTM];

void setTimer(int index, int counter);
void timerRun();
