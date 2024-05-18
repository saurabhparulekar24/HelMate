/**
 * @file haptic_task.c
 * @brief Implementation of haptic feedback task functions.
 *
 * This source file contains the functions necessary to control haptic feedback based on
 * sensor data and system state in an embedded system. Functions are designed to operate
 * within a real-time operating system (RTOS) environment.
 * @author Binh Nguyen
 */

#include "haptic_task.h"

/**
 * @brief Selects the haptic direction and applies an optional delay.
 *
 * This function triggers a directional haptic feedback and optionally delays further
 * execution to allow the haptic effect to complete.
 *
 * @param dir The direction of the haptic feedback (LEFT or RIGHT).
 * @param delay If set to 1, delays the task after triggering the haptic feedback.
 */
static void select_dir(enum direction dir, uint8_t delay){
    HapticGo_dir(dir);
    if(delay == 1){
    vTaskDelay(3000);
    }

}

/**
 * @brief Controls the vibration motor based on sensor data and direction.
 *
 * This function decides the haptic feedback pattern based on the proximity sensor data
 * and the direction indicated by the navigation logic.
 *
 * @param data Pointer to SensorData structure containing sensor states.
 * @param dir Direction of the turn indicated by the navigation system (TURN_LEFT or TURN_RIGHT).
 */
static void haptic_vibrate(struct SensorData *data, enum direction_states dir){
    if(dir == TURN_LEFT){
        if(data->left_side){
            select_dir(LEFT, 0);
        }
        else{
            select_dir(LEFT, 1);
        }
    }
    else if(dir == TURN_RIGHT){
        if(data->right_side){
            select_dir(RIGHT, 0);
        }
        else{
            select_dir(RIGHT, 1);
        }
    }
}

/**
 * @brief Main task for handling haptic feedback based on system states and sensor inputs.
 *
 * This task continuously monitors the system state and sensor readings, triggering haptic
 * feedback accordingly. It supports multiple operational modes and ensures that the
 * appropriate haptic feedback is provided in real-time.
 *
 * @param pvParameters Pointer to parameters passed to the task at creation time, typically unused.
 */
void HapticTask(void *pvParameters){
    enum system_states system_state_haptic;
    enum direction_states bike_mode_state; // States Object on the right or left
    enum lock_states alert_state;
    hapdev_ctx_t *hap_dev = GetHapStruct();
    struct SensorData ir_sensor_state;
    while(1){
        system_state_haptic = get_system_state_LED();
        bike_mode_state = get_bike_mode_state_LED();
        read_sensor(&ir_sensor_state);
        switch (system_state_haptic)
        {
            case MODE_BIKE:
                if(bike_mode_state !=STOPPING){
                haptic_vibrate(&ir_sensor_state, bike_mode_state);
                }
                break;
            case MODE_LOCK:
                alert_state = get_lock_state();
                if(alert_state == ALERT_ACTIVE){
                ir_sensor_state.left_side = 1;
                ir_sensor_state.right_side = 1;
                haptic_vibrate(&ir_sensor_state, TURN_LEFT);
                haptic_vibrate(&ir_sensor_state, TURN_RIGHT);
                }
            default:
                break;
        }
        vTaskDelay(200);
    }
}

