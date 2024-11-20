/*
 * RTOS_TMR_interface.h
 *
 * Created: 2/3/2024 9:36:13 AM
 *  Author: Kareem Hussein
 */ 


#ifndef RTOS_TMR_INTERFACE_H_
#define RTOS_TMR_INTERFACE_H_


void RTOS_TMR_init                (void);
void RTOS_TMR_start               (void);
void RTOS_TMR_stop                (void);
void RTOS_TMR_setCompareMatchValue(u8 compareValue);
void RTOS_TMR_setCallBackCTC      (void(*ptrToFun)(void));


#endif /* RTOS_TMR_INTERFACE_H_ */