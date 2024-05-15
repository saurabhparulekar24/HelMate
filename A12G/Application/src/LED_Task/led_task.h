/**
 * @file led_task.h
 * @brief Header file for LED control tasks.
 *
 * This file contains definitions and declarations for controlling LEDs based on system states and sensor inputs.
 * It includes configurations for task size, priority, and LED brightness, along with functional interfaces
 * to set or get system states, and specific functions for LED manipulation.
 *
 * @date Created: 26-04-2024 11.18.46 AM
 * @author Saurabh Sandeep Parulekar
 */


#ifndef LED_TASK_H_
#define LED_TASK_H_

#include "LED_Strip\APA102C_LED_Strip.h"
#include "WifiHandlerThread\WifiHandler.h"
#include "AccelerometerTask\accelerometer_task.h"

/**
 * @brief Stack size for the LED control task.
 */
#define LED_TASK_SIZE 500

/**
 * @brief Priority for the LED control task.
 */
#define LED_PRIORITY (configMAX_PRIORITIES - 3)

/**
 * @brief Default brightness level for LEDs.
 */
#define LED_BRIGHTNESS 10

/**
 * @brief Axis index used for forward direction in accelerometer readings.
 *
 * 0: Z-axis, 1: X-axis, 2: Y-axis
 */
#define FORWARD_DIRECTION 0

/**
 * @brief Threshold value for locking mechanism triggers.
 */
#define LOCK_THRESHOLD 1100

/**
 * @enum imu_led_resolution
 * @brief Resolution settings for mapping IMU readings to LED brightness values.
 */
enum imu_led_resolution{
   IMU_MAX = 2048,
   IMU_MIN = -2048,
   LED_MAX = 255,
   LED_MIN = 0
};

/**
 * @enum led_positions
 * @brief LED positions on the strip for different lighting areas.
 */
enum led_positions{
   LEFT_LED_START = 0,
   LEFT_LED_END = 2,
   RIGHT_LED_START = 7,
   RIGHT_LED_END = 9,
   CENTER_LED_START = 3,
   CENTER_LED_END = 6
};


void LedTask(void *pvParameters);
void set_bike_mode_state_LED(enum direction_states state);
void set_system_state_LED(enum system_states state);
enum lock_states get_lock_state();
enum direction_states get_bike_mode_state_LED();
enum system_states get_system_state_LED();
enum lock_states get_lock_state();

#endif /* LED_TASK_H_ */
