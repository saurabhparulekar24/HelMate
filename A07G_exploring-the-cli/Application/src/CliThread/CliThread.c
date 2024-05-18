/**
* @file      CliThread.c
* @brief     File for the CLI Thread handler. Uses FREERTOS + CLI
* @author    Eduardo Garcia
* @date      2020-02-15

******************************************************************************/

/******************************************************************************
 * Includes
 ******************************************************************************/
#include "CliThread.h"

#include "I2cDriver/I2cDriver.h"
#include "WifiHandlerThread/WifiHandler.h"

/******************************************************************************
 * Defines
 ******************************************************************************/
#define FIRMWARE_VERSION "0.0.1" // Firmware version definition

/******************************************************************************
 * Variables
 ******************************************************************************/
static const char pcWelcomeMessage[] = "FreeRTOS CLI.\r\nType Help to view a list of registered commands.\r\n";

static const CLI_Command_Definition_t xOTAUCommand = {"fw", "fw: Download a file and perform an FW update\r\n", (const pdCOMMAND_LINE_CALLBACK)CLI_OTAU, 0};
static const CLI_Command_Definition_t xResetCommand = {"reset", "reset: Resets the device\r\n", (const pdCOMMAND_LINE_CALLBACK)CLI_ResetDevice, 0};
static const CLI_Command_Definition_t xI2cScan = {"i2c", "i2c: Scans I2C bus\r\n", (const pdCOMMAND_LINE_CALLBACK)CLI_i2cScan, 0};
// Command structure for 'version' and "ticks"
static const CLI_Command_Definition_t xVersionCommand = {"version", "version: Prints the firmware version.\r\n", (const pdCOMMAND_LINE_CALLBACK)CLI_Version, 0};
static const CLI_Command_Definition_t xTicksCommand = {"ticks", "ticks: Prints the number of ticks since the scheduler started.\r\n", (const pdCOMMAND_LINE_CALLBACK)CLI_Ticks, 0};
const CLI_Command_Definition_t xClearScreen = {CLI_COMMAND_CLEAR_SCREEN, CLI_HELP_CLEAR_SCREEN, CLI_CALLBACK_CLEAR_SCREEN, CLI_PARAMS_CLEAR_SCREEN};

SemaphoreHandle_t cliCharReadySemaphore;  ///< Semaphore to indicate that a character has been received

/******************************************************************************
 * Forward Declarations
 ******************************************************************************/
static void FreeRTOS_read(char *character);

/******************************************************************************
 * Callback Functions
 ******************************************************************************/

/******************************************************************************
 * CLI Thread
 ******************************************************************************/

void vCommandConsoleTask(void *pvParameters)
{
    // REGISTER COMMANDS HERE
    FreeRTOS_CLIRegisterCommand(&xOTAUCommand);
    FreeRTOS_CLIRegisterCommand(&xClearScreen);
    FreeRTOS_CLIRegisterCommand(&xResetCommand);
    FreeRTOS_CLIRegisterCommand(&xI2cScan);
	// New Command registrations for version ans ticks
	FreeRTOS_CLIRegisterCommand(&xVersionCommand);
	FreeRTOS_CLIRegisterCommand(&xTicksCommand);

    char cRxedChar[2];
    unsigned char cInputIndex = 0;
    BaseType_t xMoreDataToFollow;
    /* The input and output buffers are declared static to keep them off the stack. */
    static char pcOutputString[MAX_OUTPUT_LENGTH_CLI], pcInputString[MAX_INPUT_LENGTH_CLI];
    static char pcLastCommand[MAX_INPUT_LENGTH_CLI];
    static bool isEscapeCode = false;
    static char pcEscapeCodes[4];
    static uint8_t pcEscapeCodePos = 0;

    /* This code assumes the peripheral being used as the console has already
    been opened and configured, and is passed into the task as the task
    parameter.  Cast the task parameter to the correct type. */

    /* Send a welcome message to the user knows they are connected. */
    SerialConsoleWriteString((char *)pcWelcomeMessage);

    // Any semaphores/mutexes/etc you needed to be initialized, you can do them here
    cliCharReadySemaphore = xSemaphoreCreateBinary();
    if (cliCharReadySemaphore == NULL) {
        LogMessage(LOG_ERROR_LVL, "Could not allocate semaphore\r\n");
        vTaskSuspend(NULL);
    }

    for (;;) {
        FreeRTOS_read(&cRxedChar[0]);

        if (cRxedChar[0] == '\n' || cRxedChar[0] == '\r') {
            /* A newline character was received, so the input command string is
            complete and can be processed.  Transmit a line separator, just to
            make the output easier to read. */
            SerialConsoleWriteString((char *)"\r\n");
            // Copy for last command
            isEscapeCode = false;
            pcEscapeCodePos = 0;
            strncpy(pcLastCommand, pcInputString, MAX_INPUT_LENGTH_CLI - 1);
            pcLastCommand[MAX_INPUT_LENGTH_CLI - 1] = 0;  // Ensure null termination

            /* The command interpreter is called repeatedly until it returns
            pdFALSE.  See the "Implementing a command" documentation for an
            explanation of why this is. */
            do {
                /* Send the command string to the command interpreter.  Any
                output generated by the command interpreter will be placed in the
                pcOutputString buffer. */
                xMoreDataToFollow = FreeRTOS_CLIProcessCommand(pcInputString,        /* The command string.*/
                                                               pcOutputString,       /* The output buffer. */
                                                               MAX_OUTPUT_LENGTH_CLI /* The size of the output buffer. */
                );

                /* Write the output generated by the command interpreter to the
                console. */
                // Ensure it is null terminated
                pcOutputString[MAX_OUTPUT_LENGTH_CLI - 1] = 0;
                SerialConsoleWriteString(pcOutputString);

            } while (xMoreDataToFollow != pdFALSE);

            /* All the strings generated by the input command have been sent.
            Processing of the command is complete.  Clear the input string ready
            to receive the next command. */
            cInputIndex = 0;
            memset(pcInputString, 0x00, MAX_INPUT_LENGTH_CLI);
            memset(pcOutputString, 0, MAX_OUTPUT_LENGTH_CLI);
        } else {
            /* The if() clause performs the processing after a newline character
is received.  This else clause performs the processing if any other
character is received. */

            if (true == isEscapeCode) {
                if (pcEscapeCodePos < CLI_PC_ESCAPE_CODE_SIZE) {
                    pcEscapeCodes[pcEscapeCodePos++] = cRxedChar[0];
                } else {
                    isEscapeCode = false;
                    pcEscapeCodePos = 0;
                }

                if (pcEscapeCodePos >= CLI_PC_MIN_ESCAPE_CODE_SIZE) {
                    // UP ARROW SHOW LAST COMMAND
                    if (strcasecmp(pcEscapeCodes, "oa")) {
                        /// Delete current line and add prompt (">")
                        sprintf(pcInputString, "%c[2K\r>", 27);
                        SerialConsoleWriteString((char *)pcInputString);
                        /// Clear input buffer
                        cInputIndex = 0;
                        memset(pcInputString, 0x00, MAX_INPUT_LENGTH_CLI);
                        /// Send last command
                        strncpy(pcInputString, pcLastCommand, MAX_INPUT_LENGTH_CLI - 1);
                        cInputIndex = (strlen(pcInputString) < MAX_INPUT_LENGTH_CLI - 1) ? strlen(pcLastCommand) : MAX_INPUT_LENGTH_CLI - 1;
                        SerialConsoleWriteString(pcInputString);
                    }

                    isEscapeCode = false;
                    pcEscapeCodePos = 0;
                }
            }
            /* The if() clause performs the processing after a newline character
            is received.  This else clause performs the processing if any other
            character is received. */

            else if (cRxedChar[0] == '\r') {
                /* Ignore carriage returns. */
            } else if (cRxedChar[0] == ASCII_BACKSPACE || cRxedChar[0] == ASCII_DELETE) {
                char erase[4] = {0x08, 0x20, 0x08, 0x00};
                SerialConsoleWriteString(erase);
                /* Backspace was pressed.  Erase the last character in the input
                buffer - if there are any. */
                if (cInputIndex > 0) {
                    cInputIndex--;
                    pcInputString[cInputIndex] = 0;
                }
            }
            // ESC
            else if (cRxedChar[0] == ASCII_ESC) {
                isEscapeCode = true;  // Next characters will be code arguments
                pcEscapeCodePos = 0;
            } else {
                /* A character was entered.  It was not a new line, backspace
                or carriage return, so it is accepted as part of the input and
                placed into the input buffer.  When a n is entered the complete
                string will be passed to the command interpreter. */
                if (cInputIndex < MAX_INPUT_LENGTH_CLI) {
                    pcInputString[cInputIndex] = cRxedChar[0];
                    cInputIndex++;
                }

                // Order Echo
                cRxedChar[1] = 0;
                SerialConsoleWriteString(&cRxedChar[0]);
            }
        }
    }
}

/**
* @fn			void FreeRTOS_read(char* character)
* @brief		STUDENTS TO COMPLETE. This function block the thread unless we received a character
* @details		The function waits to acquire semaphone cliCharReadySemaphore then calls SerialConsoleReadCharacter to read 
                a character, if -1 is received it repeats, if 0 is received, it will load the character into character variable
* @note         None
*****************************************************************************/
static void FreeRTOS_read(char *character)
{   
    // SerialConsoleReadCharacter returns -1 when no characters are received
    // and 0 when it has received character
    int is_rx_char = SerialConsoleReadCharacter((uint8_t *)character);
    while(is_rx_char==-1){
        if(xSemaphoreTake(cliCharReadySemaphore,portMAX_DELAY)){
            is_rx_char = SerialConsoleReadCharacter((uint8_t *)character);
        }

    }
    // vTaskSuspend(NULL);  // We suspend ourselves. Please remove this when doing your code
}

/**
 * @fn			void CliCharReadySemaphoreGiveFromISR(void)
 * @brief		Give cliCharReadySemaphore binary semaphore from an ISR
 * @details
 * @note
 */
void CliCharReadySemaphoreGiveFromISR(void)
{
    static BaseType_t xHigherPriorityTaskWoken;
    xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(cliCharReadySemaphore, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

/******************************************************************************
 * CLI Functions - Define here
 ******************************************************************************/

// THIS COMMAND USES vt100 TERMINAL COMMANDS TO CLEAR THE SCREEN ON A TERMINAL PROGRAM LIKE TERA TERM
// SEE http://www.csie.ntu.edu.tw/~r92094/c++/VT100.html for more info
// CLI SPECIFIC COMMANDS
static char bufCli[CLI_MSG_LEN];
BaseType_t xCliClearTerminalScreen(char *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString)
{
    char clearScreen = ASCII_ESC;
    snprintf(bufCli, CLI_MSG_LEN - 1, "%c[2J", clearScreen);
    snprintf(pcWriteBuffer, xWriteBufferLen, bufCli);
    return pdFALSE;
}

// Example CLI Command. Reads from the IMU and returns data.
BaseType_t CLI_OTAU(int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString)
{
    WifiHandlerSetState(WIFI_DOWNLOAD_INIT);

    return pdFALSE;
}

// Example CLI Command. Resets system.
BaseType_t CLI_ResetDevice(int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString)
{
    system_reset();
    return pdFALSE;
}
// Version CLI Command 
BaseType_t CLI_Version(int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString)
{
	// Use snprintf to safely format the firmware version string into the provided buffer
	snprintf((char *)pcWriteBuffer, xWriteBufferLen, "Firmware Version: %s\r\n", FIRMWARE_VERSION);
	return pdFALSE; // Indicates no further output is expected
}

// Ticks CLI Command 
BaseType_t CLI_Ticks(int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString)
{
	// Retrieve the current tick count using FreeRTOS's xTaskGetTickCount()
	const TickType_t ticks = xTaskGetTickCount();
	// Format the tick count into the provided buffer
	snprintf((char *)pcWriteBuffer, xWriteBufferLen, "Ticks since start: %lu\r\n", (unsigned long)ticks);
	return pdFALSE; // Indicates no further output is expected
}



/**
 * @brief    Scans fot connected i2c devices
 * @param    p_cli
 * @param    argc
 * @param    argv
 ******************************************************************************/
BaseType_t CLI_i2cScan(int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString)
{
    I2C_Data i2cDevice;
    uint8_t address;
    // Send 0 command byte
    uint8_t dataOut[2] = {0, 0};
    uint8_t dataIn[2];
    dataOut[0] = 0;
    dataOut[1] = 0;
    i2cDevice.address = 0;
    i2cDevice.msgIn = (uint8_t *)&dataIn[0];
    i2cDevice.lenOut = 1;
    i2cDevice.msgOut = (const uint8_t *)&dataOut[0];
    i2cDevice.lenIn = 1;

    SerialConsoleWriteString("0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f\r\n");
    for (int i = 0; i < 128; i += 16) {
        snprintf(bufCli, CLI_MSG_LEN - 1, "%02x: ", i);
        SerialConsoleWriteString(bufCli);

        for (int j = 0; j < 16; j++) {
            i2cDevice.address = (i + j) << 1;

            int32_t ret = I2cWriteDataWait(&i2cDevice, 100);
            if (ret == 0) {
                snprintf(bufCli, CLI_MSG_LEN - 1, "%02x: ", i2cDevice.address);
                SerialConsoleWriteString(bufCli);
            } else {
                snprintf(bufCli, CLI_MSG_LEN - 1, "X ");
                SerialConsoleWriteString(bufCli);
            }
        }
        SerialConsoleWriteString("\r\n");
    }
    SerialConsoleWriteString("\r\n");
    return pdFALSE;
}