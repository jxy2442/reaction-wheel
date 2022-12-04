/*
 * datatypes.h
 *
 *  Created on: Aug 24, 2022
 *      Author: yevge
 */

#ifndef __DATATYPES_H__
#define __DATATYPES_H__

#include <math.h> // for float_t
#include <stdint.h>

typedef struct {
	float_t x;
	float_t y;
	float_t z;
} vector3_t;
/*
typedef struct {
	vector3_t* values;
	int32_t size;
	int32_t position;
} measurement_ringbuf_t;

typedef struct {
	int32_t* values;
	int32_t size;
	int32_t position;
} time_ringbuf_t;
*/

#define TD_RINGBUF(type, name) typedef struct {type* values; int32_t size; int32_t position;} name;
#define INIT_RINGBUF(vals) {.values = vals, .size = sizeof(vals) / sizeof(*vals), .position = 0}

TD_RINGBUF(vector3_t, measurement_ringbuf_t);
TD_RINGBUF(uint32_t, time_ringbuf_t);
#endif /* __DATATYPES_H__ */
