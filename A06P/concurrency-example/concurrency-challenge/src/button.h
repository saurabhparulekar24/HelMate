/**************************************************************************/ /**
 * @file      button.h
 * @brief     Code for BUTTON task of L2 Example of ESE516
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

#define BUTTON_PRESS_TIME_MS 1000   ///< Time, in ms, that a button must be pressed to count as a press.

//! Button state variable definition
typedef enum buttonControlStates {
    BUTTON_RELEASED,    ///< BUTTON IS RELEASED
    BUTTON_PRESSED,     ///< BUTTON IS PRESSED
    BUTTON_MAX_STATES   /// Max number of states.
} buttonControlStates;
/******************************************************************************
 * Structures and Enumerations
 ******************************************************************************/

/******************************************************************************
 * Global Function Declaration
 ******************************************************************************/
void InitButtonTask(void);
void ButtonTask(void);

#ifdef __cplusplus
}
#endif