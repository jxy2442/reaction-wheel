#ifndef __STATE_H__
#define __STATE_H__


#include "main.h"
#include "tim.h"
#include <math.h>
#include <stdint.h>
#include "../Dev/datatypes.h"

typedef struct
{
	measurement_ringbuf_t angular_rates;
	measurement_ringbuf_t accels;
	measurement_ringbuf_t mag_fields;
	time_ringbuf_t angular_rate_times;
	time_ringbuf_t accel_times;
	time_ringbuf_t mag_field_times;
} raw_measurements_t;

typedef enum
{
	IDLE_F,
	ARM,
	BOOST,
	COAST,
	ENDCOAST,
	DESCENT,
	LAND
} flight_state_t;

typedef struct
{
	vector3_t angular_rate;
	vector3_t accel;
	vector3_t mag_field;
	uint32_t angular_rate_time;
	uint32_t accel_time;
	uint32_t mag_field_time;
	flight_state_t flight_state;
} estimates_t;

typedef struct
{
	/* JOHN CODE HERE */
	float_t motor_output;
	int32_t motor_output_time;

	/* JOHN CODE HERE */
} control_state_t;

extern raw_measurements_t raw_measurements;
extern flight_state_t flight_state;
extern estimates_t estimate;
extern control_state_t control_state;

#define PLATFORM_GET_TIME __HAL_TIM_GET_COUNTER(&htim5)
#endif
