/*
 * routines.c
 *
 *  Created on: Nov 20, 2022
 *      Author: yevge
 */

#include "routines.h"

void put_measurement_ringbuf(measurement_ringbuf_t* vals, vector3_t val)
{
	vals->values[vals->position] = val;
	vals->position = (vals->position + 1) % vals->size;
}

void put_time_ringbuf(time_ringbuf_t* vals, uint32_t val)
{

	vals->values[vals->position] = val;
	vals->position = (vals->position + 1) % vals->size;
}

int32_t read_gyro(raw_measurements_t* rm, stmdev_ctx_t* ctx)
{
	vector3_t value;
	int32_t ret = get_angular_rate(ctx, &value);
	if (ret)
	{
		return ret;
	}

	put_measurement_ringbuf(&(rm->angular_rates), value);
	put_time_ringbuf(&(rm->angular_rate_times), PLATFORM_GET_TIME);
	return 0;
}

int32_t read_accel(raw_measurements_t* rm, stmdev_ctx_t* ctx)
{
	vector3_t value;
	int32_t ret = get_accel(ctx, &value);
	if (ret)
	{
		return ret;
	}

	put_measurement_ringbuf(&(rm->accels), value);
	put_time_ringbuf(&(rm->accel_times), PLATFORM_GET_TIME);
	return 0;
}

int32_t read_mag(raw_measurements_t* rm, stmdev_ctx_t* ctx)
{
	vector3_t value;
	int32_t ret = get_mag(ctx, &value);
	if (ret)
	{
		return ret;
	}

	put_measurement_ringbuf(&(rm->mag_fields), value);
	put_time_ringbuf(&(rm->mag_field_times), PLATFORM_GET_TIME);

	return 0;
}

int32_t print_mag_rt(stmdev_ctx_t* ctx)
{
	uint32_t cur_time = PLATFORM_GET_TIME;
	vector3_t value;
	int32_t ret = get_mag(ctx, &value);
	if (ret)
	{
		printf("# No mag data: %ld\n", ret);
		return ret;
	}
	printf("%lu,%3.3f,%3.2f,%3.2f\tEOL\n", cur_time,
			value.x, value.y, value.z);

	return 0;
}

int32_t calc_estimates(estimates_t* est, raw_measurements_t* rm)
{
	uint32_t cur_time = PLATFORM_GET_TIME;

	vector3_t sum;
	int i;
	for (i = 0; i < rm->mag_fields.size; i++)
	{
		int32_t posn = (rm->mag_field_times.position - i) % rm->mag_field_times.size;

		if (rm->mag_field_times.values[posn] < est->mag_field_time)
		{
			break;
		}

		sum.x += rm->mag_fields.values[posn].x;
		sum.y += rm->mag_fields.values[posn].y;
		sum.z += rm->mag_fields.values[posn].z;
	}

	if (i > 0)
	{
		sum.x /= i;
		sum.y /= i;
		sum.z /= i;
		est->mag_field = sum;
		est->mag_field_time = cur_time;
	}

	return 0;
}


int32_t log_estimates(estimates_t* est)
{
	printf("M\t%3.2f\t%3.2f\t%3.2f\t(%4.2f ms)\n",
			est->mag_field.x, est->mag_field.y, est->mag_field.z,
			(float_t) (est->mag_field_time) / 1e3);
	return 0;
}
