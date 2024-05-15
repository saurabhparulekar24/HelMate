/**
  ******************************************************************************
  * @file    lis2dh_reg.c
  * @author  Sensors Software Solution Team
  * @brief   LIS2DH driver file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  * NOTE: THe file is licensed by the above license, I have added function to make it compatible with SAMD21.
  * Also added updated "lis2dh_read_reg" function to work correctly, look under the brief in the function for complete details
  */

#include "lis2dh_reg.h"
#include "I2cDriver\I2cDriver.h"

/**
  * @defgroup  LIS2DH
  * @brief     This file provides a set of functions needed to drive the
  *            lis2dh enanced inertial module.
  * @{
  *
  */

/**
  * @defgroup  LIS2DH_Interfaces_Functions
  * @brief     This section provide a set of functions used to read and
  *            write a generic register of the device.
  *            MANDATORY: return 0 -> no Error.
  * @{
  *
  */

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
int32_t __weak lis2dh_read_reg(const stmdev_ctx_t *ctx, uint8_t reg,
                               uint8_t *data,
                               uint16_t len)
{
  int32_t ret;

  if (ctx == NULL)
  {
    return -1;
  }

  ret = ctx->read_reg(ctx->handle, reg, data, len);

  return ret;
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
int32_t __weak lis2dh_write_reg(const stmdev_ctx_t *ctx, uint8_t reg,
                                uint8_t *data,
                                uint16_t len)
{
  int32_t ret;

  if (ctx == NULL)
  {
    return -1;
  }

  ret = ctx->write_reg(ctx->handle, reg, data, len);

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup    LIS2DH_Sensitivity
  * @brief       These functions convert raw-data into engineering units.
  * @{
  *
  */

float_t lis2dh_from_fs2_hr_to_mg(int16_t lsb)
{
  return ((float_t)lsb / 16.0f) * 1.0f;
}

float_t lis2dh_from_fs4_hr_to_mg(int16_t lsb)
{
  return ((float_t)lsb / 16.0f) *  2.0f;
}

float_t lis2dh_from_fs8_hr_to_mg(int16_t lsb)
{
  return ((float_t)lsb / 16.0f) * 4.0f;
}

float_t lis2dh_from_fs16_hr_to_mg(int16_t lsb)
{
  return ((float_t)lsb / 16.0f) * 12.0f;
}

float_t lis2dh_from_lsb_hr_to_celsius(int16_t lsb)
{
  return (((float_t)lsb / 64.0f) / 4.0f) + 25.0f;
}

float_t lis2dh_from_fs2_nm_to_mg(int16_t lsb)
{
  return ((float_t)lsb / 64.0f) *  4.0f;
}

float_t lis2dh_from_fs4_nm_to_mg(int16_t lsb)
{
  return ((float_t)lsb / 64.0f) *  8.0f;
}

float_t lis2dh_from_fs8_nm_to_mg(int16_t lsb)
{
  return ((float_t)lsb / 64.0f) * 16.0f;
}

float_t lis2dh_from_fs16_nm_to_mg(int16_t lsb)
{
  return ((float_t)lsb / 64.0f) * 48.0f;
}

float_t lis2dh_from_lsb_nm_to_celsius(int16_t lsb)
{
  return (((float_t)lsb / 64.0f) / 4.0f) + 25.0f;
}

float_t lis2dh_from_fs2_lp_to_mg(int16_t lsb)
{
  return ((float_t)lsb / 256.0f) * 16.0f;
}

float_t lis2dh_from_fs4_lp_to_mg(int16_t lsb)
{
  return ((float_t)lsb / 256.0f) * 32.0f;
}

float_t lis2dh_from_fs8_lp_to_mg(int16_t lsb)
{
  return ((float_t)lsb / 256.0f) * 64.0f;
}

float_t lis2dh_from_fs16_lp_to_mg(int16_t lsb)
{
  return ((float_t)lsb / 256.0f) * 192.0f;
}

float_t lis2dh_from_lsb_lp_to_celsius(int16_t lsb)
{
  return (((float_t)lsb / 256.0f) * 1.0f) + 25.0f;
}

/**
  * @}
  *
  */

/**
  * @defgroup  LIS2DH_Data_generation
  * @brief     This section group all the functions concerning data generation.
  * @{
  *
  */

/**
  * @brief  Interrupt event counter.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      get the value of INT_COUNTER
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_int_count_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_INT_COUNTER, val, 1);

  return ret;
}

/**
  * @brief  Temperature status register.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  buff     buffer that stores data read
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_temp_status_reg_get(const stmdev_ctx_t *ctx, uint8_t *buff)
{
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_STATUS_REG_AUX, buff, 1);

  return ret;
}
/**
  * @brief  Temperature data available.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of tda in reg STATUS_REG_AUX
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_temp_data_ready_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lis2dh_status_reg_aux_t status_reg_aux;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_STATUS_REG_AUX,
                        (uint8_t *)&status_reg_aux, 1);
  *val = status_reg_aux.tda;

  return ret;
}

/**
  * @brief  Temperature data overrun.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of tor in reg STATUS_REG_AUX
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_temp_data_ovr_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lis2dh_status_reg_aux_t status_reg_aux;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_STATUS_REG_AUX,
                        (uint8_t *)&status_reg_aux, 1);
  *val = status_reg_aux.tor;

  return ret;
}
/**
  * @brief  Temperature output value.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  buff     buffer that stores data read
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_temperature_raw_get(const stmdev_ctx_t *ctx, int16_t *val)
{
  uint8_t buff[2];
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_OUT_TEMP_L, buff, 2);
  *val = (int16_t)buff[1];
  *val = (*val * 256) + (int16_t)buff[0];

  return ret;
}
/**
  * @brief  Temperature sensor enable.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of temp_en in reg TEMP_CFG_REG
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_temperature_meas_set(const stmdev_ctx_t *ctx,
                                    lis2dh_temp_en_t val)
{
  lis2dh_temp_cfg_reg_t temp_cfg_reg;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_TEMP_CFG_REG,
                        (uint8_t *)&temp_cfg_reg, 1);

  if (ret == 0)
  {
    temp_cfg_reg.temp_en = (uint8_t) val;
    ret = lis2dh_write_reg(ctx, LIS2DH_TEMP_CFG_REG,
                           (uint8_t *)&temp_cfg_reg, 1);
  }

  return ret;
}

/**
  * @brief  Temperature sensor enable.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      get the values of temp_en in reg TEMP_CFG_REG
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_temperature_meas_get(const stmdev_ctx_t *ctx,
                                    lis2dh_temp_en_t *val)
{
  lis2dh_temp_cfg_reg_t temp_cfg_reg;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_TEMP_CFG_REG,
                        (uint8_t *)&temp_cfg_reg, 1);

  switch (temp_cfg_reg.temp_en)
  {
    case LIS2DH_TEMP_DISABLE:
      *val = LIS2DH_TEMP_DISABLE;
      break;

    case LIS2DH_TEMP_ENABLE:
      *val = LIS2DH_TEMP_ENABLE;
      break;

    default:
      *val = LIS2DH_TEMP_DISABLE;
      break;
  }

  return ret;
}

/**
  * @brief  Operating mode selection.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of lpen in reg CTRL_REG1
  *                  and HR in reg CTRL_REG4
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_operating_mode_set(const stmdev_ctx_t *ctx,
                                  lis2dh_op_md_t val)
{
  lis2dh_ctrl_reg1_t ctrl_reg1;
  lis2dh_ctrl_reg4_t ctrl_reg4;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_CTRL_REG1,
                        (uint8_t *)&ctrl_reg1, 1);

  if (ret == 0)
  {
    ret = lis2dh_read_reg(ctx, LIS2DH_CTRL_REG4,
                          (uint8_t *)&ctrl_reg4, 1);
  }

  if (ret == 0)
  {
    if (val == LIS2DH_HR_12bit)
    {
      ctrl_reg1.lpen = 0;
      ctrl_reg4.hr   = 1;
    }

    if (val == LIS2DH_NM_10bit)
    {
      ctrl_reg1.lpen = 0;
      ctrl_reg4.hr   = 0;
    }

    if (val == LIS2DH_LP_8bit)
    {
      ctrl_reg1.lpen = 1;
      ctrl_reg4.hr   = 0;
    }

    ret = lis2dh_write_reg(ctx, LIS2DH_CTRL_REG1,
                           (uint8_t *)&ctrl_reg1, 1);
  }

  if (ret == 0)
  {
    ret = lis2dh_write_reg(ctx, LIS2DH_CTRL_REG4,
                           (uint8_t *)&ctrl_reg4, 1);
  }

  return ret;
}

/**
  * @brief  Operating mode selection.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of lpen in reg CTRL_REG1
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_operating_mode_get(const stmdev_ctx_t *ctx,
                                  lis2dh_op_md_t *val)
{
  lis2dh_ctrl_reg1_t ctrl_reg1;
  lis2dh_ctrl_reg4_t ctrl_reg4;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_CTRL_REG1,
                        (uint8_t *)&ctrl_reg1, 1);

  if (ret == 0)
  {
    ret = lis2dh_read_reg(ctx, LIS2DH_CTRL_REG4,
                          (uint8_t *)&ctrl_reg4, 1);

    if (ctrl_reg1.lpen == PROPERTY_ENABLE)
    {
      *val = LIS2DH_LP_8bit;
    }

    else if (ctrl_reg4.hr == PROPERTY_ENABLE)
    {
      *val = LIS2DH_HR_12bit;
    }

    else
    {
      *val = LIS2DH_NM_10bit;
    }
  }

  return ret;
}

/**
  * @brief  Output data rate selection.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of odr in reg CTRL_REG1
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_data_rate_set(const stmdev_ctx_t *ctx, lis2dh_odr_t val)
{
  lis2dh_ctrl_reg1_t ctrl_reg1;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_CTRL_REG1,
                        (uint8_t *)&ctrl_reg1, 1);

  if (ret == 0)
  {
    ctrl_reg1.odr = (uint8_t)val;
    ret = lis2dh_write_reg(ctx, LIS2DH_CTRL_REG1,
                           (uint8_t *)&ctrl_reg1, 1);
  }

  return ret;
}

/**
  * @brief  Output data rate selection.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      get the values of odr in reg CTRL_REG1
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_data_rate_get(const stmdev_ctx_t *ctx, lis2dh_odr_t *val)
{
  lis2dh_ctrl_reg1_t ctrl_reg1;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_CTRL_REG1,
                        (uint8_t *)&ctrl_reg1, 1);

  switch (ctrl_reg1.odr)
  {
    case LIS2DH_POWER_DOWN:
      *val = LIS2DH_POWER_DOWN;
      break;

    case LIS2DH_ODR_1Hz:
      *val = LIS2DH_ODR_1Hz;
      break;

    case LIS2DH_ODR_10Hz:
      *val = LIS2DH_ODR_10Hz;
      break;

    case LIS2DH_ODR_25Hz:
      *val = LIS2DH_ODR_25Hz;
      break;

    case LIS2DH_ODR_50Hz:
      *val = LIS2DH_ODR_50Hz;
      break;

    case LIS2DH_ODR_100Hz:
      *val = LIS2DH_ODR_100Hz;
      break;

    case LIS2DH_ODR_200Hz:
      *val = LIS2DH_ODR_200Hz;
      break;

    case LIS2DH_ODR_400Hz:
      *val = LIS2DH_ODR_400Hz;
      break;

    case LIS2DH_ODR_1kHz620_LP:
      *val = LIS2DH_ODR_1kHz620_LP;
      break;

    case LIS2DH_ODR_5kHz376_LP_1kHz344_NM_HP:
      *val = LIS2DH_ODR_5kHz376_LP_1kHz344_NM_HP;
      break;

    default:
      *val = LIS2DH_POWER_DOWN;
      break;
  }

  return ret;
}

/**
  * @brief   High pass data from internal filter sent to output register
  *          and FIFO.
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of fds in reg CTRL_REG2
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_high_pass_on_outputs_set(const stmdev_ctx_t *ctx,
                                        uint8_t val)
{
  lis2dh_ctrl_reg2_t ctrl_reg2;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_CTRL_REG2,
                        (uint8_t *)&ctrl_reg2, 1);

  if (ret == 0)
  {
    ctrl_reg2.fds = val;
    ret = lis2dh_write_reg(ctx, LIS2DH_CTRL_REG2,
                           (uint8_t *)&ctrl_reg2, 1);
  }

  return ret;
}

/**
  * @brief   High pass data from internal filter sent to output register
  *          and FIFO.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of fds in reg CTRL_REG2
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_high_pass_on_outputs_get(const stmdev_ctx_t *ctx,
                                        uint8_t *val)
{
  lis2dh_ctrl_reg2_t ctrl_reg2;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_CTRL_REG2,
                        (uint8_t *)&ctrl_reg2, 1);
  *val = (uint8_t)ctrl_reg2.fds;

  return ret;
}

/**
  * @brief   High-pass filter cutoff frequency selection.[set]
  *
  * HPCF[2:1]\ft @1Hz    @10Hz  @25Hz  @50Hz @100Hz @200Hz @400Hz @1kHz6 ft@5kHz
  * AGGRESSIVE   0.02Hz  0.2Hz  0.5Hz  1Hz   2Hz    4Hz    8Hz    32Hz   100Hz
  * STRONG       0.008Hz 0.08Hz 0.2Hz  0.5Hz 1Hz    2Hz    4Hz    16Hz   50Hz
  * MEDIUM       0.004Hz 0.04Hz 0.1Hz  0.2Hz 0.5Hz  1Hz    2Hz    8Hz    25Hz
  * LIGHT        0.002Hz 0.02Hz 0.05Hz 0.1Hz 0.2Hz  0.5Hz  1Hz    4Hz    12Hz
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of hpcf in reg CTRL_REG2
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_high_pass_bandwidth_set(const stmdev_ctx_t *ctx,
                                       lis2dh_hpcf_t val)
{
  lis2dh_ctrl_reg2_t ctrl_reg2;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_CTRL_REG2,
                        (uint8_t *)&ctrl_reg2, 1);

  if (ret == 0)
  {
    ctrl_reg2.hpcf = (uint8_t)val;
    ret = lis2dh_write_reg(ctx, LIS2DH_CTRL_REG2,
                           (uint8_t *)&ctrl_reg2, 1);
  }

  return ret;
}

/**
  * @brief   High-pass filter cutoff frequency selection.[get]
  *
  * HPCF[2:1]\ft @1Hz    @10Hz  @25Hz  @50Hz @100Hz @200Hz @400Hz @1kHz6 ft@5kHz
  * AGGRESSIVE   0.02Hz  0.2Hz  0.5Hz  1Hz   2Hz    4Hz    8Hz    32Hz   100Hz
  * STRONG       0.008Hz 0.08Hz 0.2Hz  0.5Hz 1Hz    2Hz    4Hz    16Hz   50Hz
  * MEDIUM       0.004Hz 0.04Hz 0.1Hz  0.2Hz 0.5Hz  1Hz    2Hz    8Hz    25Hz
  * LIGHT        0.002Hz 0.02Hz 0.05Hz 0.1Hz 0.2Hz  0.5Hz  1Hz    4Hz    12Hz
  *
  * @param  ctx      read / write interface definitions
  * @param  val      get the values of hpcf in reg CTRL_REG2
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_high_pass_bandwidth_get(const stmdev_ctx_t *ctx,
                                       lis2dh_hpcf_t *val)
{
  lis2dh_ctrl_reg2_t ctrl_reg2;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_CTRL_REG2,
                        (uint8_t *)&ctrl_reg2, 1);

  switch (ctrl_reg2.hpcf)
  {
    case LIS2DH_AGGRESSIVE:
      *val = LIS2DH_AGGRESSIVE;
      break;

    case LIS2DH_STRONG:
      *val = LIS2DH_STRONG;
      break;

    case LIS2DH_MEDIUM:
      *val = LIS2DH_MEDIUM;
      break;

    case LIS2DH_LIGHT:
      *val = LIS2DH_LIGHT;
      break;

    default:
      *val = LIS2DH_LIGHT;
      break;
  }

  return ret;
}

/**
  * @brief  High-pass filter mode selection.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of hpm in reg CTRL_REG2
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_high_pass_mode_set(const stmdev_ctx_t *ctx,
                                  lis2dh_hpm_t val)
{
  lis2dh_ctrl_reg2_t ctrl_reg2;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_CTRL_REG2,
                        (uint8_t *)&ctrl_reg2, 1);

  if (ret == 0)
  {
    ctrl_reg2.hpm = (uint8_t)val;
    ret = lis2dh_write_reg(ctx, LIS2DH_CTRL_REG2,
                           (uint8_t *)&ctrl_reg2, 1);
  }

  return ret;
}

/**
  * @brief  High-pass filter mode selection.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      get the values of hpm in reg CTRL_REG2
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_high_pass_mode_get(const stmdev_ctx_t *ctx,
                                  lis2dh_hpm_t *val)
{
  lis2dh_ctrl_reg2_t ctrl_reg2;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_CTRL_REG2,
                        (uint8_t *)&ctrl_reg2, 1);

  switch (ctrl_reg2.hpm)
  {
    case LIS2DH_NORMAL_WITH_RST:
      *val = LIS2DH_NORMAL_WITH_RST;
      break;

    case LIS2DH_REFERENCE_MODE:
      *val = LIS2DH_REFERENCE_MODE;
      break;

    case LIS2DH_NORMAL:
      *val = LIS2DH_NORMAL;
      break;

    case LIS2DH_AUTORST_ON_INT:
      *val = LIS2DH_AUTORST_ON_INT;
      break;

    default:
      *val = LIS2DH_NORMAL_WITH_RST;
      break;
  }

  return ret;
}

/**
  * @brief  Full-scale configuration.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of fs in reg CTRL_REG4
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_full_scale_set(const stmdev_ctx_t *ctx, lis2dh_fs_t val)
{
  lis2dh_ctrl_reg4_t ctrl_reg4;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_CTRL_REG4,
                        (uint8_t *)&ctrl_reg4, 1);

  if (ret == 0)
  {
    ctrl_reg4.fs = (uint8_t)val;
    ret = lis2dh_write_reg(ctx, LIS2DH_CTRL_REG4,
                           (uint8_t *)&ctrl_reg4, 1);
  }

  return ret;
}

/**
  * @brief  Full-scale configuration.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      get the values of fs in reg CTRL_REG4
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_full_scale_get(const stmdev_ctx_t *ctx, lis2dh_fs_t *val)
{
  lis2dh_ctrl_reg4_t ctrl_reg4;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_CTRL_REG4,
                        (uint8_t *)&ctrl_reg4, 1);

  switch (ctrl_reg4.fs)
  {
    case LIS2DH_2g:
      *val = LIS2DH_2g;
      break;

    case LIS2DH_4g:
      *val = LIS2DH_4g;
      break;

    case LIS2DH_8g:
      *val = LIS2DH_8g;
      break;

    case LIS2DH_16g:
      *val = LIS2DH_16g;
      break;

    default:
      *val = LIS2DH_2g;
      break;
  }

  return ret;
}

/**
  * @brief  Block Data Update.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of bdu in reg CTRL_REG4
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_block_data_update_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lis2dh_ctrl_reg4_t ctrl_reg4;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_CTRL_REG4,
                        (uint8_t *)&ctrl_reg4, 1);

  if (ret == 0)
  {
    ctrl_reg4.bdu = val;
    ret = lis2dh_write_reg(ctx, LIS2DH_CTRL_REG4,
                           (uint8_t *)&ctrl_reg4, 1);
  }

  return ret;
}

/**
  * @brief  Block Data Update.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of bdu in reg CTRL_REG4
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_block_data_update_get(const stmdev_ctx_t *ctx,
                                     uint8_t *val)
{
  lis2dh_ctrl_reg4_t ctrl_reg4;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_CTRL_REG4,
                        (uint8_t *)&ctrl_reg4, 1);
  *val = (uint8_t)ctrl_reg4.bdu;

  return ret;
}

/**
  * @brief  Reference value for interrupt generation.[set]
  *         LSB = ~16@2g / ~31@4g / ~63@8g / ~127@16g
  *
  * @param  ctx      read / write interface definitions
  * @param  buff     buffer that contains data to write
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_filter_reference_set(const stmdev_ctx_t *ctx,
                                    uint8_t *buff)
{
  int32_t ret;

  ret = lis2dh_write_reg(ctx, LIS2DH_REFERENCE, buff, 1);

  return ret;
}

/**
  * @brief  Reference value for interrupt generation.[get]
  *         LSB = ~16@2g / ~31@4g / ~63@8g / ~127@16g
  *
  * @param  ctx      read / write interface definitions
  * @param  buff     buffer that stores data read
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_filter_reference_get(const stmdev_ctx_t *ctx,
                                    uint8_t *buff)
{
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_REFERENCE, buff, 1);

  return ret;
}
/**
  * @brief  Acceleration set of data available.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of zyxda in reg STATUS_REG
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_xl_data_ready_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lis2dh_status_reg_t status_reg;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_STATUS_REG,
                        (uint8_t *)&status_reg, 1);
  *val = status_reg.zyxda;

  return ret;
}
/**
  * @brief  Acceleration set of data overrun.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of zyxor in reg STATUS_REG
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_xl_data_ovr_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lis2dh_status_reg_t status_reg;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_STATUS_REG,
                        (uint8_t *)&status_reg, 1);
  *val = status_reg.zyxor;

  return ret;
}
/**
  * @brief  Acceleration output value.[get]
  * This function reads all the XYZ registers of the accelerometer, when sending the command the MSB should be 1 for the command to 
  * increment automatically, hence ORed 0x80 with the command, go to link below for more info
  * https://community.st.com/t5/mems-sensors/lis2dh12-returns-constant-data-using-stmems-driver-read-data/td-p/198567
  * @param  ctx      read / write interface definitions
  * @param  buff     buffer that stores data read
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_acceleration_raw_get(const stmdev_ctx_t *ctx, int16_t *val)
{
  uint8_t buff[6];
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_OUT_X_L | 0x80, buff, 6);
  val[0] = (int16_t)buff[1];
  val[0] = (val[0] * 256) + (int16_t)buff[0];
  val[1] = (int16_t)buff[3];
  val[1] = (val[1] * 256) + (int16_t)buff[2];
  val[2] = (int16_t)buff[5];
  val[2] = (val[2] * 256) + (int16_t)buff[4];

  return ret;
}
/**
  * @}
  *
  */

/**
  * @defgroup  LIS2DH_Common
  * @brief     This section group common useful functions
  * @{
  *
  */

/**
  * @brief  DeviceWhoamI .[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  buff     buffer that stores data read
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_device_id_get(const stmdev_ctx_t *ctx, uint8_t *buff)
{
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_WHO_AM_I, buff, 1);

  return ret;
}
/**
  * @brief  Self Test.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of st in reg CTRL_REG4
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_self_test_set(const stmdev_ctx_t *ctx, lis2dh_st_t val)
{
  lis2dh_ctrl_reg4_t ctrl_reg4;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_CTRL_REG4,
                        (uint8_t *)&ctrl_reg4, 1);

  if (ret == 0)
  {
    ctrl_reg4.st = (uint8_t)val;
    ret = lis2dh_write_reg(ctx, LIS2DH_CTRL_REG4,
                           (uint8_t *)&ctrl_reg4, 1);
  }

  return ret;
}

/**
  * @brief  Self Test.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of st in reg CTRL_REG4
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_self_test_get(const stmdev_ctx_t *ctx, lis2dh_st_t *val)
{
  lis2dh_ctrl_reg4_t ctrl_reg4;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_CTRL_REG4,
                        (uint8_t *)&ctrl_reg4, 1);

  switch (ctrl_reg4.st)
  {
    case LIS2DH_ST_DISABLE:
      *val = LIS2DH_ST_DISABLE;
      break;

    case LIS2DH_ST_POSITIVE:
      *val = LIS2DH_ST_POSITIVE;
      break;

    case LIS2DH_ST_NEGATIVE:
      *val = LIS2DH_ST_NEGATIVE;
      break;

    default:
      *val = LIS2DH_ST_DISABLE;
      break;
  }

  return ret;
}

/**
  * @brief  Big/Little Endian data selection.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of ble in reg CTRL_REG4
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_data_format_set(const stmdev_ctx_t *ctx,
                               lis2dh_ble_t val)
{
  lis2dh_ctrl_reg4_t ctrl_reg4;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_CTRL_REG4,
                        (uint8_t *)&ctrl_reg4, 1);

  if (ret == 0)
  {
    ctrl_reg4.ble = (uint8_t)val;
    ret = lis2dh_write_reg(ctx, LIS2DH_CTRL_REG4,
                           (uint8_t *)&ctrl_reg4, 1);
  }

  return ret;
}

/**
  * @brief  Big/Little Endian data selection.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      get the values of ble in reg CTRL_REG4
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_data_format_get(const stmdev_ctx_t *ctx,
                               lis2dh_ble_t *val)
{
  lis2dh_ctrl_reg4_t ctrl_reg4;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_CTRL_REG4,
                        (uint8_t *)&ctrl_reg4, 1);

  switch (ctrl_reg4.ble)
  {
    case LIS2DH_LSB_AT_LOW_ADD:
      *val = LIS2DH_LSB_AT_LOW_ADD;
      break;

    case LIS2DH_MSB_AT_LOW_ADD:
      *val = LIS2DH_MSB_AT_LOW_ADD;
      break;

    default:
      *val = LIS2DH_LSB_AT_LOW_ADD;
      break;
  }

  return ret;
}

/**
  * @brief  Reboot memory content. Reload the calibration parameters.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of boot in reg CTRL_REG5
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_boot_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lis2dh_ctrl_reg5_t ctrl_reg5;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_CTRL_REG5,
                        (uint8_t *)&ctrl_reg5, 1);

  if (ret == 0)
  {
    ctrl_reg5.boot = val;
    ret = lis2dh_write_reg(ctx, LIS2DH_CTRL_REG5,
                           (uint8_t *)&ctrl_reg5, 1);
  }

  return ret;
}

/**
  * @brief  Reboot memory content. Reload the calibration parameters.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of boot in reg CTRL_REG5
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_boot_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lis2dh_ctrl_reg5_t ctrl_reg5;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_CTRL_REG5,
                        (uint8_t *)&ctrl_reg5, 1);
  *val = (uint8_t)ctrl_reg5.boot;

  return ret;
}

/**
  * @brief  Info about device status.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      register STATUS_REG
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_status_get(const stmdev_ctx_t *ctx,
                          lis2dh_status_reg_t *val)
{
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_STATUS_REG, (uint8_t *) val, 1);

  return ret;
}
/**
  * @}
  *
  */

/**
  * @defgroup   LIS2DH_Interrupts_generator_1
  * @brief      This section group all the functions that manage the first
  *             interrupts generator
  * @{
  *
  */

/**
  * @brief  Interrupt generator 1 configuration register.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      register INT1_CFG
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_int1_gen_conf_set(const stmdev_ctx_t *ctx,
                                 lis2dh_int1_cfg_t *val)
{
  int32_t ret;

  ret = lis2dh_write_reg(ctx, LIS2DH_INT1_CFG, (uint8_t *) val, 1);

  return ret;
}

/**
  * @brief  Interrupt generator 1 configuration register.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      register INT1_CFG
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_int1_gen_conf_get(const stmdev_ctx_t *ctx,
                                 lis2dh_int1_cfg_t *val)
{
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_INT1_CFG, (uint8_t *) val, 1);

  return ret;
}

/**
  * @brief  Interrupt generator 1 source register.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Registers INT1_SRC
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_int1_gen_source_get(const stmdev_ctx_t *ctx,
                                   lis2dh_int1_src_t *val)
{
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_INT1_SRC, (uint8_t *) val, 1);

  return ret;
}
/**
  * @brief  User-defined threshold value for xl interrupt event on
  *         generator 1.[set]
  *         LSb = 16mg@2g / 32mg@4g / 62mg@8g / 186mg@16g
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of ths in reg INT1_THS
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_int1_gen_threshold_set(const stmdev_ctx_t *ctx,
                                      uint8_t val)
{
  lis2dh_int1_ths_t int1_ths;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_INT1_THS, (uint8_t *)&int1_ths, 1);

  if (ret == 0)
  {
    int1_ths.ths = val;
    ret = lis2dh_write_reg(ctx, LIS2DH_INT1_THS, (uint8_t *)&int1_ths, 1);
  }

  return ret;
}

/**
  * @brief  User-defined threshold value for xl interrupt event on
  *         generator 1.[get]
  *         LSb = 16mg@2g / 32mg@4g / 62mg@8g / 186mg@16g
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of ths in reg INT1_THS
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_int1_gen_threshold_get(const stmdev_ctx_t *ctx,
                                      uint8_t *val)
{
  lis2dh_int1_ths_t int1_ths;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_INT1_THS, (uint8_t *)&int1_ths, 1);
  *val = (uint8_t)int1_ths.ths;

  return ret;
}

/**
  * @brief  The minimum duration (LSb = 1/ODR) of the Interrupt 1 event to be
  *         recognized.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of d in reg INT1_DURATION
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_int1_gen_duration_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lis2dh_int1_duration_t int1_duration;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_INT1_DURATION,
                        (uint8_t *)&int1_duration, 1);

  if (ret == 0)
  {
    int1_duration.d = val;
    ret = lis2dh_write_reg(ctx, LIS2DH_INT1_DURATION,
                           (uint8_t *)&int1_duration, 1);
  }

  return ret;
}

/**
  * @brief  The minimum duration (LSb = 1/ODR) of the Interrupt 1 event to be
  *         recognized.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of d in reg INT1_DURATION
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_int1_gen_duration_get(const stmdev_ctx_t *ctx,
                                     uint8_t *val)
{
  lis2dh_int1_duration_t int1_duration;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_INT1_DURATION,
                        (uint8_t *)&int1_duration, 1);
  *val = (uint8_t)int1_duration.d;

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup   LIS2DH_Interrupts_generator_2
  * @brief      This section group all the functions that manage the second
  *             interrupts generator
  * @{
  *
  */

/**
  * @brief  Interrupt generator 2 configuration register.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      registers INT2_CFG
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_int2_gen_conf_set(const stmdev_ctx_t *ctx,
                                 lis2dh_int2_cfg_t *val)
{
  int32_t ret;

  ret = lis2dh_write_reg(ctx, LIS2DH_INT2_CFG, (uint8_t *) val, 1);

  return ret;
}

/**
  * @brief  Interrupt generator 2 configuration register.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      registers INT2_CFG
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_int2_gen_conf_get(const stmdev_ctx_t *ctx,
                                 lis2dh_int2_cfg_t *val)
{
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_INT2_CFG, (uint8_t *) val, 1);

  return ret;
}
/**
  * @brief  Interrupt generator 2 source register.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      registers INT2_SRC
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_int2_gen_source_get(const stmdev_ctx_t *ctx,
                                   lis2dh_int2_src_t *val)
{
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_INT2_SRC, (uint8_t *) val, 1);

  return ret;
}
/**
  * @brief   User-defined threshold value for xl interrupt event on
  *          generator 2.[set]
  *          LSb = 16mg@2g / 32mg@4g / 62mg@8g / 186mg@16g
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of ths in reg INT2_THS
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_int2_gen_threshold_set(const stmdev_ctx_t *ctx,
                                      uint8_t val)
{
  lis2dh_int2_ths_t int2_ths;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_INT2_THS, (uint8_t *)&int2_ths, 1);

  if (ret == 0)
  {
    int2_ths.ths = val;
    ret = lis2dh_write_reg(ctx, LIS2DH_INT2_THS, (uint8_t *)&int2_ths, 1);
  }

  return ret;
}

/**
  * @brief  User-defined threshold value for xl interrupt event on
  *         generator 2.[get]
  *         LSb = 16mg@2g / 32mg@4g / 62mg@8g / 186mg@16g
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of ths in reg INT2_THS
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_int2_gen_threshold_get(const stmdev_ctx_t *ctx,
                                      uint8_t *val)
{
  lis2dh_int2_ths_t int2_ths;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_INT2_THS, (uint8_t *)&int2_ths, 1);
  *val = (uint8_t)int2_ths.ths;

  return ret;
}

/**
  * @brief  The minimum duration (LSb = 1/ODR) of the Interrupt 1 event to be
  *         recognized .[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of d in reg INT2_DURATION
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_int2_gen_duration_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lis2dh_int2_duration_t int2_duration;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_INT2_DURATION,
                        (uint8_t *)&int2_duration, 1);

  if (ret == 0)
  {
    int2_duration.d = val;
    ret = lis2dh_write_reg(ctx, LIS2DH_INT2_DURATION,
                           (uint8_t *)&int2_duration, 1);
  }

  return ret;
}

/**
  * @brief  The minimum duration (LSb = 1/ODR) of the Interrupt 1 event to be
  *         recognized.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of d in reg INT2_DURATION
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_int2_gen_duration_get(const stmdev_ctx_t *ctx,
                                     uint8_t *val)
{
  lis2dh_int2_duration_t int2_duration;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_INT2_DURATION,
                        (uint8_t *)&int2_duration, 1);
  *val = (uint8_t)int2_duration.d;

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup  LIS2DH_Interrupt_pins
  * @brief     This section group all the functions that manage interrupt pins
  * @{
  *
  */

/**
  * @brief  High-pass filter on interrupts/tap generator.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of hp in reg CTRL_REG2
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_high_pass_int_conf_set(const stmdev_ctx_t *ctx,
                                      lis2dh_hp_t val)
{
  lis2dh_ctrl_reg2_t ctrl_reg2;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_CTRL_REG2,
                        (uint8_t *)&ctrl_reg2, 1);

  if (ret == 0)
  {
    ctrl_reg2.hp = (uint8_t)val;
    ret = lis2dh_write_reg(ctx, LIS2DH_CTRL_REG2,
                           (uint8_t *)&ctrl_reg2, 1);
  }

  return ret;
}

/**
  * @brief  High-pass filter on interrupts/tap generator.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of hp in reg CTRL_REG2
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_high_pass_int_conf_get(const stmdev_ctx_t *ctx,
                                      lis2dh_hp_t *val)
{
  lis2dh_ctrl_reg2_t ctrl_reg2;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_CTRL_REG2,
                        (uint8_t *)&ctrl_reg2, 1);

  switch (ctrl_reg2.hp)
  {
    case LIS2DH_DISC_FROM_INT_GENERATOR:
      *val = LIS2DH_DISC_FROM_INT_GENERATOR;
      break;

    case LIS2DH_ON_INT1_GEN:
      *val = LIS2DH_ON_INT1_GEN;
      break;

    case LIS2DH_ON_INT2_GEN:
      *val = LIS2DH_ON_INT2_GEN;
      break;

    case LIS2DH_ON_TAP_GEN:
      *val = LIS2DH_ON_TAP_GEN;
      break;

    case LIS2DH_ON_INT1_INT2_GEN:
      *val = LIS2DH_ON_INT1_INT2_GEN;
      break;

    case LIS2DH_ON_INT1_TAP_GEN:
      *val = LIS2DH_ON_INT1_TAP_GEN;
      break;

    case LIS2DH_ON_INT2_TAP_GEN:
      *val = LIS2DH_ON_INT2_TAP_GEN;
      break;

    case LIS2DH_ON_INT1_INT2_TAP_GEN:
      *val = LIS2DH_ON_INT1_INT2_TAP_GEN;
      break;

    default:
      *val = LIS2DH_DISC_FROM_INT_GENERATOR;
      break;
  }

  return ret;
}

/**
  * @brief  Int1 pin routing configuration register.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      registers CTRL_REG3
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_pin_int1_config_set(const stmdev_ctx_t *ctx,
                                   lis2dh_ctrl_reg3_t *val)
{
  int32_t ret;

  ret = lis2dh_write_reg(ctx, LIS2DH_CTRL_REG3, (uint8_t *) val, 1);

  return ret;
}

/**
  * @brief  Int1 pin routing configuration register.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      registers CTRL_REG3
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_pin_int1_config_get(const stmdev_ctx_t *ctx,
                                   lis2dh_ctrl_reg3_t *val)
{
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_CTRL_REG3, (uint8_t *) val, 1);

  return ret;
}
/**
  * @brief  int2_pin_detect_4d: [set]  4D enable: 4D detection is enabled
  *                                    on INT2 pin when 6D bit on
  *                                    INT2_CFG (34h) is set to 1.
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of d4d_int2 in reg CTRL_REG5
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_int2_pin_detect_4d_set(const stmdev_ctx_t *ctx,
                                      uint8_t val)
{
  lis2dh_ctrl_reg5_t ctrl_reg5;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_CTRL_REG5,
                        (uint8_t *)&ctrl_reg5, 1);

  if (ret == 0)
  {
    ctrl_reg5.d4d_int2 = val;
    ret = lis2dh_write_reg(ctx, LIS2DH_CTRL_REG5,
                           (uint8_t *)&ctrl_reg5, 1);
  }

  return ret;
}

/**
  * @brief  4D enable: 4D detection is enabled on INT2 pin when 6D bit on
  *         INT2_CFG (34h) is set to 1.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of d4d_int2 in reg CTRL_REG5
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_int2_pin_detect_4d_get(const stmdev_ctx_t *ctx,
                                      uint8_t *val)
{
  lis2dh_ctrl_reg5_t ctrl_reg5;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_CTRL_REG5,
                        (uint8_t *)&ctrl_reg5, 1);
  *val = (uint8_t)ctrl_reg5.d4d_int2;

  return ret;
}

/**
  * @brief   Latch interrupt request on INT2_SRC (35h) register, with
  *          INT2_SRC (35h) register cleared by reading INT2_SRC(35h)
  *          itself.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of lir_int2 in reg CTRL_REG5
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_int2_pin_notification_mode_set(const stmdev_ctx_t *ctx,
                                              lis2dh_lir_int2_t val)
{
  lis2dh_ctrl_reg5_t ctrl_reg5;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_CTRL_REG5,
                        (uint8_t *)&ctrl_reg5, 1);

  if (ret == 0)
  {
    ctrl_reg5.lir_int2 = (uint8_t)val;
    ret = lis2dh_write_reg(ctx, LIS2DH_CTRL_REG5,
                           (uint8_t *)&ctrl_reg5, 1);
  }

  return ret;
}

/**
  * @brief   Latch interrupt request on INT2_SRC (35h) register, with
  *          INT2_SRC (35h) register cleared by reading INT2_SRC(35h)
  *          itself.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of lir_int2 in reg CTRL_REG5
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_int2_pin_notification_mode_get(const stmdev_ctx_t *ctx,
                                              lis2dh_lir_int2_t *val)
{
  lis2dh_ctrl_reg5_t ctrl_reg5;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_CTRL_REG5,
                        (uint8_t *)&ctrl_reg5, 1);

  switch (ctrl_reg5.lir_int2)
  {
    case LIS2DH_INT2_PULSED:
      *val = LIS2DH_INT2_PULSED;
      break;

    case LIS2DH_INT2_LATCHED:
      *val = LIS2DH_INT2_LATCHED;
      break;

    default:
      *val = LIS2DH_INT2_PULSED;
      break;
  }

  return ret;
}

/**
  * @brief  4D enable: 4D detection is enabled on INT1 pin when 6D bit
  *                    on INT1_CFG(30h) is set to 1.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of d4d_int1 in reg CTRL_REG5
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_int1_pin_detect_4d_set(const stmdev_ctx_t *ctx,
                                      uint8_t val)
{
  lis2dh_ctrl_reg5_t ctrl_reg5;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_CTRL_REG5,
                        (uint8_t *)&ctrl_reg5, 1);

  if (ret == 0)
  {
    ctrl_reg5.d4d_int1 = val;
    ret = lis2dh_write_reg(ctx, LIS2DH_CTRL_REG5,
                           (uint8_t *)&ctrl_reg5, 1);
  }

  return ret;
}

/**
  * @brief  4D enable: 4D detection is enabled on INT1 pin when 6D bit on
  *         INT1_CFG(30h) is set to 1.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of d4d_int1 in reg CTRL_REG5
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_int1_pin_detect_4d_get(const stmdev_ctx_t *ctx,
                                      uint8_t *val)
{
  lis2dh_ctrl_reg5_t ctrl_reg5;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_CTRL_REG5,
                        (uint8_t *)&ctrl_reg5, 1);
  *val = (uint8_t)ctrl_reg5.d4d_int1;

  return ret;
}

/**
  * @brief   Latch interrupt request on INT1_SRC (31h), with INT1_SRC(31h)
  *          register cleared by reading INT1_SRC (31h) itself.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of lir_int1 in reg CTRL_REG5
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_int1_pin_notification_mode_set(const stmdev_ctx_t *ctx,
                                              lis2dh_lir_int1_t val)
{
  lis2dh_ctrl_reg5_t ctrl_reg5;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_CTRL_REG5,
                        (uint8_t *)&ctrl_reg5, 1);

  if (ret == 0)
  {
    ctrl_reg5.lir_int1 = (uint8_t)val;
    ret = lis2dh_write_reg(ctx, LIS2DH_CTRL_REG5,
                           (uint8_t *)&ctrl_reg5, 1);
  }

  return ret;
}

/**
  * @brief   Latch interrupt request on INT1_SRC (31h), with INT1_SRC(31h)
  *          register cleared by reading INT1_SRC (31h) itself.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of lir_int1 in reg CTRL_REG5
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_int1_pin_notification_mode_get(const stmdev_ctx_t *ctx,
                                              lis2dh_lir_int1_t *val)
{
  lis2dh_ctrl_reg5_t ctrl_reg5;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_CTRL_REG5,
                        (uint8_t *)&ctrl_reg5, 1);

  switch (ctrl_reg5.lir_int1)
  {
    case LIS2DH_INT1_PULSED:
      *val = LIS2DH_INT1_PULSED;
      break;

    case LIS2DH_INT1_LATCHED:
      *val = LIS2DH_INT1_LATCHED;
      break;

    default:
      *val = LIS2DH_INT1_PULSED;
      break;
  }

  return ret;
}

/**
  * @brief  Int2 pin routing configuration register.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      registers CTRL_REG6
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_pin_int2_config_set(const stmdev_ctx_t *ctx,
                                   lis2dh_ctrl_reg6_t *val)
{
  int32_t ret;

  ret = lis2dh_write_reg(ctx, LIS2DH_CTRL_REG6, (uint8_t *) val, 1);

  return ret;
}

/**
  * @brief  Int2 pin routing configuration register.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      registers CTRL_REG6
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_pin_int2_config_get(const stmdev_ctx_t *ctx,
                                   lis2dh_ctrl_reg6_t *val)
{
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_CTRL_REG6, (uint8_t *) val, 1);

  return ret;
}
/**
  * @}
  *
  */

/**
  * @defgroup  LIS2DH_Fifo
  * @brief     This section group all the functions concerning the fifo usage
  * @{
  *
  */

/**
  * @brief  FIFO enable.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of fifo_en in reg CTRL_REG5
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_fifo_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lis2dh_ctrl_reg5_t ctrl_reg5;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_CTRL_REG5,
                        (uint8_t *)&ctrl_reg5, 1);

  if (ret == 0)
  {
    ctrl_reg5.fifo_en = val;
    ret = lis2dh_write_reg(ctx, LIS2DH_CTRL_REG5,
                           (uint8_t *)&ctrl_reg5, 1);
  }

  return ret;
}

/**
  * @brief  FIFO enable.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of fifo_en in reg CTRL_REG5
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_fifo_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lis2dh_ctrl_reg5_t ctrl_reg5;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_CTRL_REG5,
                        (uint8_t *)&ctrl_reg5, 1);
  *val = (uint8_t)ctrl_reg5.fifo_en;

  return ret;
}

/**
  * @brief  FIFO watermark level selection.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of fth in reg FIFO_CTRL_REG
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_fifo_watermark_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lis2dh_fifo_ctrl_reg_t fifo_ctrl_reg;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_FIFO_CTRL_REG,
                        (uint8_t *)&fifo_ctrl_reg, 1);

  if (ret == 0)
  {
    fifo_ctrl_reg.fth = val;
    ret = lis2dh_write_reg(ctx, LIS2DH_FIFO_CTRL_REG,
                           (uint8_t *)&fifo_ctrl_reg, 1);
  }

  return ret;
}

/**
  * @brief  FIFO watermark level selection.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of fth in reg FIFO_CTRL_REG
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_fifo_watermark_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lis2dh_fifo_ctrl_reg_t fifo_ctrl_reg;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_FIFO_CTRL_REG,
                        (uint8_t *)&fifo_ctrl_reg, 1);
  *val = (uint8_t)fifo_ctrl_reg.fth;

  return ret;
}

/**
  * @brief  Trigger FIFO selection.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of tr in reg FIFO_CTRL_REG
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_fifo_trigger_event_set(const stmdev_ctx_t *ctx,
                                      lis2dh_tr_t val)
{
  lis2dh_fifo_ctrl_reg_t fifo_ctrl_reg;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_FIFO_CTRL_REG,
                        (uint8_t *)&fifo_ctrl_reg, 1);

  if (ret == 0)
  {
    fifo_ctrl_reg.tr = (uint8_t)val;
    ret = lis2dh_write_reg(ctx, LIS2DH_FIFO_CTRL_REG,
                           (uint8_t *)&fifo_ctrl_reg, 1);
  }

  return ret;
}

/**
  * @brief  Trigger FIFO selection.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of tr in reg FIFO_CTRL_REG
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_fifo_trigger_event_get(const stmdev_ctx_t *ctx,
                                      lis2dh_tr_t *val)
{
  lis2dh_fifo_ctrl_reg_t fifo_ctrl_reg;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_FIFO_CTRL_REG,
                        (uint8_t *)&fifo_ctrl_reg, 1);

  switch (fifo_ctrl_reg.tr)
  {
    case LIS2DH_INT1_GEN:
      *val = LIS2DH_INT1_GEN;
      break;

    case LIS2DH_INT2_GEN:
      *val = LIS2DH_INT2_GEN;
      break;

    default:
      *val = LIS2DH_INT1_GEN;
      break;
  }

  return ret;
}

/**
  * @brief  FIFO mode selection.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of fm in reg FIFO_CTRL_REG
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_fifo_mode_set(const stmdev_ctx_t *ctx, lis2dh_fm_t val)
{
  lis2dh_fifo_ctrl_reg_t fifo_ctrl_reg;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_FIFO_CTRL_REG,
                        (uint8_t *)&fifo_ctrl_reg, 1);

  if (ret == 0)
  {
    fifo_ctrl_reg.fm = (uint8_t)val;
    ret = lis2dh_write_reg(ctx, LIS2DH_FIFO_CTRL_REG,
                           (uint8_t *)&fifo_ctrl_reg, 1);
  }

  return ret;
}

/**
  * @brief  FIFO mode selection.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of fm in reg FIFO_CTRL_REG
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_fifo_mode_get(const stmdev_ctx_t *ctx, lis2dh_fm_t *val)
{
  lis2dh_fifo_ctrl_reg_t fifo_ctrl_reg;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_FIFO_CTRL_REG,
                        (uint8_t *)&fifo_ctrl_reg, 1);

  switch (fifo_ctrl_reg.fm)
  {
    case LIS2DH_BYPASS_MODE:
      *val = LIS2DH_BYPASS_MODE;
      break;

    case LIS2DH_FIFO_MODE:
      *val = LIS2DH_FIFO_MODE;
      break;

    case LIS2DH_DYNAMIC_STREAM_MODE:
      *val = LIS2DH_DYNAMIC_STREAM_MODE;
      break;

    case LIS2DH_STREAM_TO_FIFO_MODE:
      *val = LIS2DH_STREAM_TO_FIFO_MODE;
      break;

    default:
      *val = LIS2DH_BYPASS_MODE;
      break;
  }

  return ret;
}

/**
  * @brief  FIFO status register.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      registers FIFO_SRC_REG
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_fifo_status_get(const stmdev_ctx_t *ctx,
                               lis2dh_fifo_src_reg_t *val)
{
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_FIFO_SRC_REG, (uint8_t *) val, 1);

  return ret;
}
/**
  * @brief  FIFO stored data level.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of fss in reg FIFO_SRC_REG
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_fifo_data_level_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lis2dh_fifo_src_reg_t fifo_src_reg;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_FIFO_SRC_REG,
                        (uint8_t *)&fifo_src_reg, 1);
  *val = (uint8_t)fifo_src_reg.fss;

  return ret;
}
/**
  * @brief  Empty FIFO status flag.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of empty in reg FIFO_SRC_REG
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_fifo_empty_flag_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lis2dh_fifo_src_reg_t fifo_src_reg;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_FIFO_SRC_REG,
                        (uint8_t *)&fifo_src_reg, 1);
  *val = (uint8_t)fifo_src_reg.empty;

  return ret;
}
/**
  * @brief  FIFO overrun status flag.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of ovrn_fifo in reg FIFO_SRC_REG
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_fifo_ovr_flag_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lis2dh_fifo_src_reg_t fifo_src_reg;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_FIFO_SRC_REG,
                        (uint8_t *)&fifo_src_reg, 1);
  *val = (uint8_t)fifo_src_reg.ovrn_fifo;

  return ret;
}
/**
  * @brief  FIFO watermark status.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of wtm in reg FIFO_SRC_REG
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_fifo_fth_flag_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lis2dh_fifo_src_reg_t fifo_src_reg;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_FIFO_SRC_REG,
                        (uint8_t *)&fifo_src_reg, 1);
  *val = (uint8_t)fifo_src_reg.wtm;

  return ret;
}
/**
  * @}
  *
  */

/**
  * @defgroup  LIS2DH_Tap_generator
  * @brief     This section group all the functions that manage the tap and
  *            double tap event generation
  * @{
  *
  */

/**
  * @brief  Tap/Double Tap generator configuration register.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      registers CLICK_CFG
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_tap_conf_set(const stmdev_ctx_t *ctx,
                            lis2dh_click_cfg_t *val)
{
  int32_t ret;

  ret = lis2dh_write_reg(ctx, LIS2DH_CLICK_CFG, (uint8_t *) val, 1);

  return ret;
}

/**
  * @brief  Tap/Double Tap generator configuration register.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      registers CLICK_CFG
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_tap_conf_get(const stmdev_ctx_t *ctx,
                            lis2dh_click_cfg_t *val)
{
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_CLICK_CFG, (uint8_t *) val, 1);

  return ret;
}
/**
  * @brief  Tap/Double Tap generator source register.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      registers CLICK_SRC
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_tap_source_get(const stmdev_ctx_t *ctx,
                              lis2dh_click_src_t *val)
{
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_CLICK_SRC, (uint8_t *) val, 1);

  return ret;
}
/**
  * @brief  User-defined threshold value for Tap/Double Tap event.[set]
  *         1 LSB = full scale/128
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of ths in reg CLICK_THS
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_tap_threshold_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lis2dh_click_ths_t click_ths;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_CLICK_THS,
                        (uint8_t *)&click_ths, 1);

  if (ret == 0)
  {
    click_ths.ths = val;
    ret = lis2dh_write_reg(ctx, LIS2DH_CLICK_THS,
                           (uint8_t *)&click_ths, 1);
  }

  return ret;
}

/**
  * @brief  User-defined threshold value for Tap/Double Tap event.[get]
  *         1 LSB = full scale/128
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of ths in reg CLICK_THS
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_tap_threshold_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lis2dh_click_ths_t click_ths;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_CLICK_THS,
                        (uint8_t *)&click_ths, 1);
  *val = (uint8_t)click_ths.ths;

  return ret;
}

/**
  * @brief  The maximum time (1 LSB = 1/ODR) interval that can elapse
  *         between the start of the click-detection procedure and when the
  *         acceleration falls back below the threshold.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of tli in reg TIME_LIMIT
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_shock_dur_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lis2dh_time_limit_t time_limit;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_TIME_LIMIT,
                        (uint8_t *)&time_limit, 1);

  if (ret == 0)
  {
    time_limit.tli = val;
    ret = lis2dh_write_reg(ctx, LIS2DH_TIME_LIMIT,
                           (uint8_t *)&time_limit, 1);
  }

  return ret;
}

/**
  * @brief  The maximum time (1 LSB = 1/ODR) interval that can elapse between
  *         the start of the click-detection procedure and when the
  *         acceleration falls back below the threshold.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of tli in reg TIME_LIMIT
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_shock_dur_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lis2dh_time_limit_t time_limit;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_TIME_LIMIT,
                        (uint8_t *)&time_limit, 1);
  *val = (uint8_t)time_limit.tli;

  return ret;
}

/**
  * @brief  The time (1 LSB = 1/ODR) interval that starts after the first
  *         click detection where the click-detection procedure is
  *         disabled, in cases where the device is configured for
  *         double-click detection.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of tla in reg TIME_LATENCY
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_quiet_dur_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lis2dh_time_latency_t time_latency;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_TIME_LATENCY,
                        (uint8_t *)&time_latency, 1);

  if (ret == 0)
  {
    time_latency.tla = val;
    ret = lis2dh_write_reg(ctx, LIS2DH_TIME_LATENCY,
                           (uint8_t *)&time_latency, 1);
  }

  return ret;
}

/**
  * @brief  The time (1 LSB = 1/ODR) interval that starts after the first
  *         click detection where the click-detection procedure is
  *         disabled, in cases where the device is configured for
  *         double-click detection.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of tla in reg TIME_LATENCY
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_quiet_dur_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lis2dh_time_latency_t time_latency;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_TIME_LATENCY,
                        (uint8_t *)&time_latency, 1);
  *val = (uint8_t)time_latency.tla;

  return ret;
}

/**
  * @brief  The maximum interval of time (1 LSB = 1/ODR) that can elapse
  *         after the end of the latency interval in which the click-detection
  *         procedure can start, in cases where the device is configured
  *         for double-click detection.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of tw in reg TIME_WINDOW
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_double_tap_timeout_set(const stmdev_ctx_t *ctx,
                                      uint8_t val)
{
  lis2dh_time_window_t time_window;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_TIME_WINDOW,
                        (uint8_t *)&time_window, 1);

  if (ret == 0)
  {
    time_window.tw = val;
    ret = lis2dh_write_reg(ctx, LIS2DH_TIME_WINDOW,
                           (uint8_t *)&time_window, 1);
  }

  return ret;
}

/**
  * @brief  The maximum interval of time (1 LSB = 1/ODR) that can elapse
  *         after the end of the latency interval in which the
  *         click-detection procedure can start, in cases where the device
  *         is configured for double-click detection.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of tw in reg TIME_WINDOW
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_double_tap_timeout_get(const stmdev_ctx_t *ctx,
                                      uint8_t *val)
{
  lis2dh_time_window_t time_window;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_TIME_WINDOW,
                        (uint8_t *)&time_window, 1);
  *val = (uint8_t)time_window.tw;

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup  LIS2DH_Activity_inactivity
  * @brief     This section group all the functions concerning activity
  *            inactivity functionality
  * @{
  *
  */

/**
  * @brief    Sleep-to-wake, return-to-sleep activation threshold in
  *           low-power mode.[set]
  *           1 LSb = 16mg@2g / 32mg@4g / 62mg@8g / 186mg@16g
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of acth in reg ACT_THS
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_act_threshold_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lis2dh_act_ths_t act_ths;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_ACT_THS, (uint8_t *)&act_ths, 1);

  if (ret == 0)
  {
    act_ths.acth = val;
    ret = lis2dh_write_reg(ctx, LIS2DH_ACT_THS, (uint8_t *)&act_ths, 1);
  }

  return ret;
}

/**
  * @brief  Sleep-to-wake, return-to-sleep activation threshold in low-power
  *         mode.[get]
  *         1 LSb = 16mg@2g / 32mg@4g / 62mg@8g / 186mg@16g
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of acth in reg ACT_THS
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_act_threshold_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lis2dh_act_ths_t act_ths;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_ACT_THS, (uint8_t *)&act_ths, 1);
  *val = (uint8_t)act_ths.acth;

  return ret;
}

/**
  * @brief  Sleep-to-wake, return-to-sleep.[set]
  *         duration = (8*1[LSb]+1)/ODR
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of actd in reg ACT_DUR
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_act_timeout_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lis2dh_act_dur_t act_dur;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_ACT_DUR, (uint8_t *)&act_dur, 1);

  if (ret == 0)
  {
    act_dur.actd = val;
    ret = lis2dh_write_reg(ctx, LIS2DH_ACT_DUR, (uint8_t *)&act_dur, 1);
  }

  return ret;
}

/**
  * @brief  Sleep-to-wake, return-to-sleep.[get]
  *         duration = (8*1[LSb]+1)/ODR
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of actd in reg ACT_DUR
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_act_timeout_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lis2dh_act_dur_t act_dur;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_ACT_DUR, (uint8_t *)&act_dur, 1);
  *val = (uint8_t)act_dur.actd;

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup  LIS2DH_Serial_interface
  * @brief     This section group all the functions concerning serial
  *            interface management
  * @{
  *
  */

/**
  * @brief  SPI Serial Interface Mode selection.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of sim in reg CTRL_REG4
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_spi_mode_set(const stmdev_ctx_t *ctx, lis2dh_sim_t val)
{
  lis2dh_ctrl_reg4_t ctrl_reg4;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_CTRL_REG4,
                        (uint8_t *)&ctrl_reg4, 1);

  if (ret == 0)
  {
    ctrl_reg4.sim = (uint8_t)val;
    ret = lis2dh_write_reg(ctx, LIS2DH_CTRL_REG4,
                           (uint8_t *)&ctrl_reg4, 1);
  }

  return ret;
}

/**
  * @brief  SPI Serial Interface Mode selection.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of sim in reg CTRL_REG4
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lis2dh_spi_mode_get(const stmdev_ctx_t *ctx, lis2dh_sim_t *val)
{
  lis2dh_ctrl_reg4_t ctrl_reg4;
  int32_t ret;

  ret = lis2dh_read_reg(ctx, LIS2DH_CTRL_REG4,
                        (uint8_t *)&ctrl_reg4, 1);

  switch (ctrl_reg4.sim)
  {
    case LIS2DH_SPI_4_WIRE:
      *val = LIS2DH_SPI_4_WIRE;
      break;

    case LIS2DH_SPI_3_WIRE:
      *val = LIS2DH_SPI_3_WIRE;
      break;

    default:
      *val = LIS2DH_SPI_4_WIRE;
      break;
  }

  return ret;
}



static int32_t platform_write(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len);

static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len);

static void platform_delay(uint32_t ms);



stmdev_ctx_t dev_ctx = {.write_reg = platform_write, .read_reg = platform_read, .mdelay=platform_delay};

uint8_t msgOutImu[64]; ///<USE ME AS A BUFFER FOR platform_write and platform_read
I2C_Data imuData; ///<Use me as a structure to communicate with the IMU on platform_write and platform_read

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
  msgOutImu[0] = reg;
	for(uint16_t i=0; i < len; i++){
		msgOutImu[i+1] = bufp[i];
	}
	imuData.address = 0x19;
	imuData.msgOut = &msgOutImu;
	imuData.lenOut = len + 1;
	imuData.lenIn = len;
	imuData.msgIn = bufp;
  return I2cWriteDataWait(&imuData, 100, SERCOM_3);
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
	msgOutImu[0] = reg;
	imuData.address = 0x19;
	imuData.msgIn = bufp;
	imuData.lenIn = len;
	imuData.lenOut = 1;
	imuData.msgOut = &msgOutImu;
	
	return I2cReadDataWait(&imuData, 100, 100, SERCOM_3);
}

/**
 * @brief Delays execution for a specified number of milliseconds.
 * 
 * This is a simple wrapper function around the `delay_ms` function to add abstraction
 * and possibly make future changes to the delay mechanism easier to manage.
 *
 * @param ms Number of milliseconds to delay.
 */
static void platform_delay(uint32_t ms){
  delay_ms(ms);
}

/**
 * @brief Retrieves a pointer to the IMU device context.
 * 
 * This function returns a pointer to the global IMU device context used for
 * managing IMU operations and configurations.
 *
 * @return Pointer to the IMU device context.
 */
stmdev_ctx_t * GetImuStruct(void)
{
return &dev_ctx;
}


/**
 * @brief Initializes the IMU sensor with default settings.
 * 
 * Configures the IMU sensor with a default set of parameters including data rate, 
 * scale, and operating mode. Also performs a system reboot at the start to ensure 
 * configurations are applied correctly.
 *
 * @return Error status (0 if no errors).
 */
int32_t InitImu(void)
{
uint8_t rst;
int32_t error = 0;
/*
   * Restore default configuration
   */
  platform_delay(BOOT_TIME);
  // System memory reboot is needed to keep updating values
  rst = 0x80;
  lis2dh_boot_set(&dev_ctx, &rst);
  /* Enable Block Data Update. */
  lis2dh_block_data_update_set(&dev_ctx, PROPERTY_ENABLE);
  /* Set Output Data Rate to 1Hz. */
  lis2dh_data_rate_set(&dev_ctx, LIS2DH_ODR_25Hz);
  /* Set full scale to 2g. */
  lis2dh_full_scale_set(&dev_ctx, LIS2DH_2g);
  /* Enable temperature sensor. */
  // lis2dh_temperature_meas_set(&dev_ctx, LIS2DH_TEMP_DISABLE);
  /* Set device in continuous mode with 12 bit resol. */
  lis2dh_operating_mode_set(&dev_ctx, LIS2DH_HR_12bit);
  
  return error;
}

/**
  * @}
  *
  */

/**
  * @}
  *
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
