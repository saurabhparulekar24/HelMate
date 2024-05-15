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
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include <asf.h>
#include <string.h>
#include "delay.h"

#define I2C_SLAVE_ADDR 0x30
#define retry 50

//Globally accessible module structure:
struct usart_module usartComm;
struct i2c_slave_module i2c_slave_instance;
struct i2c_master_module i2c_master_instance;
struct spi_module spi_master_instance;
struct spi_module spi_slave_instance;
struct spi_slave_inst slave;

// Enumerated for selecting interface
enum interface {USART,I2C,SPI};

/**
 * @brief Configures SPI as slave
 * 
 */
void configure_spi_slave(void)
{
    struct spi_config config_spi_slave;
	struct port_config config_port_pin;
    port_get_config_defaults(&config_port_pin);
    config_port_pin.direction  = PORT_PIN_DIR_INPUT;
    config_port_pin.input_pull = PORT_PIN_PULL_UP;
	port_pin_set_config(PIN_PA17, &config_port_pin);
    /* Configure, initialize and enable SERCOM SPI module */
    spi_get_config_defaults(&config_spi_slave);
    config_spi_slave.mode = SPI_MODE_SLAVE;
    config_spi_slave.mode_specific.slave.preload_enable = true;
    config_spi_slave.mode_specific.slave.frame_format = SPI_FRAME_FORMAT_SPI_FRAME;
    config_spi_slave.mux_setting = SPI_SIGNAL_MUX_SETTING_E;
    config_spi_slave.pinmux_pad0 = PINMUX_PA16C_SERCOM1_PAD0;
    config_spi_slave.pinmux_pad1 = PIN_PA17;
    config_spi_slave.pinmux_pad2 = PINMUX_PA18C_SERCOM1_PAD2;
    config_spi_slave.pinmux_pad3 = PINMUX_PA19C_SERCOM1_PAD3;
    spi_init(&spi_slave_instance, EDBG_SPI_MODULE, &config_spi_slave);
    spi_enable(&spi_slave_instance);
}

/**
 * @brief Configures SPI as master
 * Configure setting for SPI
 */
void configure_spi_master(void)
{
    struct spi_config config_spi_master;
    struct spi_slave_inst_config slave_dev_config;
    /* Configure and initialize software device instance of peripheral slave */
    spi_slave_inst_get_config_defaults(&slave_dev_config);
    slave_dev_config.ss_pin = PIN_PA17;
    spi_attach_slave(&slave, &slave_dev_config);
    /* Configure, initialize and enable SERCOM SPI module */
    spi_get_config_defaults(&config_spi_master);
    config_spi_master.mux_setting = SPI_SIGNAL_MUX_SETTING_E;
    config_spi_master.pinmux_pad0 = PINMUX_PA16C_SERCOM1_PAD0;
    config_spi_master.pinmux_pad1 = PIN_PA17;
    config_spi_master.pinmux_pad2 = PINMUX_PA18C_SERCOM1_PAD2;
    config_spi_master.pinmux_pad3 = PINMUX_PA19C_SERCOM1_PAD3;
    spi_init(&spi_master_instance, EDBG_SPI_MODULE, &config_spi_master);
    spi_enable(&spi_master_instance);
}

/**
 * @brief Configures SPI as master
 * Configure setting for SPI
 */
void configure_spi_master_no_ss(void)
{
    struct spi_config config_spi_master;
    struct spi_slave_inst_config slave_dev_config;
    /* Configure and initialize software device instance of peripheral slave */
    spi_slave_inst_get_config_defaults(&slave_dev_config);
    // slave_dev_config.ss_pin = PIN_PA17;
    // spi_attach_slave(&slave, &slave_dev_config);
    /* Configure, initialize and enable SERCOM SPI module */
    spi_get_config_defaults(&config_spi_master);
    config_spi_master.mux_setting = SPI_SIGNAL_MUX_SETTING_E;
    config_spi_master.pinmux_pad0 = PINMUX_PA16C_SERCOM1_PAD0;
    config_spi_master.pinmux_pad1 = PINMUX_UNUSED;
    config_spi_master.pinmux_pad2 = PINMUX_PA18C_SERCOM1_PAD2;
    config_spi_master.pinmux_pad3 = PINMUX_PA19C_SERCOM1_PAD3;
    spi_init(&spi_master_instance, EDBG_SPI_MODULE, &config_spi_master);
    spi_enable(&spi_master_instance);
}
/**
 * @brief Configures USART
 * This function configures the USART, setting the baud rate, Pins and SERCOM
 */
static void configure_usart(void)
{	
    struct usart_config config_usart;
    usart_get_config_defaults(&config_usart);

    config_usart.baudrate = 9600;
    config_usart.mux_setting = USART_RX_1_TX_0_XCK_1;
    config_usart.pinmux_pad0 = PINMUX_PB02D_SERCOM5_PAD0;
    config_usart.pinmux_pad1 = PINMUX_PB03D_SERCOM5_PAD1;
    config_usart.pinmux_pad2 = PINMUX_UNUSED;
    config_usart.pinmux_pad3 = PINMUX_UNUSED;

    while (usart_init(&usartComm, SERCOM5, &config_usart) != STATUS_OK) {
    }

    usart_enable(&usartComm);
}

/**
 * @brief Configures I2C as Slave
 * Configure the setting for setting the SERCOM as I2C slave
 */
void configure_i2c_slave(void)
{
	struct i2c_slave_config i2c_slave;
	i2c_slave_get_config_defaults(&i2c_slave);
	
	i2c_slave.address = I2C_SLAVE_ADDR;
	i2c_slave.address_mode = I2C_SLAVE_ADDRESS_MODE_MASK;	// can set for these: Address mask, second address, or lower limit of address range.
	i2c_slave.pinmux_pad0 = EDBG_I2C_SERCOM_PINMUX_PAD0;
	i2c_slave.pinmux_pad1 = EDBG_I2C_SERCOM_PINMUX_PAD1;
	i2c_slave.buffer_timeout = 1000;
	
	//initialize and enable device with i2c_slave/
	i2c_slave_init(&i2c_slave_instance, EDBG_I2C_MODULE, &i2c_slave);
	i2c_slave_enable(&i2c_slave_instance);
}

/**
 * @brief Configures I2C as master
 * Configure the setting for setting the SERCOM as I2C master
 */
void configure_i2c_master(void)
{
	/* Initialize config structure and software module. */
	struct i2c_master_config i2c_master;
	i2c_master_get_config_defaults(&i2c_master);
	
	/* Change buffer timeout to something longer. */
	i2c_master.buffer_timeout = 10000;
	i2c_master.pinmux_pad0 = EDBG_I2C_SERCOM_PINMUX_PAD0;
	i2c_master.pinmux_pad1 = EDBG_I2C_SERCOM_PINMUX_PAD1;
	
	 /* Initialize and enable device with config. */
	i2c_master_init(&i2c_master_instance, EDBG_I2C_MODULE, &i2c_master);
	i2c_master_enable(&i2c_master_instance);
}


/**
 * @brief Blinks LED
 * This function turns on the ON-Board LED for 1 sec and turns it OFF
 */
void blink_led(void){
	port_pin_set_output_level(LED_0_PIN,0);
	delay_s(1);
	port_pin_set_output_level(LED_0_PIN,1);
}

/**
 * @brief Send Message Over USART
 * This function sends the string message over USART
 * @param commProt enum value for which protocol to use
 * @param message pointer to the string to be sent
 */
void send_message(enum interface commProt, char *message){
	// Master packet struct
	struct i2c_master_packet master_packet;
	int counter = retry;
	switch(commProt){
		case USART:
			usart_write_buffer_wait(&usartComm, (uint8_t *)message, 12);
			break;
		case I2C:
			// Create transmitting packet
			master_packet.address = I2C_SLAVE_ADDR;
			master_packet.data_length = 1;
			master_packet.data = (uint8_t *)message;
			master_packet.ten_bit_address = false;
			master_packet.high_speed = false;
			master_packet.hs_master_code = 0x0;
			// Disable the Slave I2C
			i2c_slave_disable(&i2c_slave_instance);
			// Configure I2C as master
			configure_i2c_master();
			// Write packet
			while(i2c_master_write_packet_wait(&i2c_master_instance, &master_packet)!=STATUS_OK && counter > 0){
				counter--;
			}
			delay_ms(500);
			// Disable master
			i2c_master_disable(&i2c_master_instance);
			// Configure I2C back to slave
			configure_i2c_slave();
			break;
		case SPI:
			spi_disable(&spi_slave_instance);
			configure_spi_master();
			spi_select_slave(&spi_master_instance, &slave, true);
			while( spi_write_buffer_wait(&spi_master_instance, message, 1)!=STATUS_OK && counter > 0){
				counter--;
			}
			spi_select_slave(&spi_master_instance, &slave, false);
			delay_ms(500);
			//spi_disable(&spi_master_instance);
			spi_reset(&spi_master_instance);
			delay_ms(500);
			configure_spi_slave();
			break;
		default:
			usart_write_buffer_wait(&usartComm, (uint8_t *)message, 12);
			break;
	}
	
}


/**
 * @brief Read message from USART
 * 
 * @param commProt enum value for which protocol to use
 * @param message pointer for storing the received string
 */
void read_message(enum interface commProt, char *message){
	char received_message[12] = "Nothing";
	uint8_t r_message[1] = {0x00};
	struct i2c_slave_packet slave_packet;
	enum status_code code;
	switch (commProt)
	{
	case USART:
		code = usart_read_buffer_wait(&usartComm, (uint8_t *)&received_message,12);
		if(strcmp(received_message, message) == 0 && code == STATUS_OK){
			blink_led();
		}
		break;
	case I2C:
		slave_packet.data_length = 1;
		slave_packet.data = (uint8_t *)r_message;
		code = i2c_slave_read_packet_wait(&i2c_slave_instance,&slave_packet);
		if(r_message[0]==message[0] && code == STATUS_OK){
			blink_led();
		}
		break;
	case SPI:
		code = spi_read_buffer_wait(&spi_slave_instance, r_message, 1,0x00);
		if(r_message[0]==message[0] && code == STATUS_OK){
			blink_led();
		}
		break;
	default:
	 	code = usart_read_buffer_wait(&usartComm, (uint8_t *)&received_message,12);
		break;
	}
	
	
	
}


int main (void)
{
	system_init(); 
	delay_init();
	configure_usart();
	configure_i2c_slave();
	configure_spi_slave();
	char messageUSART[] = "Hello World";
	uint8_t messageI2C[1] = {0x21};
	uint8_t messageSPI[1] = {0xAA};
 	enum interface select_interface = SPI;
	while (1) {
		if(!port_pin_get_input_level(BUTTON_0_PIN)){
			switch(select_interface){
				case USART:
					send_message(select_interface,messageUSART);
					break;
				case I2C:
					send_message(select_interface,messageI2C);
					break;
				case SPI:
					send_message(select_interface,messageSPI);
					break;
				default:
					send_message(select_interface,messageUSART);
					break;
			}
			delay_ms(200);
		}
		else{
			
			switch(select_interface){
				case USART:
					read_message(select_interface,messageUSART);
					break;
				case I2C:
					configure_i2c_slave();
					read_message(select_interface,messageI2C);
					break;
				case SPI:
					configure_spi_slave();
					read_message(select_interface,messageSPI);
					break;
				default:
					read_message(select_interface,messageUSART);
					break;
			}
		}
	}
}


