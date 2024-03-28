/*
 * sched.c
 *
 *  Created on: Mar 14, 2024
 *      Author: Amina Ismail
 */
#include <sched.h>


typedef struct
{
	runnable_t* runnable;
	uint32_t RemainingTimeMS;

}InfoRunnable_t;

static InfoRunnable_t Tasks[MAX_TASKS];
static uint8_t pendingflag=0;
void sched();
void scheduler();

void sched_init()
{
	systick_SetTimerMs(TICK_TIME_MS);
	systick_setCallBack(scheduler);
}
void sched_RegisterRunnable(runnable_t* r)
{
	if (r && (Tasks[r->priority].runnable == 0))
	{
		Tasks[r->priority].runnable=r;
		Tasks[r->priority].RemainingTimeMS=r->periodicity;
	}
}

void sched_start()
{
	systick_Start(PERIODIC);
	while(1)
	{
		if(pendingflag)
		{
			pendingflag--;
			sched();
		}
	}
}
void scheduler()
{
	pendingflag++;
}
void sched()
{
	uint32_t idx=0;
	for (idx=0;idx<MAX_TASKS;idx++)
	{
		if(Tasks[idx].runnable!=0)
		{
			if(Tasks[idx].RemainingTimeMS==0)
			{
				Tasks[idx].runnable->CB();
				Tasks[idx].RemainingTimeMS=Tasks[idx].runnable->periodicity;
			}
			Tasks[idx].RemainingTimeMS -= TICK_TIME_MS;
		}

	}
}
