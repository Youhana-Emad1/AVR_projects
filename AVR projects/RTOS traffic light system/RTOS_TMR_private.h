/*
 * RTOS_TMR_private.h
 *
 * Created: 2/3/2024 9:36:34 AM
 *  Author: Kareem Hussein
 */ 


#ifndef RTOS_TMR_PRIVATE_H_
#define RTOS_TMR_PRIVATE_H_


										/* TIMER2 REGISTERS*/
								 
// Timer/Counter Control Register
#define TCCR2            (*(volatile u8*)0x45)
#define CS20             0
#define CS21             1
#define CS22             2
#define WGM21            3
#define COM20            4
#define COM21            5
#define WGM20            6
#define FOC2             7

// Timer/Counter Register
#define TCNT2            (*(volatile u8*)0x44)

// Output Compare Register
#define OCR2             (*(volatile u8*)0x43)

// Timer/Counter Interrupt Mask Register
#define TIMSK            (*(volatile u8*)0x59)
#define TOIE2            6
#define OCIE2            7

// Timer/Counter Interrupt Flag Register
#define TIFR             (*(volatile u8*)0x58)
#define TOV2             6
#define OCF2             7


#endif /* RTOS_TMR_PRIVATE_H_ */