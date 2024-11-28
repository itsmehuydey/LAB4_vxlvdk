/*
 * scheduler.h
 *
 *  Created on: Oct 30, 2024
 *      Author: pc
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

//Begin include section
#include "global.h"
#include <stdlib.h>
//End include section

//Begin Define Section
#define SCH_MAX_TASKS  32
#define NO_TASK_ID 0
//End Define Section

//Type Definition Declaration
//=================================================================


struct Node {
	void (*TaskPointer)();
    uint32_t 				TaskID;
    uint32_t 				Delay;
    uint32_t 				Period;
    uint32_t 				RunMe;
    struct Node * 	NextTask;
};

typedef struct Node Node;

typedef struct {
    Node * head;
    int size;
} TaskList_t;


//type definition for ERRORCODE
typedef enum {
		NO_ERROR,
		ERROR_SCH_TOO_MANY_TASKS,
		ERROR_SCH_CANNOT_DELETE_TASK
} ERROR_CODE;

//type definition for RETURN CODE
typedef enum {
		RETURN_NORMAL,
		RETURN_ERROR
} RETURN_CODE;

//=================================================================

//Function Declaration
//void 			systemInitialzation();
void 		  	schedulerInit();
unsigned char 	schedulerAddTask(void (* functionPointer)(), unsigned int DELAY, unsigned int PERIOD);
void 		  	schedulerUpdate();
void 		  	schedulerDispatcher();
RETURN_CODE   	schedulerDeleteTask(const unsigned char TaskID);

#ifdef WATCHDOG
void watchDogRefresh();
unsigned char isWatchDogReset();
void watchdogCounting();
void resetWatchdogCounting();
#endif
//operation relation function
void 			schedulerReportStatus();
void 			schedulerSleep();

#endif /* INC_SCHEDULER_H_ */
