#include<state.h>

#define GYRO_SIZE 400
#define ACCEL_SIZE 400
#define MAG_SIZE 155

vector3_t _gyro_measurements[GYRO_SIZE];
vector3_t _accel_measurements[ACCEL_SIZE];
vector3_t _mag_field_measurements[MAG_SIZE];
uint32_t _gyro_times[GYRO_SIZE];
uint32_t _accel_times[ACCEL_SIZE];
uint32_t _mag_times[MAG_SIZE];

raw_measurements_t raw_measurements = {
	.angular_rates = INIT_RINGBUF(_gyro_measurements),
	.accels = INIT_RINGBUF(_accel_measurements),
	.mag_fields = INIT_RINGBUF(_mag_field_measurements),
	.angular_rate_times = INIT_RINGBUF(_gyro_times),
	.accel_times = INIT_RINGBUF(_accel_times),
	.mag_field_times = INIT_RINGBUF(_mag_times),
};
flight_state_t flight_state;
estimates_t estimate;
control_state_t control_state;
