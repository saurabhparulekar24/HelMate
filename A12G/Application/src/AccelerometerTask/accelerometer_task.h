/*
 * accelerometer_task.h
 *
 * Created: 26-04-2024 4.50.44 PM
 *  Author: Saurabh
 */ 


#ifndef ACCELEROMETER_TASK_H_
#define ACCELEROMETER_TASK_H_

#include "IMU\imu.h"
#include "WifiHandlerThread\WifiHandler.h"
#include "SerialConsole\SerialConsole.h"
#include "asf.h"

#define ACCELEROMETER_TASK_SIZE 200
#define ACCELEROMETER_TASK_PRIORITY (configMAX_PRIORITIES - 4)

void AccelerometerTask(void *pvParameters);
void GetImuValue(struct ImuDataPacket *packet);



#endif /* ACCELEROMETER_TASK_H_ */