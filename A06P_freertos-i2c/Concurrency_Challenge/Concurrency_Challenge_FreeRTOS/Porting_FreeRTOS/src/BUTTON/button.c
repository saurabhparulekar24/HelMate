/**************************************************************************/ /**
 * @file      button.c
 * @brief     Code for BUTTON task of L2, ESE516 Example code
 * @author    Eduardo Garcia
 * @date      2020-01-01

 ******************************************************************************/

/******************************************************************************
 * Includes
 ******************************************************************************/
#include "FreeRTOS.h"
#include "button.h"
#include "asf.h"
#include "led.h"
#include "task.h"

/******************************************************************************
 * Defines
 ******************************************************************************/

/******************************************************************************
 * Variables
 ******************************************************************************/
// static buttonControlStates buttonState;
static uint32_t pressTime;      ///< Time button was pressed.
static bool buttonHeldActive;   ///< Flag that determines if we already sent a message to the LED task in the current <1 second press.
static uint32_t startTime;

/******************************************************************************
 * Forward Declarations
 ******************************************************************************/

/******************************************************************************
 * Callback Functions
 ******************************************************************************/

/**************************************************************************/ /**
 * @fn		void ButtonTask(void)
 * @brief	Initializes the button task. Only run once at the start! Assumes button has already been initialized.

 * @param[in] Void
 * @param[out] Void
 * @return Void
 * @note None
 *****************************************************************************/
void InitButtonTask(void) {
    startTime = xTaskGetTickCount();
    pressTime = 0;
}

/**************************************************************************/ /**
 * @fn		void ButtonTask(void)
 * @brief	Runs Button Task

 * @param[in] Void
 * @param[out] Void
 * @return Void
 * @note None
 *****************************************************************************/
void ButtonTask(int *flag) {
    bool buttonHeldActive = !(port_pin_get_input_level(BUTTON_0_PIN));
    if(buttonHeldActive){
            pressTime = xTaskGetTickCount() - startTime;
    }
    else{
        InitButtonTask();
    }
    if(pressTime>=BUTTON_PRESS_TIME_MS){
        *flag = 1;
        InitButtonTask();
    }
}
