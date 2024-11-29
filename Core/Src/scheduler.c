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
//#include "stdlib.h"
#include "string.h"

TaskList_t TaskList;
uint32_t TaskIDCounter = 0; // we using ID as invalid ID
uint32_t timestamp = 0;
ERROR_CODE ErrorCode = NO_ERROR;
ERROR_CODE LastErrorCode = NO_ERROR;

char str[50];

void schedulerInit() {
//    while (TaskList.head != NULL) {
//        deleteTask(TaskList.head->TaskID); // Xóa tác vụ đầu tiên trong danh sách
//    }
    TaskList.head = NULL;	//Node head = 0;
    TaskList.size = 0;        //Asign size = 0
    TaskIDCounter = 0;        // Reset task ID counter
    timestamp = 0;            // Reset timestamp
    ErrorCode = NO_ERROR;      // Clear any existing errors
    LastErrorCode = NO_ERROR;  // Clear last error code
}

void schedulerUpdate() {
    //timestamp += 10; // Cập nhật tổng thời gian
    Node *current = TaskList.head;

    // Duyệt qua danh sách các tác vụ
    while (current != NULL) {
        if (current->Delay > 0) {
            current->Delay--; // Giảm thời gian chờ
        }

        if (current->Delay == 0) {
            current->RunMe++; // Đánh dấu sẵn sàng thực thi

            // Lên lịch lại nếu là tác vụ định kỳ
            if (current->Period > 0) {
                current->Delay = current->Period;
            }
        }

        // Tiếp tục duyệt sang tác vụ kế tiếp
        current = current->NextTask;
    }
}



int deleteTask(uint32_t ID){
    if(TaskList.size == 0)
        return 1;

    Node * curr = TaskList.head;
    Node * prev = NULL;

    while(curr != NULL){
        if(ID == curr -> TaskID){
            if(prev == NULL && curr -> NextTask == NULL){
                free(curr);
                TaskList.head = NULL;
                TaskList.size--;
				curr = NULL;
            } else if (prev == NULL){
                curr -> NextTask -> Delay += curr -> Delay;
                TaskList.head = curr -> NextTask;
                free(curr);
                TaskList.size--;
				curr = NULL;
            } else if (curr -> NextTask == NULL){
                free(curr);
                prev -> NextTask = NULL;
                TaskList.size--;
				curr = NULL;
            } else {
                curr -> NextTask -> Delay += curr -> Delay;
                prev -> NextTask = curr -> NextTask;
                curr -> NextTask = NULL;
                free(curr);
                TaskList.size--;
				curr = NULL;
            }

        } else {
            prev = curr;
            curr = curr -> NextTask;
        }
    }
    return 0;
}

RETURN_CODE schedulerDeleteTask(const unsigned char TaskID){
	RETURN_CODE returnCode;
	if(deleteTask(TaskID))
		returnCode = ERROR_SCH_CANNOT_DELETE_TASK;
	else
		returnCode = NO_ERROR;
	return returnCode;
}

int addTask(Node *task) {
    if (TaskList.size >= SCH_MAX_TASKS) {
        return 1; // Quá số lượng tác vụ cho phép
    }

    task->RunMe = 0; // Đảm bảo cờ được đặt về 0
    if (TaskList.size == 0) {
        TaskList.head = task;
    } else {
        Node *curr = TaskList.head;
        Node *prev = NULL;

        while (curr && task->Delay >= curr->Delay) {
            task->Delay -= curr->Delay;
            prev = curr;
            curr = curr->NextTask;
        }

        task->NextTask = curr;
        if (prev) {
            prev->NextTask = task;
        } else {
            TaskList.head = task;
        }

        if (curr) {
            curr->Delay -= task->Delay;
        }
    }

    TaskList.size++;
    return 0;
}


unsigned char schedulerAddTask(void (*functionPointer)(), unsigned int DELAY, unsigned int PERIOD){
	Node * task = (Node *)malloc(sizeof(Node));
	task -> Delay 		= DELAY;
	task -> Period 		= PERIOD;
	task -> TaskID 		= (++TaskIDCounter)%256;
	task -> TaskPointer = functionPointer;
	task -> NextTask 	= NULL;
	task -> RunMe 		= 0;
	addTask(task);
	return task -> TaskID;
}

void schedulerSleep(){
	// Enter idle or low-power mode
	    __WFI();  // Wait For Interrupt: puts the MCU in idle mode until an interrupt occurs
}

void schedulerDispatcher() {
    while (TaskList.size != 0) {
        Node *current = TaskList.head;

        // Duyệt qua tất cả các tác vụ
        while (current != NULL) {
            if (current->RunMe > 0) {
                current->RunMe--; // Đánh dấu là đã thực thi

                // Báo cáo và thực thi tác vụ
//                uint32_t time_point = timestamp;
//                sprintf(str, "TaskID: %ld timeout at timestamp: %ld ms\r\n", current->TaskID, time_point);
//                writeMessage(str);

                // Thực thi tác vụ
                current->TaskPointer();

                // Nếu là tác vụ định kỳ, không xóa
                if (current->Period == 0) {
                    schedulerDeleteTask(current->TaskID);
                }
            }

            // Tiếp tục với tác vụ kế tiếp
            current = current->NextTask;
        }

        schedulerSleep(); // Đưa hệ thống về chế độ tiết kiệm năng lượng
    }

    schedulerReportStatus();
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


#ifdef WATCHDOG
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
