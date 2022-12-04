/*
 * badsched.c
 * Runs the set tasks every specified period
 * Not preemptive
 * Bad
 *  Created on: Aug 24, 2022
 *      Author: yevge
 */

#include "badsched.h"

void run_tasks(bad_task_t* taskv, uint16_t taskc)
{
	uint32_t time;
	for (uint32_t i = 0; i < taskc; i++)
	{
		time = SCHED_TIMER_GET(taskv[i].timer);

		if (time - taskv[i].last > taskv[i].period)
		{
			taskv[i].last = time;
			taskv[i].task(taskv + i);
		}
	}
}
