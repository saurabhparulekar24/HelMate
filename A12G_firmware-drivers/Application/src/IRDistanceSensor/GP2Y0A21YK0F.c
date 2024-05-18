/**
 * @file GP2Y0A21YK0F.c
 * @brief Implementation file for the GP2Y0A21YK0F IR Distance Sensor.
 *
 * This file provides the function definitions for initializing and reading data from
 * the GP2Y0A21YK0F infrared distance sensors used to detect objects on the left and right sides.
 *
 * @date Created: 19-04-2024 2.06.28 PM
 * @author Binh Nguyen
 */
#include "GP2Y0A21YK0F.h"

/**
 * @brief Initializes the IR sensors for input.
 * 
 * This function configures the GPIO pins connected to the IR sensors as input pins.
 * It ensures that the sensors are ready to report their status without any pull-up or pull-down,
 * allowing for accurate distance sensing.
 * 
 * @return uint32_t Returns 0 if initialization is successful, a non-zero error code otherwise.
 */
uint32_t InitIRSensor(void){

    uint32_t error = 0;
    struct port_config pin_conf;
	port_get_config_defaults(&pin_conf);

    pin_conf.direction  = PORT_PIN_DIR_INPUT;
    pin_conf.direction  = PORT_PIN_PULL_NONE;
	port_pin_set_config(LEFT_IR_SENSOR_PIN, &pin_conf);

    pin_conf.direction  = PORT_PIN_DIR_INPUT;
    pin_conf.direction  = PORT_PIN_PULL_NONE;
	port_pin_set_config(RIGHT_IR_SENSOR_PIN, &pin_conf);

    return error;
}

/**
 * @brief Reads the state of both the LEFT and RIGHT IR sensors.
 * 
 * This function updates the provided SensorData structure with the current states of the IR sensors.
 * It reads the input levels of the pins connected to the IR sensors, where a HIGH signal typically
 * indicates the presence of an object within the sensor's detection range.
 * 
 * @param sensor_data Pointer to a SensorData struct where the current states of the IR sensors will be stored.
 */
void read_sensor(struct SensorData *sensor_data){
    sensor_data->left_side = port_pin_get_input_level(LEFT_IR_SENSOR_PIN);
    sensor_data->right_side = port_pin_get_input_level(RIGHT_IR_SENSOR_PIN);
}
