/**
 * @file state_machine.h
 * @brief Header file for system state definitions.
 *
 * This file defines the various states used by the system's state machine, including general
 * system states, direction states for navigation, and lock states for security features.
 * These states help in managing the behavior of the system under different operating conditions.
 *
 * @date Created: 26-04-2024 11.17.06 AM
 * @author Saurabh Sandeep Parulekar
 */


#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_

/**
 * @enum system_states
 * @brief Defines possible states of the overall system.
 *
 * Enumerates the different modes the system can be in, affecting how other components like
 * LEDs and sensors behave.
 */
enum system_states{
	MODE_BIKE,
	MODE_LOCK,
	MODE_FUN
	};

/**
 * @enum direction_states
 * @brief Defines possible directional states for navigation-related tasks.
 *
 * Enumerates the directions relevant to biking, such as turning left or right, which can
 * be used to trigger specific actions like LED signaling.
 */
enum direction_states{
	TURN_LEFT,
	TURN_RIGHT,
	STOPPING
};

/**
 * @enum lock_states
 * @brief Defines lock states for the security system of the bike.
 *
 * Enumerates the possible states of the locking mechanism's alert system, which can indicate
 * whether the security system is active or has been triggered.
 */
enum lock_states{
	ALERT_INACTIVE,
	ALERT_ACTIVE
};


#endif /* STATE_MACHINE_H_ */
