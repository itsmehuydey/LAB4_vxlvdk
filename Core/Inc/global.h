/*
 * global.h
 *
 *  Created on: Oct 30, 2024
 *      Author: pc
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

//Begin global define section
#define REFRESH_RATE 100
#define TIMER_CYCLE 1
#define SHIFT_CYCLE 500
#define BUTTON_SCAN_INTERVAL 10
#define BUTTON_THRESHOLD 5

//#define REPORT_ERROR

//End global define section

//Begin global include section
#include "main.h"
//#include "usart.h"

//End global include section
extern UART_HandleTypeDef huart1;

//Begin global variable section
extern uint32_t timestamp;
//End global variable section

//Begin global function section
void writeMessage(char * str);
//End global fucnction section

#endif /* INC_GLOBAL_H_ */
