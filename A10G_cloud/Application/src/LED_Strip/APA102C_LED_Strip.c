/*
 * APA102C_LED_Strip.c
 *
 * Created: 08-04-2024 12.22.20 PM
 *  Author: Saurabh
 */ 
/*
  This is a library written for the Qwiic LED Stick.
  By Ciara Jekel @ SparkFun Electronics, June 11th, 2018

  The Qwiic LED Stick features ten addressable APA102 LEDs, 
  making it easy to add full color LED control using I2C. 
  Write to individual LEDs to display a count in binary,
  or write to the whole strip for cool lighting effects
  
  https://github.com/sparkfun/SparkFun_Qwiic_LED_Stick_Arduino_Library

  Development environment specifics:
  Arduino IDE 1.8.5

  SparkFun labored with love to create this code. Feel like supporting open
  source hardware? Buy a board from SparkFun!
  https://www.sparkfun.com/products/14783

  /**
 * @file APA102C_LED_Strip.c
 * @brief This file is a driver for sparkfun led strip derived from the original arduino driver and converted into a generalised driver,
 * Add your I2C code to platform_read, and platform_write functions
 * @author Saurabh Sandeep Parulekar
 * @date 2024-04-11
 * @version 1.0
  */


#include "APA102C_LED_Strip.h"
#include "I2cDriver\I2cDriver.h"

//This stores the current I2C address of the LED Stick
static uint8_t _LEDAddress = 0x23;

// //Start I2C communication
// boolean LED::begin(uint8_t address, TwoWire &wirePort) {
//   if (address < 0x08 || address > 0x77) return false; //invalid I2C addresses
//   _LEDAddress = address; //store the address in a private global variable
//   _i2cPort = &wirePort; //Grab which port the user wants us to use		
  
//  return isConnected();
// }

// boolean LED::isConnected() {
//   _i2cPort->beginTransmission(_LEDAddress);
//   if (_i2cPort->endTransmission() == 0)
//     return true;
//   return false;
// }

/**
 * @brief Set the LEDColor index object
 * Change the color of a specific LED
 * each color must be a value between 0-255
 * LEDS indexed starting at 1
 * @param number 
 * @param red 
 * @param green 
 * @param blue 
 * @return uint32_t 
 */
uint32_t setLEDColor_index(LEDdev_ctx_t *ctx, uint8_t number, uint8_t red, uint8_t green, uint8_t blue) {
  // First, boundary check
  uint8_t reg[4];
  uint32_t error = ERROR_NONE;
  if (red > 255)
    red = 255;
  if (red < 0)
    red = 0;
  if (green > 255)
    green = 255;
  if (green < 0)
    green = 0;
  if (blue > 255)
    blue = 255;
  if (blue < 0)
    blue = 0;
reg[0] = number;
reg[1] = red;
reg[2] = green;
reg[3] = blue;
error = apa102c_write_reg(ctx, COMMAND_WRITE_SINGLE_LED_COLOR, &reg, 4);
//   _i2cPort->beginTransmission(_LEDAddress); //communicate using address
//   _i2cPort->write(COMMAND_WRITE_SINGLE_LED_COLOR); //command to change single LED's color
//   _i2cPort->write(number); //choose which LED
//   _i2cPort->write(red); //update red value
//   _i2cPort->write(green); //update green value
//   _i2cPort->write(blue); //update blue value
//   if (_i2cPort->endTransmission() != 0)
//   {
//     //Sensor did not ACK
//     return (false);
//   }
  return error;
}

/**
 * @brief Set the LEDColor all object
 * Change the color of all LEDs
 * each color must be a value between 0-255
 * @param red 
 * @param green 
 * @param blue 
 * @return uint32_t 
 */
uint32_t setLEDColor_all(LEDdev_ctx_t *ctx, uint8_t red, uint8_t green, uint8_t blue) {
  // First, boundary check
  uint8_t reg[3];
  uint32_t error = ERROR_NONE;
  if (red > 255)
    red = 255;
  if (red < 0)
    red = 0;
  if (green > 255)
    green = 255;
  if (green < 0)
    green = 0;
  if (blue > 255)
    blue = 255;
  if (blue < 0)
    blue = 0;
  reg[0] = red;
  reg[1] = green;
  reg[2] = blue;
  error = apa102c_write_reg(ctx, COMMAND_WRITE_ALL_LED_COLOR, &reg, 3);
//   _i2cPort->beginTransmission(_LEDAddress); //communicate using address
//   _i2cPort->write(COMMAND_WRITE_ALL_LED_COLOR); //command to change all LEDs' colors
//   _i2cPort->write(red); //update red value
//   _i2cPort->write(green); //update green value
//   _i2cPort->write(blue); //update blue value
//   if (_i2cPort->endTransmission() != 0)
//   {
//     //Sensor did not ACK
//     return (false);
//   }
  return error;
}


/**
 * @brief Set the LEDColor index all object
 * Change the color of all LEDs at once to individual values
 * Pass in 3 arrays of color values
 * each color must be a value between 0-255
 * @param[in] redArray 
 * @param[in] greenArray 
 * @param[in] blueArray 
 * @param[in] length 
 * @return uint32_t If no error returns ERROR_NONE
 */
uint32_t setLEDColor_index_all(LEDdev_ctx_t *ctx, uint8_t redArray[], uint8_t greenArray[], uint8_t blueArray[], uint8_t length) {
  // Create an array of given size
  uint8_t reg[20];
  uint32_t error = ERROR_NONE;
  // First, boundary check
  for (int i = 0; i < length; i++){
    if (redArray[i] > 255)
      redArray[i] = 255;
    if (redArray[i] < 0)
      redArray[i] = 0;
    if (greenArray[i] > 255)
      greenArray[i] = 255;
    if (greenArray[i] < 0)
      greenArray[i] = 0;
    if (blueArray[i] > 255)
      blueArray[i] = 255;
    if (blueArray[i] < 0)
      blueArray[i] = 0;
  }

   //ATtiny has a 16 uint8_t limit on a single I2C transmission,
   //so multiple calls to commands are required
  uint8_t n;
  uint8_t len = length % 12; //value for remainder of division length/12
  for (n = 0; n < length / 12; n++) { //will repeat for the # of times 12 goes into length evenly
    reg[0] = 12;
    reg[1] = n * 12;
    for(uint32_t i=0; i < 12; i++){
        reg[i + 2] = redArray[n * 12 + i];
    }
    error = apa102c_write_reg(ctx, COMMAND_WRITE_RED_ARRAY, &reg, 14);
    // _i2cPort->beginTransmission(_LEDAddress); //communicate using address
    // _i2cPort->write(COMMAND_WRITE_RED_ARRAY); //command to change red value of LEDs
    // _i2cPort->write(12); //length of expected transmission
    // _i2cPort->write(n * 12 ); //write offset
    // _i2cPort->write(&redArray[n * 12], 12); //transmit 12 values of color array starting at (n*12)th value
    // if (_i2cPort->endTransmission() != 0)
    // {
    //   //Sensor did not ACK
    //   return false;
    // }
  }
  if (len != 0) { //will transmit if there is a remainder of the division length/12
    reg[0] = len;
    reg[1] = n * 12;
    for(uint32_t i=0; i < len; i++){
        reg[i + 2] = redArray[n * 12 + i];
    }
    error = apa102c_write_reg(ctx, COMMAND_WRITE_RED_ARRAY, &reg, len+2);
    // _i2cPort->beginTransmission(_LEDAddress); //communicate using address
    // _i2cPort->write(COMMAND_WRITE_RED_ARRAY); //command to change red value of LEDs
    // _i2cPort->write(len); //length of expected transmission is the remainder of the division length/12
    // _i2cPort->write(n * 12); //offset
    // _i2cPort->write(&redArray[n * 12], len); //transmit len values of color array starting at (n*12)th value
    // if (_i2cPort->endTransmission() != 0) {
    //   //Sensor did not ACK
    //   return false;
    // }
  }
  for (n = 0; n < length / 12; n++) {
    reg[0] = 12;
    reg[1] = n * 12;
    for(uint32_t i=0; i < 12; i++){
        reg[i + 2] = greenArray[n * 12 + i];
    }
    error = apa102c_write_reg(ctx, COMMAND_WRITE_GREEN_ARRAY, &reg, 14);
    // _i2cPort->beginTransmission(_LEDAddress);
    // _i2cPort->write(COMMAND_WRITE_GREEN_ARRAY);
    // _i2cPort->write(12);
    // _i2cPort->write(n * 12 ); //offset
    // _i2cPort->write(&greenArray[n * 12], 12);
    // if (_i2cPort->endTransmission() != 0)
    // {
    //   //Sensor did not ACK
    //   return false;
    // }
  }
  if (len != 0) {
    reg[0] = len;
    reg[1] = n * 12;
    for(uint32_t i=0; i < len; i++){
        reg[i + 2] = greenArray[n * 12 + i];
    }
    error = apa102c_write_reg(ctx, COMMAND_WRITE_GREEN_ARRAY, &reg, len+2);
    // _i2cPort->beginTransmission(_LEDAddress);
    // _i2cPort->write(COMMAND_WRITE_GREEN_ARRAY);
    // _i2cPort->write(len);
    // _i2cPort->write(n * 12); //offset
    // _i2cPort->write(&greenArray[n * 12], len);
    // if (_i2cPort->endTransmission() != 0) {
    //   //Sensor did not ACK
    //   return false;
    // }
  }
  for (n = 0; n < length / 12; n++) {
    reg[0] = 12;
    reg[1] = n * 12;
    for(uint32_t i=0; i < 12; i++){
        reg[i + 2] = blueArray[n * 12 + i];
    }
    error = apa102c_write_reg(ctx, COMMAND_WRITE_BLUE_ARRAY, &reg, 14);
    // _i2cPort->beginTransmission(_LEDAddress);
    // _i2cPort->write(COMMAND_WRITE_BLUE_ARRAY);
    // _i2cPort->write(12);
    // _i2cPort->write(n * 12 ); //offset
    // _i2cPort->write(&blueArray[n * 12], 12);
    // if (_i2cPort->endTransmission() != 0)
    // {
    //   //Sensor did not ACK
    //   return false;
    // }
  }
  if (len != 0) {
    reg[0] = len;
    reg[1] = n * 12;
    for(uint32_t i=0; i < len; i++){
        reg[i + 2] = blueArray[n * 12 + i];
    }
    error = apa102c_write_reg(ctx, COMMAND_WRITE_BLUE_ARRAY, &reg, len+2);
    // _i2cPort->beginTransmission(_LEDAddress);
    // _i2cPort->write(COMMAND_WRITE_BLUE_ARRAY);
    // _i2cPort->write(len);
    // _i2cPort->write(n * 12); //offset
    // _i2cPort->write(&blueArray[n * 12], len);
    // if (_i2cPort->endTransmission() != 0) {
    //   //Sensor did not ACK
    //   return false;
    // }
  }
  return error;
}

/**
 * @brief Set the LEDBrightness index object
 * Change the brightness of a specific LED, while keeping their current color
 * brightness must be a value between 0-31
 * To turn LEDs off but remember their previous color, set brightness to 0
 * LEDS indexed starting at 1
 * @param[in] ctx I2C Handle
 * @param[in] number Led Index (1 to 10)
 * @param[in] brightness Brightness values between 0 to 31
 * @return uin32_t If no error returns ERROR_NONE
 */
uint32_t setLEDBrightness_index(LEDdev_ctx_t *ctx, uint8_t number, uint8_t brightness) {
  uint8_t reg[2];
  uint32_t error = ERROR_NONE;
  reg[0] = number;
  reg[1] = brightness;
  // First, boundary check
  if (brightness > 31)
    brightness = 31;
  if (brightness < 0)
    brightness = 0;

  error = apa102c_write_reg(ctx, COMMAND_WRITE_SINGLE_LED_BRIGHTNESS, &reg, 2);
  return error;

//   _i2cPort->beginTransmission(_LEDAddress); //Communicate using the address
//   _i2cPort->write(COMMAND_WRITE_SINGLE_LED_BRIGHTNESS); //Command to write single brightness
//   _i2cPort->write(number); //Choose which LED
//   _i2cPort->write(brightness); //Update brightness 
//   if (_i2cPort->endTransmission() != 0)
//   {
//     //Sensor did not ACK
//     return (false);
//   }
//   return (true);
}

/**
 * @brief Set the LEDBrightness all object
 * Change the brightness of all LEDs, while keeping their current color
 * brightness must be a value between 0-31
 * To turn all LEDs off but remember their previous color, set brightness to 0
 * @param[in] ctx I2C handle
 * @param[in] brightness Brightness values between 0 to 31
 * @return uint32_t If no error returns ERROR_NONE
 */
uint32_t setLEDBrightness_all(LEDdev_ctx_t *ctx, uint8_t brightness) {
  uint8_t reg = brightness;
  uint32_t error = ERROR_NONE;
  // First, boundary check
  if (brightness > 31)
    brightness = 31;
  if (brightness < 0)
    brightness = 0;

  error = apa102c_write_reg(ctx, COMMAND_WRITE_ALL_LED_BRIGHTNESS, &reg, 1);
  return error;

//   _i2cPort->beginTransmission(_LEDAddress); //Communicate using the address
//   _i2cPort->write(COMMAND_WRITE_ALL_LED_BRIGHTNESS); //Command to change all brightness
//   _i2cPort->write(brightness); //Update brightness
//   if (_i2cPort->endTransmission() != 0)
//   {
//     //Sensor did not ACK
//     return (false);
//   }
//   return (true);
}

/**
 * @brief Turn all LEDS off by setting color to 0
 * 
 * @return uint32_t If no error returns ERROR_NONE
 */
uint32_t LEDOff(LEDdev_ctx_t *ctx) {
    uint8_t reg = 0;
    uint32_t error = ERROR_NONE;
    error = apa102c_write_reg(ctx, COMMAND_WRITE_ALL_LED_OFF, &reg, 0);
    return error;
//   _i2cPort->beginTransmission(_LEDAddress); //Communicate using the address
//   _i2cPort->write(COMMAND_WRITE_ALL_LED_OFF); //Command to turn off
//   if (_i2cPort->endTransmission() != 0)
//   {
//     //Sensor did not ACK
//     return (false);
//   }
//   return (true);
}

/**
 * @brief Change the I2C address from one address to another
 * 
 * @param[in] newAddress New address to set as the I2C device address
 * @return uint32_t If no error returns ERROR_NONE
 */
uint32_t changeAddress(LEDdev_ctx_t *ctx, uint8_t newAddress)
{
    uint8_t reg = newAddress;
    uint32_t error = ERROR_NONE;
    error = apa102c_write_reg(ctx, COMMAND_CHANGE_ADDRESS, &reg, 1);
    return error;
//   _i2cPort->beginTransmission(_LEDAddress); //Communicate using the old address
//   _i2cPort->write(COMMAND_CHANGE_ADDRESS); //0xC7 is the register location on the KeyPad to change its I2C address
//   _i2cPort->write(newAddress); //Go to the new address
//   if (_i2cPort->endTransmission() != 0)
//   {
//     //Sensor did not ACK
//     return (false);
//   }
//     _LEDAddress = newAddress;
// 	return (true);

}


/**
 * @brief Change Length of LEDs in the strip
 * 
 * @param[in] ctx I2C handle
 * @param[in] newLength New length of LED strip
 * @return uint32_t If no error returns ERROR_NONE
 */
uint32_t changeLength(LEDdev_ctx_t *ctx, uint8_t newLength)
{  
  uint8_t reg = newLength;
  uint32_t error = ERROR_NONE;
  error = apa102c_write_reg(ctx, COMMAND_CHANGE_LED_LENGTH, &reg, 1);
  return error;
    //   _i2cPort->beginTransmission(_LEDAddress); //Communicate using address
    //   _i2cPort->write(COMMAND_CHANGE_LED_LENGTH); //Command to change the length
    //   _i2cPort->write(newLength); //Update the length
    //   if (_i2cPort->endTransmission() != 0)
    //   {
    //     //Sensor did not ACK
    //     return (false);
    //   }
    //   return (true);

}

/**
  * @brief  Write generic device register
  *
  * @param  ctx   read / write interface definitions(ptr)
  * @param  reg   register to write
  * @param  data  pointer to data to write in register reg(ptr)
  * @param  len   number of consecutive register to write
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
static int32_t apa102c_write_reg(LEDdev_ctx_t *ctx, uint8_t reg,
                          uint8_t *data,
                          uint16_t len)
{
    int32_t ret;

    ret = ctx->write_reg(ctx->handle, reg, data, len);

    return ret; 
}

/**
  * @brief  Read generic device register
  *
  * @param  ctx   read / write interface definitions(ptr)
  * @param  reg   register to read
  * @param  data  pointer to buffer that store the data read(ptr)
  * @param  len   number of consecutive register to read
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
static int32_t apa102c_read_reg(LEDdev_ctx_t *ctx, uint8_t reg,
                         uint8_t *data,
                         uint16_t len)
{
  int32_t ret;

  ret = ctx->read_reg(ctx->handle, reg, data, len);

  return ret;
}

//***************************************************************************************************
// Update the platform_write and platform_read functions as per the platform used, the following interface
// is for SAMD21
// Also Update the InitLED function as per your initial conditions
//***************************************************************************************************

static int32_t platform_write(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len);

static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len);



LEDdev_ctx_t dev_ctx_APA102C = {.write_reg = platform_write, .read_reg = platform_read};

uint8_t msgOutLED[64]; ///<USE ME AS A BUFFER FOR platform_write and platform_read
I2C_Data LEDData; ///<Use me as a structure to communicate with the IMU on platform_write and platform_read

/**************************************************************************//**
 * @fn			static int32_t platform_write(void *handle, uint8_t reg, uint8_t *bufp,uint16_t len)
 * @brief       Function to write data to a register
 * @details     Function to write data (bufp) to a register (reg)
				
 * @param[in]   handle IGNORE
 * @param[in]   reg Register to write to. In an I2C transaction, this gets sent first
 * @param[in]   bufp Pointer to the data to be sent
 * @param[in]   len Length of the data sent
 * @return      Returns what the function "I2cWriteDataWait" returns
 * @note        STUDENTS TO FILL  
*****************************************************************************/
static int32_t platform_write(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len)
{
  msgOutLED[0] = reg;
	for(uint16_t i=0; i < len; i++){
		msgOutLED[i+1] = bufp[i];
	}
	LEDData.address = _LEDAddress;
	LEDData.msgOut = &msgOutLED;
	LEDData.lenOut = len + 1;
	LEDData.lenIn = len;
	LEDData.msgIn = bufp;
  return I2cWriteDataWait(&LEDData, 100);
}

/**************************************************************************//**
 * @fn			static  int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len)
 * @brief       Function to read data from a register
 * @details     Function to read data (bufp) from a register (reg)
				
 * @param[in]   handle IGNORE
 * @param[in]   reg Register to read from. In an I2C transaction, this gets sent first
 * @param[out]   bufp Pointer to the data to write to (write what was read)
 * @param[in]   len Length of the data to be read
 * @return      Returns If no error returns ERROR_NONE
*****************************************************************************/
static  int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len)
{
	//YOUR JOB: Fill out the structure "LEDData" to send to the device
	//TIP: Check the structure "LEDData" and notice that it has a msgOut and msgIn parameter. How do we fill this to our advantage?
	msgOutLED[0] = reg;
	LEDData.address = _LEDAddress;
	LEDData.msgIn = bufp;
	LEDData.lenIn = len;
	LEDData.lenOut = 1;
	LEDData.msgOut = &msgOutLED;
	
	return I2cReadDataWait(&LEDData, 100, 100);
}


/**
 * @brief Returns LED struct Object
 * 
 * @return LEDdev_ctx_t* 
 */
LEDdev_ctx_t * GetLEDStruct(void)
{
return &dev_ctx_APA102C;
}
 

/**
 * @brief Initialized LED strip
 * Can be customized to whatever is needed during Init
 * Perhaps a Initializes LED dance
 * @return int32_t If no error returns ERROR_NONE
 */
int32_t InitLED(void)
{
uint8_t rst;
int32_t error = ERROR_NONE;
setLEDBrightness_all(&dev_ctx_APA102C, 5);
for(uint8_t i=0; i<10; i++){
    setLEDColor_index(&dev_ctx_APA102C, i, 0, 200, 0);
    delay_ms(300);
}
LEDOff(&dev_ctx_APA102C);
return error;
}

