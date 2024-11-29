#include "timer.h"
//int timer0_counter = 0;
//int timer0_flag=0;
//int timer1_counter=0;
//int timer1_flag = 0;
//void setTimer0(int duration){
//	timer0_counter = duration  / TIMER_CYCLE;
//	timer0_flag = 0;
//}
//void setTimer1(int duration){
//	timer1_counter = duration  / TIMER_CYCLE;
//	timer1_flag = 0;
//}
//void timerRun(){
//	if(timer0_counter > 0){
//		timer0_counter--;
//		if(timer0_counter == 0) timer0_flag = 1;
//	}
//	if(timer1_counter > 0){
//		timer1_counter--;
//		if(timer1_counter == 0) timer1_flag = 1;
//	}
//}

int timer_flag[MAXTM] = {0};
int timer_counter[MAXTM]= {0};

void setTimer(int index, int counter){
	timer_flag[index] = 0;
	timer_counter[index] = counter;
}
void timerRun(){
	for(int i = 0; i < MAXTM; i++){
		if(timer_counter[i] > 0){
			timer_counter[i]--;

			if(timer_counter <= 0){
				timer_flag[i] = 1;
			}
		}
		else{
			timer_flag[i] = 1;
		}
	}
}

