/*
 * Concurrency_Challenge.c
 *
 * Created: 12-03-2024 11.34.20 AM
 *  Author: Saurabh
 */ 
/*
 * FreeRTOS V202212.01
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

/******************************************************************************
 * NOTE 1:  This project provides two demo applications.  A simple blinky style
 * project, and a more comprehensive test and demo application.  The
 * mainCREATE_SIMPLE_BLINKY_DEMO_ONLY setting in main.c is used to select
 * between the two.  See the notes on using mainCREATE_SIMPLE_BLINKY_DEMO_ONLY
 * in main.c.  This file implements the simply blinky style version.
 *
 * NOTE 2:  This file only contains the source code that is specific to the
 * basic demo.  Generic functions, such FreeRTOS hook functions, and functions
 * required to configure the hardware, are defined in main.c.
 ******************************************************************************
 *
 * main_blinky() creates one queue, and two tasks.  It then starts the
 * scheduler.
 *
 * The Queue Send Task:
 * The queue send task is implemented by the prvQueueSendTask() function in
 * this file.  prvQueueSendTask() sits in a loop that causes it to repeatedly
 * block for 200 milliseconds before sending the value 100 to the queue that
 * was created within main_blinky().  Once the value is sent, the task loops
 * back around to block for another 200 milliseconds.
 *
 * The Queue Receive Task:
 * The queue receive task is implemented by the prvQueueReceiveTask() function
 * in this file.  prvQueueReceiveTask() sits in a loop where it repeatedly
 * blocks on attempts to read data from the queue that was created within
 * main_blinky().  When data is received, the task checks the value of the
 * data, and if the value equals the expected 100, toggles the LED.  The 'block
 * time' parameter passed to the queue receive function specifies that the
 * task should be held in the Blocked state indefinitely to wait for data to
 * be available on the queue.  The queue receive task will only leave the
 * Blocked state when the queue send task writes to the queue.  As the queue
 * send task writes to the queue every 200 milliseconds, the queue receive
 * task leaves the Blocked state every 200 milliseconds, and therefore toggles
 * the LED every 200 milliseconds.
 */

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "led.h"
#include "button.h"
#include "task.h"

/* Priorities at which the tasks are created. */
#define TASK_PRIORITY		( tskIDLE_PRIORITY + 1 )
// #define	mainQUEUE_SEND_TASK_PRIORITY		( tskIDLE_PRIORITY + 1 )

/* The number of items the queue can hold.  This is 1 as the receive task
will remove items as they are added, meaning the send task should always find
the queue empty. */
#define mainQUEUE_LENGTH					( 1 )

/* Values passed to the two tasks just to check the task parameter
functionality. */
#define mainQUEUE_PARAMETER			( 0x1111UL )


/*-----------------------------------------------------------*/

/*
 * The tasks as described in the comments at the top of this file.
 */
static void LEDTaskCall(void *pvParameters );
static void ButtonTaskCall(void *pvParameters);

void main_concurrency(void);
// Queue created to exchange button press data between LED and Button Task
static QueueHandle_t xQueue = NULL;
// Highwatermark to get the stack size used
UBaseType_t uxHighWaterMark;
void main_concurrency( void ){

    system_init();

    xQueue = xQueueCreate( mainQUEUE_LENGTH, sizeof( unsigned long ) );
    /* Insert application code here, after the board has been initialized. */

    // Initialize PIN PA23 as an output pin
    struct port_config config_port_pin;           // Define structure needed to configure a pin
    port_get_config_defaults(&config_port_pin);   // Initialize structure with default configurations.
    // Now we change the structure to what we need.
    config_port_pin.direction = PORT_PIN_DIR_OUTPUT;   // Set pin as OUTPUT
    port_pin_set_config(LED_0_PIN, &config_port_pin);   // We assign the pin configuration to the PIN_PA23

    /* Set buttons as input */
    config_port_pin.direction = PORT_PIN_DIR_INPUT;
	config_port_pin.input_pull = PORT_PIN_PULL_UP;
	port_pin_set_config(BUTTON_0_PIN, &config_port_pin);

    int counter;
    InitLedTask();
    InitButtonTask();
    /* Start the two tasks as described in the comments at the top of this
		file. */
		xTaskCreate( LEDTaskCall,					/* The function that implements the task. */
					"LED", 									/* The text name assigned to the task - for debug only as it is not used by the kernel. */
					configMINIMAL_STACK_SIZE, 				/* The size of the stack to allocate to the task. */
					( void * ) mainQUEUE_PARAMETER, /* The parameter passed to the task - just to check the functionality. */
					TASK_PRIORITY, 		/* The priority assigned to the task. */
					NULL );									/* The task handle is not required, so NULL is passed. */

		xTaskCreate( ButtonTaskCall, "BUT", configMINIMAL_STACK_SIZE, ( void * ) mainQUEUE_PARAMETER, TASK_PRIORITY, NULL );

		/* Start the tasks and timer running. */
		vTaskStartScheduler();
    

    while (1) {
        // counter++;
        LedTask();      // Execute LED TASK
        // ButtonTask();   // Execute button task
    }
}

/**************************************************************************/ /**
 * @fn		void LEDTaskCall(void)
 * @brief	Runs RTOS Task to call LEDTask, checks queue to check if button pressed and change frequency

 * @param[in] void *pvParameters
 * @param[out] None
 * @return Void
 * @note None
 *****************************************************************************/
static void LEDTaskCall(void *pvParameters ){
    configASSERT( ( ( unsigned long ) pvParameters ) == mainQUEUE_PARAMETER );
    int flag=0;
    uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
    for (;;){
        LedTask();
        xQueueReceive( xQueue, &flag, 0U );
        if(flag){
            LedSetChange();
            flag = 0;
        
        }
		uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
    }
}

/**************************************************************************/ /**
 * @fn		void ButtonTaskCall(void)
 * @brief	Runs RTOS Task to call ButtonTask and Send data to LED Task when button Pressed

 * @param[in] void *pvParameters
 * @param[out] None
 * @return Void
 * @note None
 *****************************************************************************/
static void ButtonTaskCall(void *pvParameters){
    configASSERT( ( ( unsigned long ) pvParameters ) == mainQUEUE_PARAMETER );
    int flag=0;
    uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
    for (;;){
        ButtonTask(&flag);
        if(flag){
            xQueueSend( xQueue, &flag, 0U );
            flag = 0;
        }
        uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);

    }
}
