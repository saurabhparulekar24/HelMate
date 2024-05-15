/**************************************************************************/ /**
 * @file      WifiHandler.h
 * @brief     File to handle HTTP Download and MQTT support
 * @author    Eduardo Garcia
 * @date      2020-01-01

 ******************************************************************************/

// #pragma once
#ifndef WIFI_TASK_H_
#define WIFI_TASK_H_

#pragma once
#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 * Includes
 ******************************************************************************/
#include "MQTTClient/Wrapper/mqtt.h"
#include "SerialConsole.h"
#include "asf.h"
#include "driver/include/m2m_wifi.h"
#include "iot/http/http_client.h"
#include "main.h"
// #include "secret.h"  // NOTE: You must make this file and include your Wi-Fi settings
#include "socket/include/socket.h"
#include "stdio_serial.h"
#include "Haptic\DRV2605.h"
#include "State_Machine\state_machine.h"
#include "LED_Task\led_task.h"
#include "IRDistanceSensor\GP2Y0A21YK0F.h"

/******************************************************************************
 * Defines
 ******************************************************************************/

#define WIFI_MQTT_INIT 0        ///< State for Wifi handler to Initialize MQTT Connection
#define WIFI_MQTT_HANDLE 1      ///< State for Wifi handler to Handle MQTT Connection
#define WIFI_DOWNLOAD_INIT 2    ///< State for Wifi handler to Initialize Download Connection
#define WIFI_DOWNLOAD_HANDLE 3  ///< State for Wifi handler to Handle Download Connection

#define WIFI_TASK_SIZE 1050
#define WIFI_PRIORITY (configMAX_PRIORITIES - 2)

/** Wi-Fi AP Settings. */
// Note: It is highly recommended that you save your Wi-Fi details in a separate header file, "secret.h", which is not committed to Github (added to gitignore).
#ifndef SECRET_H_
#define MAIN_WLAN_SSID "AirPennNet-Device"           /**< Destination SSID. Change to your WIFI SSID */
#define MAIN_WLAN_AUTH M2M_WIFI_SEC_WPA_PSK /**< Security manner */
#define MAIN_WLAN_PSK "penn1740wifi"      /**< Password for Destination SSID. Change to your password. Please dont hack my WiFi router */
#endif                                      /* SECRET_H_ */

/** IP address parsing. */
#define IPV4_BYTE(val, index) ((val >> (index * 8)) & 0xFF)

/** Content URI for download. */
#define MAIN_HTTP_FILE_URL "http://172.191.242.245/Application_New.bin"  ///< Change me to the URL to download your OTAU binary file from!

/** Maximum size for packet buffer. */
#define MAIN_BUFFER_MAX_SIZE (512)
/** Maximum file name length. */
#define MAIN_MAX_FILE_NAME_LENGTH (64)
/** Maximum file extension length. */
#define MAIN_MAX_FILE_EXT_LENGTH (8)
/** Output format with '0'. */
#define MAIN_ZERO_FMT(SZ) (SZ == 4) ? "%04d" : (SZ == 3) ? "%03d" : (SZ == 2) ? "%02d" : "%d"
#define FIRMWARE_VERSION "0.0.1"  ///< Firmware Version

typedef enum {
    NOT_READY = 0,         /*!< Not ready. */
    STORAGE_READY = 0x01,  /*!< Storage is ready. */
    WIFI_CONNECTED = 0x02, /*!< Wi-Fi is connected. */
    GET_REQUESTED = 0x04,  /*!< GET request is sent. */
    DOWNLOADING = 0x08,    /*!< Running to download. */
    COMPLETED = 0x10,      /*!< Download completed. */
    CANCELED = 0x20        /*!< Download canceled. */
} download_state;

// Structure definition that holds IMU data
struct ImuDataPacket {
    int16_t xmg;
    int16_t ymg;
    int16_t zmg;
};

// Structure to hold a game packet
// struct GameDataPacket {
//     uint8_t game[GAME_SIZE];
// };

// Structure to hold an RGB LED Color packet
// struct RgbColorPacket {
//     uint8_t red;
//     uint8_t green;
//     uint8_t blue;
// };

/* Max size of UART buffer. */  
#define MAIN_CHAT_BUFFER_SIZE 64

/* Max size of MQTT buffer. */
#define MAIN_MQTT_BUFFER_SIZE 512

/* Limitation of user name. */
// #define MAIN_CHAT_USER_NAME_SIZE 64

#define PLAYER1 1  ///< Comment me to compile for player 2. Uncomment me to define for player 1.

#ifdef PLAYER1
/* Chat MQTT topic. */
#define LED_TOPIC "P1_LED_ESE516_T0"                  // Students to change to an unique identifier for each device! LED Data
// #define GAME_TOPIC_IN "P1_GAME_ESE516_T0"             // Students to change to an unique identifier for each device! Game Data
// #define GAME_TOPIC_OUT "P2_GAME_ESE516_T0"            // Students to change to an unique identifier for each device! Game Data
#define IMU_TOPIC "HELMATE_IMU_TOPIC_5160"                  // Students to change to an unique identifier for each device! IMU Data
// #define DISTANCE_TOPIC "P1_DISTANCE_ESE516_T0"        // Students to change to an unique identifier for each device! Distance Data
// #define TEMPERATURE_TOPIC "P1_TEMPERATURE_ESE516_T0"  // Students to change to an unique identifier for each device! Distance Data
#define LOCK_STATE_TOPIC "LOCK_STATE_ESE516_T0"  // Students to change to an unique identifier for each device! Distance Data
#define SYSTEM_STATE_TOPIC "SYSTEM_STATE_ESE516_T0"  // Students to change to an unique identifier for each device! Distance Data
#define IR_STATE_TOPIC "IR_STATE_ESE516_T0"  // Students to change to an unique identifier for each device! Distance Data
#define FW_STATE_TOPIC "FW_STATE_ESE516_T0"  // Students to change to an unique identifier for each device! Distance Data
#define RESET_TOPIC "RESET_STATE_ESE516_T0"  // Students to change to an unique identifier for each device! Distance Data
#define VERSION_TOPIC "VERSION_STATE_ESE516_T0"  // Students to change to an unique identifier for each device! Distance Data

#else
/* Chat MQTT topic. */
#define LED_TOPIC "P2_LED_ESE516_T0"                  // Students to change to an unique identifier for each device! LED Data
#define GAME_TOPIC_IN "P2_GAME_ESE516_T0"             // Students to change to an unique identifier for each device! Game Data
#define GAME_TOPIC_OUT "P1_GAME_ESE516_T0"            // Students to change to an unique identifier for each device! Game Data
#define IMU_TOPIC "P2_IMU_ESE516_T0"                  // Students to change to an unique identifier for each device! IMU Data
#define DISTANCE_TOPIC "P2_DISTANCE_ESE516_T0"        // Students to change to an unique identifier for each device! Distance Data
#define TEMPERATURE_TOPIC "P2_TEMPERATURE_ESE516_T0"  // Students to change to an unique identifier for each device! Distance Data

#endif

// #define LED_TOPIC_LED_OFF "false"
// #define LED_TOPIC_LED_ON "true"

// Cloud MQTT User
#define CLOUDMQTT_USER_ID "DataRacers"

// Cloud MQTT PASSWORD
#define CLOUDMQTT_USER_PASSWORD "ese5160s24@dataracers"

#define CLOUDMQTT_PORT 1883

/*
 * A MQTT broker server which was connected.
 * m2m.eclipse.org is public MQTT broker.
 */
// http://52.242.73.67/
static const char main_mqtt_broker[] = "172.191.242.245"; 

#define STRING_EOL "\r\n"
#define STRING_HEADER                                                                 \
    "-- HTTP file downloader example --" STRING_EOL "-- " BOARD_NAME " --" STRING_EOL \
    "-- Compiled: "__DATE__                                                           \
    " "__TIME__                                                                       \
    " --" STRING_EOL

/******************************************************************************
 * Structures and Enumerations
 ******************************************************************************/

/******************************************************************************
 * Global Function Declaration
 ******************************************************************************/
void vWifiTask(void *pvParameters);
void init_storage(void);
void WifiHandlerSetState(uint8_t state);
// int WifiAddDistanceDataToQueue(uint16_t *distance);
int WifiAddImuDataToQueue(struct ImuDataPacket *imuPacket);
// int WifiAddGameDataToQueue(struct GameDataPacket *game);
void SubscribeHandlerLedTopic(MessageData *msgData);
// void SubscribeHandlerGameTopic(MessageData *msgData);
// void SubscribeHandlerImuTopic(MessageData *msgData);
// void SubscribeHandlerDistanceTopic(MessageData *msgData);
void SubscribeHandlerSystemStateTopic(MessageData *msgData);
// void configure_extint_channel(void);
// void configure_extint_callbacks(void);

#ifdef __cplusplus
}
#endif

#endif /*WIFI_TASK_H_*/
