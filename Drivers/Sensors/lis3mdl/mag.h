/*
 * mag_e.h
 * Implements ST's API for LIS3MDL magnetometer
 *  Created on: Aug 22, 2022
 *      Author: yevge
 */

// Implementation note: The breakout connects via a Stemma QT connector with the pinout
// RED -> GRAY: 3V3
// BLACK -> BLACK: GND
// BLUE -> VIOLET: SDA - PB9 for I2C1
// YELLOW -> WHITE: SCL - PB6 for I2C1

#ifndef INC_SENSORS_MAG_E_H_
#define INC_SENSORS_MAG_E_H_

#include<math.h>

#include "stm32f4xx_hal.h"
#include "datatypes.h"
#include "lis3mdl_reg.h"

#define LIS3MDL_TIMEOUT 10
#define LIS3MDL_FS_g 4

#if LIS3MDL_FS_g == 4
#define LIS3MDL_FS LIS3MDL_4_GAUSS
#define LIS3MDL_DIVISOR 6842.0f
#elif LIS3MDL_FS_g == 8
#define LIS3MDL_FS LIS3MDL_8_GAUSS
#define LIS3MDL_DIVISOR 3421.0f
#elif LIS3MDL_FS_g == 12
#define LIS3MDL_FS LIS3MDL_12_GAUSS
#define LIS3MDL_DIVISOR 2281.0f
#elif LIS3MDL_FS_g == 16
#define LIS3MDL_FS LIS3MDL_16_GAUSS
#define LIS3MDL_DIVISOR 1711.0f
#else
#error Invalid magnetometer full-scale
#endif

// Initalize control structure and configure device
void init_mag(stmdev_ctx_t* mag_ctx_ptr, void* handle);

// Platform implementation to read <len> bytes to <buf> from the device at <reg>
int32_t mag_read(void* handle, uint8_t reg, uint8_t* buf, uint16_t len);

// Platform implementation to write <len> bytes from <buf> to the device at <reg>
int32_t mag_write(void* handle, uint8_t reg, uint8_t* buf, uint16_t len);

// Check status and get output if there is new data
int32_t get_mag(stmdev_ctx_t* ctx, vector3_t* output);

// x,y to heading
float_t get_heading(vector3_t value);

#endif /* INC_SENSORS_MAG_E_H_ */
