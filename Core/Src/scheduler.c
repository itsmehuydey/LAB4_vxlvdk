/*
 * scheduler.c
 *
 *  Created on: Oct 30, 2024
 *      Author: pc
 */

#ifndef SRC_SCHEDULER_C_
#define SRC_SCHEDULER_C_

#include "scheduler.h"
#include "main.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

TaskList_t TaskList;
uint32_t TaskIDCounter = 0; // we using ID as invalid ID

ERROR_CODE ErrorCode = NO_ERROR;
ERROR_CODE LastErrorCode = NO_ERROR;

char str[50];

void schedulerInit(){
	TaskList.head = NULL;
	TaskList.size = 0;
}

void schedulerUpdate(){
	// checking the head of task list, and decrease the delay time
	timestamp+=10;  // increase 10 ms each
	// report back to uart channel the timestamp value
	if(TaskList.size && TaskList.head -> Delay > 0) TaskList.head -> Delay--;
}

int deleteTask(uint32_t ID){
    if(TaskList.size == 0)
        // The list is empty, invalid operation
        return 1;

    TaskControlBlock_t * curr = TaskList.head;
    TaskControlBlock_t * prev = NULL;

    while(curr != NULL){
        if(ID == curr -> TaskID){
            // found task
            if(prev == NULL && curr -> NextTask == NULL){
                // delete at the head of the list only 1 element
                free(curr);
                TaskList.head = NULL;
                TaskList.size--;
                // after deletion, set curr to null pointer to exit the loop
				curr = NULL;
            } else if (prev == NULL){
                // delete at the head of the list has more than 1 elements
                curr -> NextTask -> Delay += curr -> Delay;
                TaskList.head = curr -> NextTask;
                free(curr);
                TaskList.size--;
                // after deletion, set curr to null pointer to exit the loop
				curr = NULL;
            } else if (curr -> NextTask == NULL){
                // delete at the end of the list
                free(curr);
                prev -> NextTask = NULL;
                TaskList.size--;
                // after deletion, set curr to null pointer to exit the loop
				curr = NULL;
            } else {
                // delete in the middle of the list
                curr -> NextTask -> Delay += curr -> Delay;
                prev -> NextTask = curr -> NextTask;
                curr -> NextTask = NULL;
                free(curr);
                TaskList.size--;
                // after deletion, set curr to null pointer to exit the loop
				curr = NULL;
            }

        } else {
            // update current and previous pointer
            prev = curr;
            curr = curr -> NextTask;
        }
    }

    // No task found
    return 0;
}

RETURN_CODE schedulerDeleteTask(const unsigned char TaskID){
	RETURN_CODE returnCode;
	if(deleteTask(TaskID))
		// no task found or the task list is empty
		returnCode = ERROR_SCH_CANNOT_DELETE_TASK;
	else
		// deletion operate normally
		returnCode = NO_ERROR;
	return returnCode;
}

int addTask(TaskControlBlock_t * task){
    if(TaskList.size >= SCH_MAX_TASKS)
        // the task list is full
        return 1;
    if(TaskList.size == 0){
        // the task list is empty
        TaskList.head = task;
        TaskList.size++;
        return 0;
    }

    TaskControlBlock_t * curr = TaskList.head;
    TaskControlBlock_t * prev = NULL;
    int found = 0;
    while(!found){
        // Using greater or equal mean that new task will be insert after the task that have the same delay time
        if(curr != NULL && task-> Delay >= curr-> Delay){
            // decrease task starting time stamp
            task -> Delay -= curr -> Delay;
            // update current and previous pointer
            prev = curr;
            curr = curr -> NextTask;
        } else {
            /* this is the slot for new added task
             *
             *  head            prev         curr
             *
             *  task_0 -> ... task_prev -> task_curr -> task_next -> ... -> NULL;
             */
            task -> NextTask = curr;
            // Check if prev is not NULL, if null the the insertion is at the head of the list
            if(prev != NULL) prev -> NextTask = task;
            else TaskList.head = task;

            // at this point, task -> delay must be less than curr -> Delay,
            // if curr != NULL, we update delay time for curr task
            if(curr != NULL) curr -> Delay -= task -> Delay;
            TaskList.size++;
            found = 1;
        }
    }
    return 0;
}

unsigned char schedulerAddTask(void (*functionPointer)(), unsigned int DELAY, unsigned int PERIOD){
	// allocate a new memory chunk to store task control block
	TaskControlBlock_t * task = (TaskControlBlock_t *)malloc(sizeof(TaskControlBlock_t));

	// copy task parameter
	task -> Delay 		= DELAY;
	task -> Period 		= PERIOD;
	task -> TaskID 		= (++TaskIDCounter)%256;
	task -> TaskPointer = functionPointer;
	task -> NextTask 	= NULL;

	// currently we dont check add task exit code
	addTask(task);

	return task -> TaskID;
}

void schedulerDispatcher(){
	while(TaskList.size != 0 &&TaskList.head -> Delay == 0){
		// report timeout task
		uint32_t time_point = timestamp;
		sprintf(str, "TaskID: %ld timeout at timestamp: %ld ms\r\n", TaskList.head -> TaskID, time_point);
		writeMessage(str);
		// execute all task timed out
		(*TaskList.head -> TaskPointer)();
		// add the task back to task list if the task is periodic
		if(TaskList.head -> Period) schedulerAddTask(TaskList.head -> TaskPointer, TaskList.head -> Period, TaskList.head -> Period);
		// delete complete task
		schedulerDeleteTask(TaskList.head -> TaskID);
	}
	schedulerReportStatus();
	//schedulerSleep();
}

int ErrorTickCount = 0;
void schedulerReportStatus(){
#ifdef REPORT_ERROR
	//only apply if we report error
	//check for a new error code
	if(ErrorCode != LastErrorCode){
		LastErrorCode = ErrorCode;
		TaskID_ScreenControl = schedulerAddTask(updateLEDMatrix, 10, 1, NULLPTR);
		setMatrixErrorCode(ErrorCode);
		if(ErrorCode != 0){
			ErrorTickCount = 60000;
		} else {
			ErrorTickCount = 0;
		}
	} else {
		if(ErrorTickCount != 0){
			if(--ErrorTickCount == 0){
				ErrorCode = 0; //reset error code
			}
		}
	}
#endif
};

void schedulerSleep(){
	//temporary do nothing here
};

#ifdef WATCHDOG
//watchdog section
IWDG_HandleTypeDef hiwdg ;
static uint32_t counterForWatchdog = 0;
void MX_IWDG_Init(){
	hiwdg.Instance = IWDG;
	hiwdg.Init.Prescaler = IWDG_PRESCALER_32;
	hiwdg.Readload = 4095;
	if(HAL_IWDG_Init(&hiwdg) != HAL_OK) Error_Handler();
}

void watchDogRefresh(){
	HAL_IWDG_Refresh(&hiwdg);
}
unsigned char isWatchDogReset(){
	if(counterForWatchdog > 3) return 1;
	else return 0;
}
void watchdogCounting(){
	counterForWatchdog++;
}
void resetWatchdogCounting(){
	counterForWatchdog = 0;
}
#endif

#endif /* SRC_SCHEDULER_C_ */
