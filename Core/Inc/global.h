#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_
#include "main.h"
#include "fsm_manual.h"
#include "fsm_setting.h"
#include "fsm_automatic.h"
#include "timer.h"
#include "button.h"
#include "display7seg.h"
#define MODE_1	1	//NORMAL
#define MODE_2	2	//MODIFY LED_RED
#define MODE_3	3	//MODIFY LED_YELLOW
#define MODE_4	4	//MODIFY LED_GREEN

#define INIT 0
#define RED_GREEN 5
#define RED_AMBER 6
#define GREEN_RED 7
#define AMBER_RED 8
#define MAN_RED_GREEN 9
#define MAN_RED_AMBER 10
#define MAN_GREEN_RED 11
#define MAN_AMBER_RED 12

extern int status;

extern int red;
extern int amber;
extern int green;
extern int temp_red;
extern int temp_amber;
extern int temp_green;
extern int max_red;
extern int max_amber;
extern int max_green;
extern int adj_red;
extern int adj_amber;
extern int adj_green;
void reTime();
#endif /* INC_GLOBAL_H_ */
