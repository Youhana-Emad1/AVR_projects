/*
 * RTOS_interface.h
 *
 * Created: 2/3/2024 9:58:31 AM
 *  Author: Kareem Hussein
 */ 


#ifndef RTOS_INTERFACE_H_
#define RTOS_INTERFACE_H_


typedef struct
{
	void(*pFunTask)(void);
	u16	 TaskPeriodicity;
	u8   TaskStatus;
}Task_t;


#define RTOS_TASK_SUSPENDED			1
#define RTOS_TASK_RESUMED           2


void RTOS_start      (void);
void RTOS_createTask (u8 priority ,u16 periodicity, void(*ptrToFun)(void));
void RTOS_deleteTask (u8 priority);
void RTOS_suspendTask(u8 priority);
void RTOS_resumeTask (u8 priority);


#endif /* RTOS_INTERFACE_H_ */