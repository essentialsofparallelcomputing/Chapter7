#ifndef _TIMER_H
#define _TIMER_H
#include <time.h>

#ifdef __cpluscplus
extern "C" {
#endif

void cpu_timer_start(struct timespec *tstart_cpu);
double cpu_timer_stop(struct timespec tstart_cpu);

#ifdef __cpluscplus
}
#endif

#endif
