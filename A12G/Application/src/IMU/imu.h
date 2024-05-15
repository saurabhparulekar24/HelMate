
/**
 * @file IMU.h
 * @brief Header file for configuring and using different IMU (Inertial Measurement Unit) devices.
 *
 * This file allows selection between multiple IMU devices by setting specific macros.
 * It configures the necessary includes and aliases based on the selected IMU device.
 * @author Saurabh Sandeep Parulekar
 */

#ifndef IMU_H_
#define IMU_H_

/**
 * @brief Uncomment the appropriate line to select the IMU device.
 * 
 * Define `USE_LIS2DH` to use the LIS2DH sensor.
 * Define `USE_LSM6DSO` to use the LSM6DSO sensor.
 */
#define USE_LIS2DH
// #define USE_LSM6DSO

#ifdef USE_LIS2DH
    #include "lis2dh\lis2dh_reg.h"                               ///< Include register definition for LIS2DH.

    // Define aliases for function names
    #define get_device_id lis2dh_device_id_get                  ///< Alias for getting device ID.
    #define xl_flag_data_ready_get lis2dh_xl_data_ready_get     ///< Alias for checking if accelerometer data is ready.
    #define acceleration_raw_get lis2dh_acceleration_raw_get    ///< Alias for getting raw acceleration data.
    #define from_fs2_to_mg lis2dh_from_fs2_hr_to_mg             ///< Alias for converting acceleration from 2g full scale to mg.
    #define device_ID LIS2DH_ID                                 ///< Define the device ID for LIS2DH.

#elif defined(USE_LSM6DSO)
    #include "lsm6dso\lsm6dso_reg.h"                            ///< Include register definition for LSM6DSO.

    // Define aliases for function names
    #define get_device_id lsm6dso_device_id_get                 ///< Alias for getting device ID.
    #define xl_flag_data_ready_get lsm6dso_xl_flag_data_ready_get ///< Alias for checking if accelerometer data is ready.
    #define acceleration_raw_get lsm6dso_acceleration_raw_get   ///< Alias for getting raw acceleration data.
    #define from_fs2_to_mg lsm6dso_from_fs2_to_mg               ///< Alias for converting acceleration from 2g full scale to mg.
    #define device_ID LSM6DSO_ID                                ///< Define the device ID for LSM6DSO.

#endif

#endif // IMU_H_
