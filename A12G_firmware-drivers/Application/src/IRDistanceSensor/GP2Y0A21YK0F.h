/**
 * @file GP2Y0A21YK0F.h
 * @brief Header file for the GP2Y0A21YK0F IR Distance Sensor.
 *
 * This file contains definitions and function declarations for interfacing
 * with the GP2Y0A21YK0F infrared distance sensor. It defines sensor pin configurations,
 * data structures for sensor data, and initialization and reading functions.
 *
 * @date Created: 19-04-2024 2.06.40 PM
 * @author Binh Nguyen
 */


#ifndef GP2Y0A21YK0F_H_
#define GP2Y0A21YK0F_H_

#include "asf.h"

/**
 * @brief Pin configuration for the left and right IR sensor.
 */
#define LEFT_IR_SENSOR_PIN PIN_PA06
#define RIGHT_IR_SENSOR_PIN PIN_PA05

/**
 * @enum sensor_location
 * @brief Enumerates the possible locations for sensors on the device.
 */
enum sensor_location{
    LEFT_SENSOR,
    RIGHT_SENSOR
};

/**
 * @struct SensorData
 * @brief Structure to store the state of sensors.
 *
 * This structure holds the boolean status of whether the left or right side
 * is detected by the corresponding sensors.
 */
struct SensorData {   
  bool left_side;        
  bool right_side;     
}; 

uint32_t InitIRSensor(void);
void read_sensor(struct SensorData *sensor_data);

#endif /* GP2Y0A21YK0F_H_ */
