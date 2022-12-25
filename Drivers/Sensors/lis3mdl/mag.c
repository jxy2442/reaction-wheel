#include "mag.h"
#include <stdio.h>

void print_hex(uint8_t* hexes, uint16_t n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%.2x", hexes[i]);
	}
	printf("\n");
}

/* Setup: FS, PM, ODR, OM
 *
 * ctx		pointer to control structure
 * handle	platform bus handle (can be used by mag_read and mag_write)
 */
void init_mag(stmdev_ctx_t* ctx, void* handle)
{
	int32_t ret;

	ctx->handle = handle;
	ctx->read_reg = (stmdev_read_ptr) mag_read;
	ctx->write_reg = (stmdev_write_ptr) mag_write;

	// initalize registers to default values
	uint8_t mag_e_controls[] = {0x01U, 0, 0, 0, 0};
	print_hex(mag_e_controls, sizeof(mag_e_controls));

	ret = lis3mdl_write_reg(ctx, LIS3MDL_CTRL_REG1,
			mag_e_controls, sizeof(mag_e_controls));
	if (ret)
	{
		printf("Unable to write default registers: %ld\n", ret);
	}

	// set desired output properties
	// make sure the conversions in get_mag are consistent with this full-scale
	ret = lis3mdl_full_scale_set(ctx, LIS3MDL_FS);
	if (ret)
	{
		printf("Unable to write full-scale: %ld\n", ret);
	}
	ret = lis3mdl_data_rate_set(ctx, LIS3MDL_UHP_155Hz);
	if (ret)
	{
		printf("Unable to write data rate: %ld\n", ret);
	}
	ret = lis3mdl_operating_mode_set(ctx, LIS3MDL_CONTINUOUS_MODE);
	if (ret)
	{
		printf("Unable to write operating mode: %ld\n", ret);
	}

	// read all of the registers, you can print them if you want
	lis3mdl_read_reg(ctx, LIS3MDL_CTRL_REG1,
			mag_e_controls, sizeof(mag_e_controls));
	print_hex(mag_e_controls, sizeof(mag_e_controls));
}

/* Platform implementation to read from the LIS3MDL
 *
 * handle	platform bus handle (may be unused)
 * reg		starting register
 * buf		data destination
 * len		amount of data
 *
 * returns	status (ok, busy, error, etc.)
 * MANDATORY: Return value of 0 means success
 * MANDATORY: Do not return -1
 */
int32_t mag_read(void* handle, uint8_t reg, uint8_t* buf, uint16_t len)
{
	/* PLATFORM READ IMPLEMENTATION */
	return (int32_t) HAL_I2C_Mem_Read((I2C_HandleTypeDef*) handle,
			LIS3MDL_I2C_ADD_L,
			reg | 0x80, 1, buf, len,
			LIS3MDL_TIMEOUT);
	/* PLATFORM READ IMPLEMENTATION END*/
}

/* Platform implementation to write to the LIS3MDL
 *
 * handle 	platform bus handle (may be unused)
 * reg		starting register
 * buf		data to be written
 * len 		amount of data to be written
 *
 * returns	status (ok, busy, error, etc.)
 * MANDATORY: Return value of 0 means success
 * MANDATORY: Do not return -1
 */
int32_t mag_write(void* handle, uint8_t reg, uint8_t* buf, uint16_t len)
{
	/* PLATFORM WRITE IMPLEMENTATION */
	return (int32_t) HAL_I2C_Mem_Write((I2C_HandleTypeDef*) handle,
			LIS3MDL_I2C_ADD_L,
			reg | 0x80, 1, buf, len,
			LIS3MDL_TIMEOUT);
	/* PLATFORM WRITE IMPLEMENTATION END*/
}

/* Use the control structure's read/write functions to get status, then read magnetic field
 * MANDATORY: Check the conversion function and factor to make sure the output units are
 * what you expect
 *
 * ctx		device control structure
 * output	pointer to where the result should be written
 *
 * returns	status: -1 no data, 0 ok, otherwise - interface status as returned by mag_read
 */
int32_t get_mag(stmdev_ctx_t* ctx, vector3_t* output)
{
	int32_t ret; // store interface return value
	int16_t buf[3]; // store raw magnetic data
	lis3mdl_status_reg_t status; // store status register contents

	ret = lis3mdl_status_get(ctx, &status);
	if (ret)
	{
		return ret; // failed to read status register
	}
	if (!status.zyxda)
	{
		return -1; // no data ready
	}
	ret = lis3mdl_magnetic_raw_get(ctx, buf);
	if (ret)
	{
		return ret; // failed to read raw data
	}

	output->x = ((float_t) buf[0]) / LIS3MDL_DIVISOR;
	output->y = ((float_t) buf[1]) / LIS3MDL_DIVISOR;
	output->z = ((float_t) buf[2]) / LIS3MDL_DIVISOR;

	return 0;
}

/* Get heading using principal arctangent
 * MANDATORY: Magnetometer must have z axis pointing up
 *
 * value	mag value to convert
 *
 * returns	angle between +x and magnetic north (0-360)
 */
float_t get_heading(vector3_t value)
{
	float_t angle = (float_t) atan2(value.y, value.x) * 180.0f / 3.141592654f;
	return (angle > 0) ? angle : 360 + angle;
}
