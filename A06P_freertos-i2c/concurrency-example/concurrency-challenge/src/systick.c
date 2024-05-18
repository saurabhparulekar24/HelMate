/**************************************************************************//**
* @file      systick.c
* @brief     Code for systick
* @author    Eduardo Garcia
* @date      2020-01-01

******************************************************************************/


/******************************************************************************
* Includes
******************************************************************************/
#include "systick.h"
#include <asf.h>

/******************************************************************************
* Defines
******************************************************************************/

/******************************************************************************
* Variables
******************************************************************************/
volatile uint32_t ul_tickcount = 0; ///<Systick counter. Holds the current value of the systick. Use to measure relative time between events.


/******************************************************************************
* Forward Declarations
******************************************************************************/

/******************************************************************************
* Callback Functions
******************************************************************************/

/**************************************************************************/ /**
* function          void SysTick_Handler(void)
* @brief            Systick handler. Increases the systick counter.
*****************************************************************************/
void SysTick_Handler(void){
	
	ul_tickcount++;
}


/**************************************************************************/ /**
* function          static void SystickInit(void)
* @brief            Initializes the systick timer. Increases the systick every one (1) ms
*****************************************************************************/
void SystickInit(void)
{
		// Configure SysTick to trigger every millisecond using the CPU Clock
		SysTick->CTRL = 0;					// Disable SysTick
		SysTick->LOAD = 47999UL;				// Set reload register for 1mS interrupts - 48MHz Clock
		NVIC_SetPriority(SysTick_IRQn, 3);	// Set interrupt priority to least urgency
		SysTick->VAL = 0;					// Reset the SysTick counter value
		SysTick->CTRL = 0x00000007;			// Enable SysTick, Enable SysTick Exceptions, Use CPU Clock
		NVIC_EnableIRQ(SysTick_IRQn);		// Enable SysTick Interrupt
}

/**************************************************************************/ /**
* function          static void SystickInit(void)
* @brief            Initializes the systick timer. Increases the systick every one (1) ms
* @return			Returns the current systick.
*****************************************************************************/

uint32_t SystickGet(void)
{
	return ul_tickcount;
}