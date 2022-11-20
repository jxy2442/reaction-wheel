#ifndef __STATE_H__
#define __STATE_H__


#include "../Devices/datatypes.h"
#include <math.h>
#include <stdint.h>

typedef struct
{
	vector3_t angular_rate;
	vector3_t accel;
	vector3_t mag_field;
	int32_t angular_rate_time;
	int32_t accel_time;
	int32_t mag_field_time;
} raw_measurements_t;

typedef enum
{
	IDLE,
	ARM,
	WAIT, // might be the same as ARM
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
	flight_state_t flight_state;
} estimates_t;

typedef struct
{
	/* JOHN CODE HERE */
	float_t dummy;

	/* JOHN CODE HERE */
}  control_state_t;

extern raw_measurements_t raw_measurements;
extern flight_state_t flight_state;
extern estimates_t estimate;
extern control_state_t control_state;


#endif
