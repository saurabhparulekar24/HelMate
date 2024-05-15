/**************************************************************************//**
* @file      led.h
* @brief     Code for LED task of L2 Example of ESE516
* @author    Eduardo Garcia
* @date      2020-01-01

******************************************************************************/

#pragma once
#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
* Includes
******************************************************************************/
#include <asf.h>
/******************************************************************************
* Defines
******************************************************************************/

#define LED_ONOFF_TIME_2000MS	2000UL/portTICK_PERIOD_MS	//Time, in ms, of an LED being ON/OFF for it to blink at 0.25Hz
#define LED_ONOFF_TIME_1000MS	1000/portTICK_PERIOD_MS	//Time, in ms, of an LED being ON/OFF for it to blink at 0.5Hz
#define LED_ONOFF_TIME_500MS	500/portTICK_PERIOD_MS		//Time, in ms, of an LED being ON/OFF for it to blink at 1Hz


//! LED state variable definition
typedef enum ledControlState
{
	LED_INIT_STATE, ///<Describes the LED initial state
	LED_ON_STATE, ///<LED is ON
	LED_OFF_STATE, ///LED is OFF
	LED_MAX_STATES ///Max number of states.
}ledControlState;

//! Possible frequencies of LEDs
typedef enum ledFrequencies
{
	LED_FREQ_1, ///<LED Frequency 1
	LED_FREQ_2, ///<LED Frequency 2
	LED_FREQ_3, ///LED Frequency 3
	LED_MAX_FREQ_NUM ///Max number of frequences allowed.
}ledFrequencies;

/******************************************************************************
* Structures and Enumerations
******************************************************************************/



/******************************************************************************
* Global Function Declaration
******************************************************************************/
uint32_t GetLedTargetTime(ledFrequencies freq);
void LedTask(void);
void InitLedTask(void);
void LedSetChange(void);

#ifdef __cplusplus
}
#endif