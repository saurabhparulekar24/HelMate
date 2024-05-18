/**************************************************************************/ /**
 * @file      button.c
 * @brief     Code for BUTTON task of L2, ESE516 Example code
 * @author    Eduardo Garcia
 * @date      2020-01-01

 ******************************************************************************/

/******************************************************************************
 * Includes
 ******************************************************************************/
#include "button.h"
#include "asf.h"
#include "led.h"
#include "systick.h"

/******************************************************************************
 * Defines
 ******************************************************************************/

/******************************************************************************
 * Variables
 ******************************************************************************/
static buttonControlStates buttonState;
static uint32_t pressTime;      ///< Time button was pressed.
static bool buttonHeldActive;   ///< Flag that determines if we already sent a message to the LED task in the current <1 second press.

/******************************************************************************
 * Forward Declarations
 ******************************************************************************/

/******************************************************************************
 * Callback Functions
 ******************************************************************************/

/**************************************************************************/ /**
 * @fn		void ButtonTask(void)
 * @brief	Initializes the button task. Only run once at the start! Assumes button has already been initialized.

 * @param[in]
 * @param[out]
 * @return
 * @note
 *****************************************************************************/
void InitButtonTask(void) {}

/**************************************************************************/ /**
 * @fn		void LedTask(void)
 * @brief	Runs the LED TASK

 * @param[in]
 * @param[out]
 * @return
 * @note
 *****************************************************************************/
void ButtonTask(void) {}