#ifndef SCHED_H
#define SCHED_H

#include <stdint.h>
#include <Errors.h>
#include <systick.h>

#define MAX_TASKS		6
#define TICK_TIME_MS	1

typedef void (*RunnableCBF_t)(void);

typedef struct{
	char name[50];
	uint16_t periodicity;
	uint16_t priority;
	RunnableCBF_t CB;
}runnable_t;

void sched_init();
void sched_RegisterRunnable(runnable_t* r);
void sched_start();

#endif
