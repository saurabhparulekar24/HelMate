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
#include <asf.h>

volatile uint32_t ul_tickcount = 0; ///<Systick counter. Holds the current value of the systick. Use to measure relative time between events.

/**************************************************************************/ /**
* function          void SysTick_Handler(void)
* @brief            Interrupt handler for the systick timer. Should be fired every 1ms. Increases ul_tickcount
*****************************************************************************/
static void SystickInit(void);
void SysTick_Handler(void){
	
	ul_tickcount++ ;
}




int main (void)
{
	system_init();
	
	
	SystickInit();
	/* Insert application code here, after the board has been initialized. */
	
	//Initialize PIN PA23 as an output pin
	struct port_config config_port_pin;//Define structure needed to configure a pin
	port_get_config_defaults(&config_port_pin); //Initialize structure with default configurations.
	//Now we change the structure to what we need.
	config_port_pin.direction = PORT_PIN_DIR_OUTPUT; //Set pin as OUTPUT
	port_pin_set_config(PIN_PA23, &config_port_pin); //We assign the pin configuration to the PIN_PA23
	
	/* Set buttons as input */
	config_port_pin.direction  = PORT_PIN_DIR_INPUT;
	config_port_pin.input_pull = PORT_PIN_PULL_UP;
	port_pin_set_config(BUTTON_0_PIN, &config_port_pin);

	while(1);
}


/**************************************************************************/ /**
* function          static void SystickInit(void)
* @brief            Initializes the systick timer. Increases the systick every one (1) ms
*****************************************************************************/
static void SystickInit(void)
{
		// Configure SysTick to trigger every millisecond using the CPU Clock
		SysTick->CTRL = 0;					// Disable SysTick
		SysTick->LOAD = 47999UL;				// Set reload register for 1mS interrupts - 48MHz Clock
		NVIC_SetPriority(SysTick_IRQn, 3);	// Set interrupt priority to least urgency
		SysTick->VAL = 0;					// Reset the SysTick counter value
		SysTick->CTRL = 0x00000007;			// Enable SysTick, Enable SysTick Exceptions, Use CPU Clock
		NVIC_EnableIRQ(SysTick_IRQn);		// Enable SysTick Interrupt
}