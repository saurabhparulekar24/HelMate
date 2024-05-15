/**
 * @file haptic_task.h
 * @brief Header for haptic feedback task management.
 *
 * This header defines the interfaces and configurations for the haptic task in an embedded system,
 * managing haptic feedback based on system state and sensor inputs. It includes integration with
 * the DRV2605 haptic driver, LED task, state machine logic, and IR distance sensor.
 *
 * @date Created: 27th April 2024
 * @author Binh Nguyen
 */
#ifndef HAPTIC_TASK_H_
#define HAPTIC_TASK_H_

// Include the haptic driver header file. Replace "haptic_driver.h" with the actual file name.
#include "Haptic\DRV2605.h"
#include "LED_Task\led_task.h"
#include "State_Machine\state_machine.h"
#include "IRDistanceSensor\GP2Y0A21YK0F.h"
#include "asf.h"

/** @def HAPTIC_TASK_SIZE
 * @brief Stack size for the haptic task.
 *
 * This defines the stack size to allocate for the haptic task. Increasing this size
 * might be necessary if the task's function calls consume more stack space.
 */
#define HAPTIC_TASK_SIZE 200

/** @def HAPTIC_TASK_PRIORITY
 * @brief Task priority for the haptic task.
 *
 * This macro sets the priority of the haptic task to one less than the system's maximum
 * priority to ensure it remains responsive while allowing higher priority tasks to preempt.
 */
#define HAPTIC_TASK_PRIORITY (configMAX_PRIORITIES - 1)

/**
 * @enum haptic_states
 * @brief Enumerates the possible states for the haptic feedback task.
 *
 * Defines various states that the haptic task can be in, which influence the type of
 * feedback provided to the user.
 */
enum haptic_states
{
  HAPTIC_STOP,
  HAPTIC_LEFT,
  HAPTIC_RIGHT
};

void HapticTask(void *pvParameters);

#endif // HAPTIC_TASK_H
