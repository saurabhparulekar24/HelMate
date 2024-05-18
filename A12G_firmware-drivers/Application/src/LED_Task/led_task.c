/**
 * @file led_task.c
 * @brief LED control tasks for bike light system.
 *
 * Implements the functions for managing the LED behaviors based on bike mode states such as turning left,
 * turning right, or maintaining a solid red light. It interacts with the system's state machine and
 * LED hardware control libraries to adjust the LED outputs based on sensor inputs and system states.
 *
 * @date 26-04-2024
 * @author Saurabh Sandeep Parulekar
 */

#include "led_task.h"


static enum system_states current_state;        ///< Current operational state of the system.        
static enum direction_states bike_mode_state;   ///< Current direction state for the bike's LED indicators.
static enum lock_states lock_alert = ALERT_INACTIVE;  ///< Alert Theft during lock

/* Forward Declarations */
static void turn_indicator(enum direction_states state, LEDdev_ctx_t *led_ctx);
static void stop_signal(struct ImuDataPacket *imudata, LEDdev_ctx_t *led_ctx);
static void blink_red(LEDdev_ctx_t *led_ctx);
static uint8_t map(int x, int in_min, int in_max, int out_min, int out_max);     

/**
 * @brief Sets the current bike mode state.
 *
 * This function updates the global bike_mode_state to reflect changes such as
 * turning left, right, or requiring a solid light indication based on user inputs
 * or sensor data.
 *
 * @param state The new state to set for the bike's directional mode.
 */
void set_bike_mode_state_LED(enum direction_states state){
    bike_mode_state = state;
}

/**
 * @brief Sets the system's overall operational state.
 *
 * This function updates the global system state to manage different modes of
 * operation such as biking, locking, etc.
 *
 * @param state The new system state to set.
 */
void set_system_state_LED(enum system_states state){
    current_state = state;
}

/**
 * @brief Retrieves the current system state.
 * @return The current state of the system.
 */
enum system_states get_system_state_LED(){
    return current_state;
}

/**
 * @brief Retrieves the current bike mode state.
 * @return The current state of the bike's directional mode.
 */
enum direction_states get_bike_mode_state_LED(){
    return bike_mode_state;
}

/**
 * @brief Retrieves the current lock state.
 * @return The current state of the lock alert.
 */
enum lock_states get_lock_state(){
    return lock_alert;
}

/**
 * @brief Controls the turning indicators based on the current bike mode state.
 *
 * Activates LEDs for indicating turning left or right by toggling the respective side's LEDs.
 * This function ensures visibility and safety by managing directional signals.
 *
 * @param state The direction state (TURN_LEFT or TURN_RIGHT).
 * @param led_ctx Pointer to LED device context for controlling LED hardware.
 */
static void turn_indicator(enum direction_states state, LEDdev_ctx_t *led_ctx) {
    static bool led_state = true;
    if (state == TURN_LEFT || state == TURN_RIGHT) {
        int start = (state == TURN_LEFT) ? LEFT_LED_START : RIGHT_LED_START;
        int end = (state == TURN_LEFT) ? LEFT_LED_END : RIGHT_LED_END;
        int opposite_start = (state == TURN_LEFT) ? RIGHT_LED_START : LEFT_LED_START;
        int opposite_end = (state == TURN_LEFT) ? RIGHT_LED_END : LEFT_LED_END;

        // Clear opposite side LEDs
        for (int i = opposite_start; i <= opposite_end; i++) {
            setLEDColor_index(led_ctx, i, 0, 0, 0);
        }
        vTaskDelay(10);

        // Toggle active side LEDs
        for (int i = start; i <= end; i++) {
            setLEDColor_index(led_ctx, i, led_state ? 255 : 0, led_state ? 165 : 0, 0);
        }

        led_state = !led_state;
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

/**
 * @brief Controls the LEDs to display a solid red light.
 *
 * This function reads acceleration data from the IMU to determine if the bike is moving.
 * If the bike is slowing down, it displays a blinking red light to indicate stopping.
 *
 * @param imudata Pointer to ImuDataPacket containing acceleration data.
 * @param led_ctx Pointer to LED device context for controlling LED hardware.
 */
static void stop_signal(struct ImuDataPacket *imudata, LEDdev_ctx_t *led_ctx){
    if(imudata->zmg < -10){
        blink_red(led_ctx);
    }
    else{
        setLEDColor_all(led_ctx, 255, 0, 0);
    }
}

/**
 * @brief Makes the LEDs blink red to indicate a stopping signal.
 *
 * This function toggles LEDs to blink in red color, commonly used to signal stopping.
 * It uses a 250ms on-off cycle.
 *
 * @param led_ctx Pointer to LED device context for controlling LED hardware.
 */
static void blink_red(LEDdev_ctx_t *led_ctx){
    setLEDColor_all(led_ctx, 255, 0, 0);
    vTaskDelay(250 / portTICK_PERIOD_MS);
    setLEDColor_all(led_ctx, 0, 0, 0);
    vTaskDelay(250 / portTICK_PERIOD_MS);
}

/**
 * @brief Maps an integer from one range to another.
 *
 * This function is used for scaling values, such as mapping sensor readings to suitable LED brightness levels.
 *
 * @param x The value to map.
 * @param in_min The minimum of the input range.
 * @param in_max The maximum of the input range.
 * @param out_min The minimum of the output range.
 * @param out_max The maximum of the output range.
 * @return The mapped value.
 */
static uint8_t map(int x, int in_min, int in_max, int out_min, int out_max) {
    return (uint8_t)(((long long)(x - in_min) * (out_max - out_min)) / (in_max - in_min) + out_min);
}

/**
 * @brief Main task function for controlling LEDs based on bike mode.
 *
 * This function initializes the LED device, sets the initial system state, and
 * continuously checks and updates the LED states based on the current bike mode.
 */
void LedTask(void *pvParameters){
    // *********************************
    // Set the states of the system
    // *********************************
    uint8_t r_value, g_value, b_value;
    // static struct ImuDataPacket imudataVar = {.xmg=0,.ymg=0,.zmg=0};
    int16_t raw_acceleration_data[3];                                ///< Buffer for raw acceleration data
    struct ImuDataPacket imudataVar;                                         ///< Data packet for IMU data      
    uint8_t data_ready_flag;                                            ///< Flag to check if new IMU data is available
    vTaskDelay(100);
    stmdev_ctx_t *dev_ctx = GetImuStruct();                                 ///< IMU device context
    LEDdev_ctx_t *led_dev = GetLEDStruct();                   ///< LED device context for controlling LED hardware.
    LEDOff(led_dev);
    setLEDBrightness_all(led_dev, PER_BRIGHTNESS(LED_BRIGHTNESS));
    set_system_state_LED(MODE_BIKE);
    set_bike_mode_state_LED(STOPPING);
    
    while (1)
    {   
        data_ready_flag = 0;
        xl_flag_data_ready_get(dev_ctx, &data_ready_flag);
        if(data_ready_flag){
            memset(raw_acceleration_data, 0x00, 3 * sizeof(int16_t));
            acceleration_raw_get(dev_ctx, raw_acceleration_data);
            imudataVar.xmg = (int16_t)from_fs2_to_mg(raw_acceleration_data[0]);
            imudataVar.ymg = (int16_t)from_fs2_to_mg(raw_acceleration_data[1]);
            imudataVar.zmg = (int16_t)from_fs2_to_mg(raw_acceleration_data[2]);
            WifiAddImuDataToQueue(&imudataVar);
            // vTaskDelay(50);
        }
        switch (current_state)
        {
            case MODE_BIKE:
                lock_alert = ALERT_INACTIVE;
                if (bike_mode_state == STOPPING) {
                    stop_signal(&imudataVar, led_dev);
                }
                else{
                    turn_indicator(bike_mode_state, led_dev);
                }
                break;
            case MODE_LOCK:
                if(lock_alert==ALERT_ACTIVE){
                    blink_red(led_dev);
                }
                else if(imudataVar.xmg > LOCK_THRESHOLD || imudataVar.ymg > LOCK_THRESHOLD || imudataVar.zmg > LOCK_THRESHOLD){
                    lock_alert = ALERT_ACTIVE;
                }
                else{
                    LEDOff(led_dev);
                }
                break;
            case MODE_FUN:
                lock_alert = ALERT_INACTIVE;
                r_value = map(imudataVar.xmg, IMU_MIN, IMU_MAX, LED_MIN, LED_MAX);
                g_value = map(imudataVar.ymg, IMU_MIN, IMU_MAX, LED_MIN, LED_MAX);
                b_value = map(imudataVar.zmg, IMU_MIN, IMU_MAX, LED_MIN, LED_MAX);
                setLEDColor_all(led_dev, r_value, g_value, b_value);
                vTaskDelay(10);
                break;
            default:
                break;
        }
    }
    
}

