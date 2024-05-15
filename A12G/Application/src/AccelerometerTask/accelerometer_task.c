/**
 * @file accelerometer_task.h
 * @brief Task for handling accelerometer data processing and transmission.
 * @author Saurabh Sandeep Parulekar
 */
#include "accelerometer_task.h"

/** 
 * @brief Queue handle data to LED strip.
 */
QueueHandle_t xQueueIMUBuffer = NULL;

/**
 * @brief Processes accelerometer data from IMU and sends it over a queue.
 * 
 * This task continuously reads the acceleration data from an IMU, converts it,
 * and sends it to a specified queue.
 * This task also sends data to a WiFi handler for further processing.
 * 
 * @param pvParameters Pointer to task parameters as passed during task creation.
 */
void AccelerometerTask(void *pvParameters){
    const TickType_t xDelay50ms = pdMS_TO_TICKS(50);
    static int16_t raw_acceleration_data[3];                                ///< Buffer for raw acceleration data
    struct ImuDataPacket imupacket;                                         ///< Data packet for IMU data      
    uint8_t data_ready_flag = 0;                                            ///< Flag to check if new IMU data is available
    vTaskDelay(100);
    stmdev_ctx_t *dev_ctx = GetImuStruct();                                 ///< IMU device context
    
    // Create the queue to hold 5 IMU data packets
    xQueueIMUBuffer = xQueueCreate(5, sizeof(struct ImuDataPacket));        
    if (xQueueIMUBuffer == NULL) {
         // Queue creation failed, exit the task
        SerialConsoleWriteString("Failed to Create Accelerometer Queue");
        return;
    }
    while(1){
        data_ready_flag = 0;
         // Check if new IMU data is available
        xl_flag_data_ready_get(dev_ctx, &data_ready_flag);
        if(data_ready_flag){
            memset(raw_acceleration_data, 0x00, 3 * sizeof(int16_t));
            acceleration_raw_get(dev_ctx, raw_acceleration_data);
            imupacket.xmg = (int16_t)from_fs2_to_mg(raw_acceleration_data[0]);
            imupacket.ymg = (int16_t)from_fs2_to_mg(raw_acceleration_data[1]);
            imupacket.zmg = (int16_t)from_fs2_to_mg(raw_acceleration_data[2]);
            xQueueSend(xQueueIMUBuffer, &imupacket, (TickType_t)10);
            WifiAddImuDataToQueue(&imupacket);
        }
        vTaskDelay(xDelay50ms);

    }
}


void GetImuValue(struct ImuDataPacket *packet){
    if(xQueueReceive(xQueueIMUBuffer, packet, 10)!=pdTRUE){
        SerialConsoleWriteString("Issue with adding to queue");
    }
}