/**
 * @file setupFlags.h
 * @brief Header file to setup configuration flags for system peripherals.
 *
 * This header file contains macro definitions that configure the presence
 * of various peripherals in the system. Each macro indicates whether a specific
 * peripheral is included in the system build (1 for included, 0 for excluded).
 *
 * @date 12-04-2024
 * @author Saurabh Sandeep Parulekar
 */

#ifndef SETUPFLAGS_H_
#define SETUPFLAGS_H_

/** @brief Enable or disable the Inertial Measurement Unit (IMU).
 *  @details Set to 1 to include the IMU, or 0 to exclude it from the system build.
 */
#define IMU 1   

/** @brief Enable or disable the LED Strip.
 *  @details Set to 1 to include the LED Strip, or 0 to exclude it from the system build.
 */
#define LED_Strip 1

/** @brief Enable or disable the IR sensor.
 *  @details Set to 1 to include the IR sensor, or 0 to exclude it from the system build.
 */
#define IR_sensor 1

/** @brief Enable or disable the Haptic feedback mechanism.
 *  @details Set to 1 to include Haptic feedback, or 0 to exclude it from the system build.
 */
#define Haptic 1

/** @brief Enable or disable the Accelerometer Task.
 *  @details Set to 1 to include the Accelerometer Task, or 0 to exclude it from the system build.
 *  This task is responsible for handling accelerometer data.
 *  @NOTE: This task was initialized planned to use but, we had to take a different approach, 
 *          Kept it here incase we needed it
 */
#define ACCELEROMETER_TASK 0

/** @brief Enable or disable the LED Task.
 *  @details Set to 1 to include the LED Task, or 0 to exclude it from the system build.
 *  This task manages the LED operations based on system states.
 */
#define LED_TASK 1

/** @brief Enable or disable the Haptic Task.
 *  @details Set to 1 to include the Haptic Task, or 0 to exclude it from the system build.
 *  This task controls the haptic feedback mechanisms based on user interactions or alerts.
 */
#define HAPTIC_TASK 1

#endif /* SETUPFLAGS_H_ */
