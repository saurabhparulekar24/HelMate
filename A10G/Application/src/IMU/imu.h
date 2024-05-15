
#ifndef IMU_H_
#define IMU_H_

// Uncomment the appropriate line to select the IMU device
#define USE_LIS2DH
// #define USE_LSM6DSO

#ifdef USE_LIS2DH
    #include "lis2dh\lis2dh_reg.h"

    // Define aliases for function names
    #define get_device_id lis2dh_device_id_get
    #define xl_flag_data_ready_get lis2dh_xl_data_ready_get
    #define acceleration_raw_get lis2dh_acceleration_raw_get
    #define from_fs2_to_mg lis2dh_from_fs2_hr_to_mg
    #define device_ID LIS2DH_ID

#elif defined(USE_LSM6DSO)
    #include "lsm6dso\lsm6dso_reg.h"

    // Define aliases for function names
    #define get_device_id lsm6dso_device_id_get
    #define xl_flag_data_ready_get lsm6dso_xl_flag_data_ready_get
    #define acceleration_raw_get lsm6dso_acceleration_raw_get
    #define from_fs2_to_mg lsm6dso_from_fs2_to_mg
    #define device_ID LSM6DSO_ID

#endif

#endif // IMU_H_
