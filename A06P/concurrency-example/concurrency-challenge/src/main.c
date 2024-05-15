/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * This is a bare minimum user application template.
 *
 * For documentation of the board, go \ref group_common_boards "here" for a link
 * to the board-specific documentation.
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# Minimal main function that starts with a call to system_init()
 * -# Basic usage of on-board LED and button
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include "button.h"
#include "led.h"
#include "systick.h"
#include <asf.h>

int main(void) {
    system_init();

    SystickInit();
    /* Insert application code here, after the board has been initialized. */

    // Initialize PIN PA23 as an output pin
    struct port_config config_port_pin;           // Define structure needed to configure a pin
    port_get_config_defaults(&config_port_pin);   // Initialize structure with default configurations.
    // Now we change the structure to what we need.
    config_port_pin.direction = PORT_PIN_DIR_OUTPUT;   // Set pin as OUTPUT
    port_pin_set_config(PIN_PA23, &config_port_pin);   // We assign the pin configuration to the PIN_PA23

    /* Set buttons as input */
    config_port_pin.direction = PORT_PIN_DIR_INPUT;
    config_port_pin.input_pull = PORT_PIN_PULL_UP;
    port_pin_set_config(BUTTON_0_PIN, &config_port_pin);

    int counter;

    InitLedTask();
    InitButtonTask();

    while (1) {
        counter++;
        LedTask();      // Execute LED TASK
        ButtonTask();   // Execute button task
    }
}
