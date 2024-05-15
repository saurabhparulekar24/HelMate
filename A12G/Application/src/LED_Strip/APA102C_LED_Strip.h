/*
 * APA102C_LED_Strip.h
 *
 * Created: 08-04-2024 12.22.31 PM
 *  Author: Saurabh
 */ 


#ifndef APA102C_LED_STRIP_H_
#define APA102C_LED_STRIP_H_

/*
  This is a library written for the Qwiic LED Stick.
  By Ciara Jekel @ SparkFun Electronics, June 11th, 2018

  The Qwiic LED Stick features ten addressable APA102 LEDs,
  making it easy to add an output to your latest project.
  Write to individual LEDs to display a count in binary,
  or write to the whole strip for cool lighting effects
  
  https://github.com/sparkfun/SparkFun_Qwiic_LED_Stick_Arduino_Library

  Development environment specifics:
  Arduino IDE 1.8.5

  SparkFun labored with love to create this code. Feel like supporting open
  source hardware? Buy a board from SparkFun!
  https://www.sparkfun.com/products/14783
*/
#include "stdint.h"
#include "stdbool.h"

#define COMMAND_CHANGE_ADDRESS (0xC7)
#define COMMAND_CHANGE_LED_LENGTH (0x70)
#define COMMAND_WRITE_SINGLE_LED_COLOR (0x71)
#define COMMAND_WRITE_ALL_LED_COLOR (0x72)
#define COMMAND_WRITE_RED_ARRAY (0x73)
#define COMMAND_WRITE_GREEN_ARRAY (0x74)
#define COMMAND_WRITE_BLUE_ARRAY (0x75)
#define COMMAND_WRITE_SINGLE_LED_BRIGHTNESS (0x76)
#define COMMAND_WRITE_ALL_LED_BRIGHTNESS (0x77)
#define COMMAND_WRITE_ALL_LED_OFF (0x78)

// Error Codes
#define ERROR_NONE 0

// Levels
#define MAX_BRIGHTNESS 31
#define MIN_BRIGHTNESS 0

// percentage calculators
#define PER_BRIGHTNESS(per) (((per*MAX_BRIGHTNESS))/(100))

//Defining function pointers 
//*************************************************************************
typedef int32_t (*LEDdev_write_ptr)(void *, uint8_t, const uint8_t *, uint16_t);
typedef int32_t (*LEDdev_read_ptr)(void *, uint8_t, uint8_t *, uint16_t);
typedef struct
{
  /** Component mandatory fields **/
  LEDdev_write_ptr  write_reg;
  LEDdev_read_ptr   read_reg;
  /** Customizable optional pointer **/
  void *handle;
} LEDdev_ctx_t;

// Function Prototypes
//Change the color of a specific LED 
//each color must be a value between 0-255
//LEDS indexed starting at 1
uint32_t setLEDColor_index(LEDdev_ctx_t *ctx, uint8_t number, uint8_t red, uint8_t green, uint8_t blue);
    
//Change the color of all LEDs
//each color must be a value between 0-255
uint32_t setLEDColor_all(LEDdev_ctx_t *ctx, uint8_t red, uint8_t green, uint8_t blue);

//Change the color of all LEDs at once to individual values
//Pass in 3 arrays of color values of length 'length'
//each color must be a value between 0-255
uint32_t setLEDColor_index_all(LEDdev_ctx_t *ctx, uint8_t redArray[], uint8_t greenArray[], uint8_t blueArray[], uint8_t length);

//Change the brightness of a specific LED, while keeping their current color
//brightness must be a value between 0-31
//To turn LEDs off but remember their previous color, set brightness to 0
//LEDS indexed starting at 1
uint32_t setLEDBrightness_index(LEDdev_ctx_t *ctx, uint8_t number, uint8_t brightness);

//Change the brightness of all LEDs, while keeping their current color
//brightness must be a value between 0-31
//To turn all LEDs off but remember their previous color, set brightness to 0
uint32_t setLEDBrightness_all(LEDdev_ctx_t *ctx, uint8_t brightness);

//Turn all LEDS off by setting color to 0
uint32_t LEDOff(LEDdev_ctx_t *ctx);

//Change the I2C address from one address to another
uint32_t changeAddress(LEDdev_ctx_t *ctx, uint8_t newAddress);

//Change the length of LEDs
uint32_t changeLength(LEDdev_ctx_t *ctx, uint8_t newLength);


int32_t InitLED(void);
LEDdev_ctx_t * GetLEDStruct(void);
static  int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len);
static int32_t platform_write(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len);
static int32_t apa102c_read_reg(LEDdev_ctx_t *ctx, uint8_t reg,
                         uint8_t *data,
                         uint16_t len);
static int32_t apa102c_write_reg(LEDdev_ctx_t *ctx, uint8_t reg,
                          uint8_t *data,
                          uint16_t len);                            



#endif /* APA102C_LED_STRIP_H_ */