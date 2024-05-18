/**
 * @file      main.c
 * @brief     Main application entry point
 * @author    Eduardo Garcia
 * @author    Nick M-G
 * @date      2022-04-14
 ******************************************************************************/

/****
 * Includes
 ******************************************************************************/
#include <errno.h>

#include "CliThread/CliThread.h"
#include "FreeRTOS.h"
#include "I2cDriver\I2cDriver.h"
#include "IMU\imu.h"
#include "Haptic\DRV2605.h"
#include "LED_Strip\APA102C_LED_Strip.h"
#include "IRDistanceSensor\GP2Y0A21YK0F.h"
#include "SerialConsole.h"
#include "setup_flags\setupFlags.h"
#include "WifiHandlerThread/WifiHandler.h"
#include "asf.h"
#include "driver/include/m2m_wifi.h"
#include "main.h"
#include "stdio_serial.h"
#include "LED_Task\led_task.h"
#include "AccelerometerTask\accelerometer_task.h"
#include "HapticTask\haptic_task.h"

/****
 * Defines and Types
 ******************************************************************************/
#define APP_TASK_ID 0 /**< @brief ID for the application task */
#define CLI_TASK_ID 1 /**< @brief ID for the command line interface task */

/****
 * Local Function Declaration
 ******************************************************************************/
void vApplicationIdleHook(void);
//!< Initial task used to initialize HW before other tasks are initialized
static void StartTasks(void);
void vApplicationDaemonTaskStartupHook(void);

void vApplicationStackOverflowHook(void);
void vApplicationMallocFailedHook(void);
void vApplicationTickHook(void);

/****
 * Variables
 ******************************************************************************/
static TaskHandle_t cliTaskHandle = NULL;      //!< CLI task handle
static TaskHandle_t daemonTaskHandle = NULL;   //!< Daemon task handle
static TaskHandle_t wifiTaskHandle = NULL;     //!< Wifi task handle
static TaskHandle_t accelerometerTaskHandle = NULL;       //!< UI task handle
static TaskHandle_t controlTaskHandle = NULL;  //!< Control task handle
static TaskHandle_t LEDTaskHandle = NULL;  //!< Control task handle
static TaskHandle_t HapticTaskHandle = NULL;  //!< Control task handle

char bufferPrint[64];  ///< Buffer for daemon task

/**
 * @brief Main application function.
 * Application entry point.
 * @return int
 */
int main(void)
{
    /* Initialize the board. */
    system_init();

    /* Initialize the UART console. */
    InitializeSerialConsole();

    // Initialize trace capabilities
    vTraceEnable(TRC_START);
    // Start FreeRTOS scheduler
    vTaskStartScheduler();

    return 0;  // Will not get here
}

/**
 * function          vApplicationDaemonTaskStartupHook
 * @brief            Initialization code for all subsystems that require FreeRToS
 * @details			This function is called from the FreeRToS timer task. Any code
 *					here will be called before other tasks are initilized.
 * @param[in]        None
 * @return           None
 */
void vApplicationDaemonTaskStartupHook(void)
{
    SerialConsoleWriteString("\r\n\r\n-----ESE516 Main Program-----\r\n");

    // Initialize HW that needs FreeRTOS Initialization
    SerialConsoleWriteString("\r\n\r\nInitialize HW...\r\n");
    if (I2cInitializeDriver() != STATUS_OK) {
        SerialConsoleWriteString("Error initializing I2C Driver!\r\n");
    } else {
        SerialConsoleWriteString("Initialized I2C Driver!\r\n");
    }

    #if(IMU)
    // Initialize IMU HW
    uint8_t whoAmI = 0x00;
    get_device_id(GetImuStruct(), &whoAmI);
    if(whoAmI == device_ID){
        SerialConsoleWriteString("Found the Correct IMU\r\n");
        if(InitImu() == 0){
            SerialConsoleWriteString("Initialized IMU!\r\n");
        }
        else{
            SerialConsoleWriteString("Unable to Initialize IMU!!!\r\n");
        }
    }
    else{
        SerialConsoleWriteString("Could not find IMU!!!\r\n");
    }
    #endif

    #if(Haptic)
    uint8_t statusExpected = 0xE0;
    if(HapticreadStatusReg() == statusExpected){
        SerialConsoleWriteString("Found Haptic!!!\r\n");
        if(InitHaptic() == 0){
            SerialConsoleWriteString("Initialized Haptic!!!\r\n");
        }
    }
    else{
        SerialConsoleWriteString("Could not find Haptic!!!\r\n");
    }
    #endif

    //*******************************************************
    // LED Strip Initialization
    //*******************************************************
    #if(LED_Strip)
    if(InitLED() == 0){
        SerialConsoleWriteString("Initialized LED Strip!!!\r\n");
    }
    #endif

    //*******************************************************
    // IR Sensor Initialization
    //*******************************************************

    #if(IR_sensor)
    if(InitIRSensor() == 0){
        SerialConsoleWriteString("Initialized IR Sensor!!!\r\n");
    }
    #endif

    StartTasks();

    vTaskSuspend(daemonTaskHandle);
}

/**
 * function          StartTasks
 * @brief            Initialize application tasks
 * @details
 * @param[in]        None
 * @return           None
 */
static void StartTasks(void)
{
    snprintf(bufferPrint, 64, "Heap before starting tasks: %d\r\n", xPortGetFreeHeapSize());
    SerialConsoleWriteString(bufferPrint);

    // Initialize Tasks here

    if (xTaskCreate(vCommandConsoleTask, "CLI_TASK", CLI_TASK_SIZE, NULL, CLI_PRIORITY, &cliTaskHandle) != pdPASS) {
        SerialConsoleWriteString("ERR: CLI task could not be initialized!\r\n");
    }

    snprintf(bufferPrint, 64, "Heap after starting CLI: %d\r\n", xPortGetFreeHeapSize());
    SerialConsoleWriteString(bufferPrint);

    if (xTaskCreate(vWifiTask, "WIFI_TASK", WIFI_TASK_SIZE, NULL, WIFI_PRIORITY, &wifiTaskHandle) != pdPASS) {
        SerialConsoleWriteString("ERR: WIFI task could not be initialized!\r\n");
    }
    snprintf(bufferPrint, 64, "Heap after starting WIFI: %d\r\n", xPortGetFreeHeapSize());
    SerialConsoleWriteString(bufferPrint);

    #if(ACCELEROMETER_TASK)
    if (xTaskCreate(AccelerometerTask, "ACCELEROMETER_TASK", ACCELEROMETER_TASK_SIZE, NULL, ACCELEROMETER_TASK_PRIORITY, &accelerometerTaskHandle) != pdPASS) {
        SerialConsoleWriteString("ERR: Accelerometer task could not be initialized!\r\n");
    }
    snprintf(bufferPrint, 64, "Heap after starting Accelerometer: %d\r\n", xPortGetFreeHeapSize());
    SerialConsoleWriteString(bufferPrint);
    #endif

    #if(LED_TASK)
    // Create LED task from led_task.c
    if (xTaskCreate(LedTask, "LED_TASK", LED_TASK_SIZE, NULL, LED_PRIORITY, &LEDTaskHandle) != pdPASS) {
        SerialConsoleWriteString("ERR: LED task could not be initialized!\r\n");
    }
    snprintf(bufferPrint, 64, "Heap after starting LED: %d\r\n", xPortGetFreeHeapSize());
    SerialConsoleWriteString(bufferPrint);
    #endif

    #if(HAPTIC_TASK)
    // Create Haptic task from led_task.c
    if (xTaskCreate(HapticTask, "HAPTIC_TASK", HAPTIC_TASK_SIZE, NULL, HAPTIC_TASK_PRIORITY, &HapticTaskHandle) != pdPASS) {
        SerialConsoleWriteString("ERR: Haptic task could not be initialized!\r\n");
    }
    snprintf(bufferPrint, 64, "Heap after starting Haptic: %d\r\n", xPortGetFreeHeapSize());
    SerialConsoleWriteString(bufferPrint);
    #endif
}

void vApplicationMallocFailedHook(void)
{
    SerialConsoleWriteString("Error on memory allocation on FREERTOS!\r\n");
    while (1)
        ;
}

void vApplicationStackOverflowHook(void)
{
    SerialConsoleWriteString("Error on stack overflow on FREERTOS!\r\n");
    while (1)
        ;
}

#include "MCHP_ATWx.h"
void vApplicationTickHook(void)
{
    SysTick_Handler_MQTT();
}
