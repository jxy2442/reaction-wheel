/*
 * datatypes.h
 *
 *  Created on: Aug 24, 2022
 *      Author: yevge
 */

#ifndef INC_SENSORS_DATATYPES_H_
#define INC_SENSORS_DATATYPES_H_

#include <math.h> // for float_t
#include <stdint.h>

typedef struct {
	float_t x;
	float_t y;
	float_t z;
} vector3_t;

typedef struct {
	vector3_t* values;
	int32_t size;
	int32_t position;
} measurement_ringbuf_t;

#define RINGBUF(vals) {.values = vals, .size = sizeof(vals) / sizeof(vector3_t), .position = 0}

#endif /* INC_SENSORS_DATATYPES_H_ */
