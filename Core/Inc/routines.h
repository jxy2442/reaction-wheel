/*
 * routines.h
 *
 *  Created on: Nov 20, 2022
 *      Author: yevge
 */

#ifndef __ROUTINES_H__
#define __ROUTINES_H__

#include <stdio.h>
#include "main.h"

int32_t read_gyro(raw_measurements_t* rm, stmdev_ctx_t* ctx);
int32_t read_accel(raw_measurements_t* rm, stmdev_ctx_t* ctx);
int32_t read_mag(raw_measurements_t* rm, stmdev_ctx_t* ctx);

int32_t update_flight_phase(estimates_t* est, raw_measurements_t* rm);

int32_t calc_estimates(estimates_t* est, raw_measurements_t* rm);
// int32_t calculate_motor_output(control_state_t* cs, estimates_t* est);

// int32_t monitor_times(raw_measurements_t* rm);

int32_t print_mag_rt(stmdev_ctx_t* ctx);
#endif /* __ROUTINES_H__ */
