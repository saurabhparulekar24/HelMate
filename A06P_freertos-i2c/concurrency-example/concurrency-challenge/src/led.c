/**************************************************************************//**
* @file      led.c
* @brief     Code for LED task of L2, ESE516 Example code
* @author    Eduardo Garcia
* @date      2020-01-01

******************************************************************************/


/******************************************************************************
* Includes
******************************************************************************/
#include "led.h"
#include <asf.h>
#include "systick.h"

/******************************************************************************
* Defines
******************************************************************************/

/******************************************************************************
* Variables
******************************************************************************/
static ledFrequencies currentFrequency; ///<Current frequency state
static ledControlState ledState;		///<Current LED state
static bool receivedButtonMessage;		///<Flag that says if we received a button event. TRUE if we did, false if not.
uint32_t initialTime;					///<Holds the systick time when the last ON/OFF state occurred.
uint32_t targetDeltaTime;				///<Holds the target time of the current ON/OFF stage

/******************************************************************************
* Forward Declarations
******************************************************************************/
static ledFrequencies LedGetNextFrequency(ledFrequencies freq);
/******************************************************************************
* Callback Functions
******************************************************************************/


/**************************************************************************//**
* @fn		void InitLedTask(void)
* @brief	Initializes the LED task. Only run once at the start!
                				
* @param[in]	
* @param[out]	
* @return		
* @note         
*****************************************************************************/
void InitLedTask(void)
{
	ledState = LED_INIT_STATE; //Initial state
	currentFrequency = LED_FREQ_1; //Initialize on first frequency
	receivedButtonMessage = false; //Button message not received
}


/**************************************************************************//**
* @fn		void LedTask(void)
* @brief	Runs the LED TASK
                				
* @param[in]	
* @param[out]	
* @return		
* @note         
*****************************************************************************/
void LedTask(void)
{
	
	//Special case before checking state: If we receive a button message,
	//we update the frequency to the next one and overwrite the state to LED_INIT_STATE
	if(receivedButtonMessage == true)
	{
		currentFrequency = LedGetNextFrequency(currentFrequency); //Update frequency used
		ledState = LED_INIT_STATE;
		receivedButtonMessage = false; //Clear flag
	}
	//Do code depending on the current state of the LED task
	
	switch(ledState)
	{
		//In this state,we get the target ON/OFF time based on the current frequency and the start time.
		case(LED_INIT_STATE):
		{
			initialTime = SystickGet(); //Set initial time
			targetDeltaTime = GetLedTargetTime(currentFrequency); //Gets the target time based on currentFrequency
			ledState = LED_ON_STATE; //Go to ON state on next pass
			break;
		}
		
		//In this state, we turn the LED on and count time. If the current time is bigger than the ON/OFF time, we go to OFF state
		case(LED_ON_STATE):
		{
			port_pin_set_output_level(LED_0_PIN, false); //Turn LED ON
			if(SystickGet() - initialTime >= targetDeltaTime)
			{
				initialTime = SystickGet();
				ledState = LED_OFF_STATE; //Go to OFF state on next pass
			}			
			break;
		}
		
		//In this state, we turn the LED off and count time. If the current time is bigger than the ON/OFF time, we go to ON state
		case(LED_OFF_STATE):
		{
			port_pin_set_output_level(LED_0_PIN, true); //Turn LED Off
			if(SystickGet() - initialTime >= targetDeltaTime)
			{
				initialTime = SystickGet();
				ledState = LED_ON_STATE; //Go to OFF state on next pass
			}
			break;
		}
		
		default:
		//invalid state: return to INIT state
		ledState = LED_INIT_STATE;
		break;
	}
}


/**************************************************************************//**
* @fn		uint32_t GetLedTargetTime(ledFrequencies freq)
* @brief	Gets the time an LED should be on, in ms, given a frequency.
                				
* @param[in]	freq Frequency enum to get a time for
* @param[out]	
* @return		Returns a time, in ms, that the device should be working for.
* @note         
*****************************************************************************/
uint32_t GetLedTargetTime(ledFrequencies freq)
{
	switch(freq)
	{
		case LED_FREQ_1:
			return LED_ONOFF_TIME_2000MS;
		break;
		
		case LED_FREQ_2:
			return LED_ONOFF_TIME_1000MS;
		break;
		
		case LED_FREQ_3:
			return LED_ONOFF_TIME_500MS;
		break;
		
		default:
			return LED_ONOFF_TIME_2000MS;
		break;
	}
}



/**************************************************************************//**
* @fn		void LedSetChange(void)
* @brief	Sets the flag to change frequency to TRUE
*****************************************************************************/
void LedSetChange(void)
{
	receivedButtonMessage = true;
}


/**************************************************************************//**
* @fn		static ledFrequencies LedGetNextFrequency(ledFrequencies freq)
* @brief	Given a frequency, gets the next frequency.
                				
* @param[in]	freq Frequency enum to get a time for
* @param[out]	
* @return		Returns a time, in ms, that the device should be working for.
* @note         
*****************************************************************************/
static ledFrequencies LedGetNextFrequency(ledFrequencies freq)
{
	switch(freq)
	{
		case LED_FREQ_1:
			return LED_FREQ_2;
		break;
		
		case LED_FREQ_2:
			return LED_FREQ_3;
		break;
		
		case LED_FREQ_3:
			return LED_FREQ_1;
		break;
		
		default:
			return LED_ONOFF_TIME_2000MS;
		break;
	}
}