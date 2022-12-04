/*
 * ../Libraries/sched/badsched.h
 *
 *  Created on: Aug 24, 2022
 *      Author: yevge
 */
#ifndef LIB_SCHED_BADSCHED_H_
#define LIB_SCHED_BADSCHED_H_

#include "stm32f4xx_hal.h"

#define SCHED_TIMER_GET __HAL_TIM_GET_COUNTER

typedef TIM_HandleTypeDef platform_timer_handle_t;

typedef struct
{
	int32_t (*task)(void *); // the scheduler calls this function with the task itself
	void* data;
	platform_timer_handle_t* timer;
	uint32_t period;
	uint32_t last;
} bad_task_t;

#define RUN_TASKS(routines) run_tasks(routines, sizeof(routines) / sizeof(bad_task_t))

void run_tasks(bad_task_t* taskv, uint16_t taskc);


#endif /* LIB_SCHED_BADSCHED_H_ */
