/*
 * DRV2605.c
 *
 * Created: 07-04-2024 2.25.50 PM
 *  Author: Saurabh
 */ 
/*!
 * @file Adafruit_DRV2605.cpp
 *
 * @mainpage Adafruit DRV2605L Haptic Driver
 *
 * @section intro_sec Introduction
 *
 * This is a library for the Adafruit DRV2605L Haptic Driver ---->
 * http://www.adafruit.com/products/2305
 *
 * Check out the links above for our tutorials and wiring diagrams.
 *
 * This motor/haptic driver uses I2C to communicate.
 *
 * Adafruit invests time and resources providing this open source code,
 * please support Adafruit and open-source hardware by purchasing
 * products from Adafruit!
 *
 * @section author Author
 *
 * Written by Limor Fried/Ladyada for Adafruit Industries.
 *
 * @section license License
 *
 * MIT license, all text above must be included in any redistribution.
 *
 * NOTE: The File is licensed by above, I have added Platform read&write functions for making it compatible with SAMD21,
 * Also added a few more functions to enable multiple device control
 */


#include "DRV2605.h"
#include "I2cDriver\I2cDriver.h"
#include <stddef.h>
/**************************************************************************/
/*!
  @brief  Setup the HW
  @return Always true
*/
/**************************************************************************/
// bool initHaptic(hapdev_ctx_t *ctx){

//   // uint8_t id = readRegister8(DRV2605_REG_STATUS);
//   // Serial.print("Status 0x"); Serial.println(id, HEX);
//   uint8_t reg = 0;
//   drv2605_write_reg(ctx, DRV2605_REG_MODE,&reg, 1); // out of standby
//   reg = 0x00;
//   drv2605_write_reg(ctx, DRV2605_REG_RTPIN,&reg, 1); // no real-time-playback
//   reg = 1;
//   drv2605_write_reg(ctx, DRV2605_REG_WAVESEQ1, &reg, 1); // strong click
//   reg = 0;
//   drv2605_write_reg(ctx, DRV2605_REG_WAVESEQ2, &reg, 1); // end sequence
//   reg = 0;
//   drv2605_write_reg(ctx, DRV2605_REG_OVERDRIVE, &reg, 1); // no overdrive
//   reg = 0;
//   drv2605_write_reg(ctx, DRV2605_REG_SUSTAINPOS, &reg, 1);
//   reg = 0;
//   drv2605_write_reg(ctx, DRV2605_REG_SUSTAINNEG, &reg, 1);
//   reg = 0;
//   drv2605_write_reg(ctx, DRV2605_REG_BREAK, &reg, 1);
//   reg = 0x64;
//   drv2605_write_reg(ctx, DRV2605_REG_AUDIOMAX, &reg, 1);

//   // ERM open loop

//   // turn off N_ERM_LRA
//   drv2605_read_reg(ctx, ((DRV2605_REG_FEEDBACK)&0x7F), &reg, 1);
//   drv2605_write_reg(ctx, DRV2605_REG_FEEDBACK, &reg, 1);
//   drv2605_read_reg(ctx, ((DRV2605_REG_CONTROL3)|0x20), &reg, 1);
//   drv2605_write_reg(ctx, DRV2605_REG_CONTROL3, &reg, 1);
  //***********************************************************
//   drv2605_write_reg(ctx, DRV2605_REG_FEEDBACK,
//                  readRegister8(DRV2605_REG_FEEDBACK) & 0x7F);
//   // turn on ERM_OPEN_LOOP
//   drv2605_write_reg(DRV2605_REG_CONTROL3,
//                  readRegister8(DRV2605_REG_CONTROL3) | 0x20);

//   writeRegister8(DRV2605_REG_MODE, 0x00); // out of standby

//   writeRegister8(DRV2605_REG_RTPIN, 0x00); // no real-time-playback

//   writeRegister8(DRV2605_REG_WAVESEQ1, 1); // strong click
//   writeRegister8(DRV2605_REG_WAVESEQ2, 0); // end sequence

//   writeRegister8(DRV2605_REG_OVERDRIVE, 0); // no overdrive

//   writeRegister8(DRV2605_REG_SUSTAINPOS, 0);
//   writeRegister8(DRV2605_REG_SUSTAINNEG, 0);
//   writeRegister8(DRV2605_REG_BREAK, 0);
//   writeRegister8(DRV2605_REG_AUDIOMAX, 0x64);

//   // ERM open loop

//   // turn off N_ERM_LRA
//   writeRegister8(DRV2605_REG_FEEDBACK,
//                  readRegister8(DRV2605_REG_FEEDBACK) & 0x7F);
//   // turn on ERM_OPEN_LOOP
//   writeRegister8(DRV2605_REG_CONTROL3,
//                  readRegister8(DRV2605_REG_CONTROL3) | 0x20);

//   return true;
// }
static void select_dir(enum direction dir);
static int32_t Init(void);
/**
 * @brief Reads Status Register
 * 
 * @param ctx 
 * @return uint8_t Returns status of register
 * NOTE: Should be 0xE0 for normal condition
 */
uint8_t drv2605_readStatusReg(hapdev_ctx_t *ctx){
    uint8_t reg;
    uint32_t error = drv2605_read_reg(ctx, DRV2605_REG_STATUS, &reg, 1);
    return reg;
}

/**************************************************************************/
/*!
  @brief Select the haptic waveform to use.
  @param slot The waveform slot to set, from 0 to 7
  @param w The waveform sequence value, refers to an index in the ROM library.

    Playback starts at slot 0 and continues through to slot 7, stopping if it
  encounters a value of 0. A list of available waveforms can be found in
  section 11.2 of the datasheet: http://www.adafruit.com/datasheets/DRV2605.pdf
*/
/**************************************************************************/
void drv2605_setWaveform(hapdev_ctx_t *ctx, uint8_t slot, uint8_t w) {
    uint8_t reg = w;
  drv2605_write_reg(ctx, DRV2605_REG_WAVESEQ1 + slot, &reg, 1);
}

/**************************************************************************/
/*!
  @brief Select the waveform library to use.
  @param lib Library to use, 0 = Empty, 1-5 are ERM, 6 is LRA.

    See section 7.6.4 in the datasheet for more details:
  http://www.adafruit.com/datasheets/DRV2605.pdf
*/
/**************************************************************************/
void drv2605_selectLibrary(hapdev_ctx_t *ctx, uint8_t lib) {
//   writeRegister8(DRV2605_REG_LIBRARY, lib);
    uint8_t reg = lib;
    drv2605_write_reg(ctx, DRV2605_REG_LIBRARY, &reg, 1);
}

/**************************************************************************/
/*!
  @brief Start playback of the waveforms (start moving!).
*/
/**************************************************************************/
void drv2605_go(hapdev_ctx_t *ctx) { 
    // writeRegister8(DRV2605_REG_GO, 1); 
    uint8_t reg = 1;
    drv2605_write_reg(ctx, DRV2605_REG_GO, &reg, 1); 
}

/**************************************************************************/
/*!
  @brief Stop playback.
*/
/**************************************************************************/
void drv2605_stop(hapdev_ctx_t *ctx) { 
    // writeRegister8(DRV2605_REG_GO, 0); 
    uint8_t reg = 0;
    drv2605_write_reg(ctx, DRV2605_REG_GO, &reg, 1); 
    }

/**************************************************************************/
/*!
  @brief Set the device mode.
  @param mode Mode value, see datasheet section 7.6.2:
  http://www.adafruit.com/datasheets/DRV2605.pdf

    0: Internal trigger, call go() to start playback\n
    1: External trigger, rising edge on IN pin starts playback\n
    2: External trigger, playback follows the state of IN pin\n
    3: PWM/analog input\n
    4: Audio\n
    5: Real-time playback\n
    6: Diagnostics\n
    7: Auto calibration
*/
/**************************************************************************/
void drv2605_setMode(hapdev_ctx_t *ctx, uint8_t mode) {
//   writeRegister8(DRV2605_REG_MODE, mode);
uint8_t reg = mode;
drv2605_write_reg(ctx, DRV2605_REG_MODE, &reg, 1);
}

/**************************************************************************/
/*!
  @brief Set the realtime value when in RTP mode, used to directly drive the
  haptic motor.
  @param rtp 8-bit drive value.
*/
/**************************************************************************/
void drv2605_setRealtimeValue(hapdev_ctx_t *ctx, uint8_t rtp) {
//   writeRegister8(DRV2605_REG_RTPIN, rtp);
uint8_t reg = rtp;
  drv2605_write_reg(ctx, DRV2605_REG_RTPIN, &reg, 1);
}

// /**************************************************************************/
// /*!
//   @brief Read an 8-bit register.
//   @param reg The register to read.
//   @return 8-bit value of the register.
// */
// /**************************************************************************/
// uint8_t HapreadRegister8(uint8_t reg) {
//   uint8_t buffer[1] = {reg};
//   i2c_dev->write_then_read(buffer, 1, buffer, 1);
//   return buffer[0];
// }

// /**************************************************************************/
// /*!
//   @brief Write an 8-bit register.
//   @param reg The register to write.
//   @param val The value to write.
// */
// /**************************************************************************/
// void HapwriteRegister8(uint8_t reg, uint8_t val) {
//   uint8_t buffer[2] = {reg, val};
//   i2c_dev->write(buffer, 2);
// }

/**************************************************************************/
/*!
  @brief Use ERM (Eccentric Rotating Mass) mode.
*/
/**************************************************************************/
void drv2605_useERM(hapdev_ctx_t *ctx) {
    uint8_t reg;
//   writeRegister8(DRV2605_REG_FEEDBACK,
                //  readRegister8(DRV2605_REG_FEEDBACK) & 0x7F);
    drv2605_read_reg(ctx, ((DRV2605_REG_FEEDBACK) & (0x7F)), &reg, 1);
    drv2605_write_reg(ctx, DRV2605_REG_FEEDBACK, &reg, 1);
}

/**************************************************************************/
/*!
  @brief Use LRA (Linear Resonance Actuator) mode.
*/
/**************************************************************************/
void drv2605_useLRA(hapdev_ctx_t *ctx) {
//   writeRegister8(DRV2605_REG_FEEDBACK,
                //  readRegister8(DRV2605_REG_FEEDBACK) | 0x80);
                uint8_t reg;
    drv2605_read_reg(ctx, ((DRV2605_REG_FEEDBACK) | (0x80)), &reg, 1);
    drv2605_write_reg(ctx, DRV2605_REG_FEEDBACK, &reg, 1);
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
int32_t drv2605_write_reg(hapdev_ctx_t *ctx, uint8_t reg,
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
int32_t drv2605_read_reg(hapdev_ctx_t *ctx, uint8_t reg,
                         uint8_t *data,
                         uint16_t len)
{
  int32_t ret;

  ret = ctx->read_reg(ctx->handle, reg, data, len);

  return ret;
}


static int32_t platform_write(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len);

static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len);



hapdev_ctx_t dev_ctx_drv2605 = {.write_reg = platform_write, .read_reg = platform_read};

uint8_t msgOutHap[64]; ///<USE ME AS A BUFFER FOR platform_write and platform_read
I2C_Data HapData; ///<Use me as a structure to communicate with the IMU on platform_write and platform_read

/**************************************************************************//**
 * @fn			static int32_t platform_write(void *handle, uint8_t reg, uint8_t *bufp,uint16_t len)
 * @brief       Function to write data to a register
 * @details     Function to write data (bufp) to a register (reg)
				
 * @param[in]   handle IGNORE
 * @param[in]   reg Register to write to. In an I2C transaction, this gets sent first
 * @param[in]   bufp Pointer to the data to be sent
 * @param[in]   len Length of the data sent
 * @return      Returns what the function "I2cWriteDataWait" returns
*****************************************************************************/
static int32_t platform_write(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len)
{
  msgOutHap[0] = reg;
	for(uint16_t i=0; i < len; i++){
		msgOutHap[i+1] = bufp[i];
	}
	HapData.address = DRV2605_ADDR;
	HapData.msgOut = &msgOutHap;
	HapData.lenOut = len + 1;
	HapData.lenIn = len;
	HapData.msgIn = bufp;
  return I2cWriteDataWait(&HapData, 100, SERCOM_3);
}

/**************************************************************************//**
 * @fn			static  int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len)
 * @brief       Function to read data from a register
 * @details     Function to read data (bufp) from a register (reg)
				
 * @param[in]   handle IGNORE
 * @param[in]   reg Register to read from. In an I2C transaction, this gets sent first
 * @param[out]   bufp Pointer to the data to write to (write what was read)
 * @param[in]   len Length of the data to be read
 * @return      Returns what the function "I2cReadDataWait" returns
*****************************************************************************/
static  int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len)
{

	msgOutHap[0] = reg;
	HapData.address = DRV2605_ADDR;
	HapData.msgIn = bufp;
	HapData.lenIn = len;
	HapData.lenOut = 1;
	HapData.msgOut = &msgOutHap;
	
	return I2cReadDataWait(&HapData, 100, 100, SERCOM_3);
}


/**
 * @brief Retrieves a pointer to the haptic device context.
 * 
 * This function returns a pointer to the global haptic device context used for
 * managing haptic device operations and configurations.
 *
 * @return Pointer to the haptic device context.
 */
hapdev_ctx_t * GetHapStruct(void)
{
return &dev_ctx_drv2605;
}

/**
 * @brief Reads the status register of the haptic device.
 * 
 * This function reads the status register twice, once for each direction (left and right),
 * and combines the errors. It ensures the device direction is set back to none after the operations.
 *
 * @return Combined error status from both reads.
 */
uint8_t HapticreadStatusReg(void){
    uint8_t error = 0;
    select_dir(LEFT);
    error = drv2605_readStatusReg(&dev_ctx_drv2605);
    select_dir(RIGHT);
    error |= drv2605_readStatusReg(&dev_ctx_drv2605);
    select_dir(NONE_SELECT);
    return error;
}

/**
 * @brief Sets the output level for directional pins.
 * 
 * Selects the direction for the haptic output by setting the respective pins' output levels.
 * There's a delay after each pin setting to ensure the direction is set properly.
 *
 * @param dir The direction to set (LEFT, RIGHT, or NONE_SELECT).
 */
static void select_dir(enum direction dir){
    if(dir==LEFT){
        port_pin_set_output_level(LEFT_EN_PIN, true);
        vTaskDelay(5);
        port_pin_set_output_level(RIGHT_EN_PIN, false);
    }
    else if(dir==RIGHT){
      port_pin_set_output_level(RIGHT_EN_PIN, true);
      vTaskDelay(5);
      port_pin_set_output_level(LEFT_EN_PIN, false);
        
    }
    else{
        port_pin_set_output_level(LEFT_EN_PIN, false);
        port_pin_set_output_level(RIGHT_EN_PIN, false);
        vTaskDelay(5);
    }
}

/**
 * @brief Activates the haptic device in the specified direction.
 * 
 * Sets the direction, activates the haptic device, then resets the direction to none.
 * The function includes significant delays to ensure the action completes.
 *
 * @param dir The direction to activate the haptic device.
 */
void HapticGo_dir(enum direction dir){
    select_dir(dir);
    drv2605_go(&dev_ctx_drv2605);
    vTaskDelay(300);
    select_dir(NONE_SELECT);
}

/**
 * @brief Initializes the haptic feedback mechanisms.
 * 
 * Performs initial setup by setting the direction to left and right sequentially,
 * initializing the device each time. It ensures all settings are cleared by setting
 * the direction to none at the end.
 *
 * @return Combined result of initialization steps.
 */
int32_t InitHaptic(){
    uint32_t error = 0;
    select_dir(LEFT);
    error = Init();
    delay_ms(500);
    select_dir(RIGHT);
    error &= Init();
    delay_ms(500);
    select_dir(NONE_SELECT);
    return error;
}


/**
 * @brief Internal function to initialize the haptic driver.
 * 
 * Sets up the haptic driver with a specific library, mode, and waveform settings.
 * Includes a delay to ensure settings take effect.
 *
 * @return Error status (0 if no errors).
 */
static int32_t Init(void)
{
uint8_t rst;
int32_t error = 0;
    drv2605_selectLibrary(&dev_ctx_drv2605, 1);
    drv2605_setMode(&dev_ctx_drv2605, DRV2605_MODE_INTTRIG);
    drv2605_setWaveform(&dev_ctx_drv2605, 0, 1);
    drv2605_setWaveform(&dev_ctx_drv2605, 1, 0);
    delay_ms(500);
    // drv2605_go(&dev_ctx_drv2605);
  return error;
}
