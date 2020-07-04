#include <stdio.h>
#include <omp.h>
#include "timer.h"

// large enough to force into main memory
#define ARRAY_SIZE 80000000
static double a[ARRAY_SIZE], b[ARRAY_SIZE], c[ARRAY_SIZE];

void vector_add(double *c, double *a, double *b, int n);

int main(int argc, char *argv[]){
   #pragma omp parallel
      if (omp_get_thread_num() == 0)
         printf("Running with %d thread(s)\n",omp_get_num_threads());

   struct timespec tstart;
   double time_sum = 0.0;
#pragma omp parallel for
   for (int i=0; i<ARRAY_SIZE; i++) {
      a[i] = 1.0;
      b[i] = 2.0;
   }

   cpu_timer_start(&tstart);
   vector_add(c, a, b, ARRAY_SIZE);
   time_sum += cpu_timer_stop(tstart);

   printf("Runtime is %lf msecs\n", time_sum);
}

void vector_add(double *c, double *a, double *b, int n)
{
#pragma omp parallel for
   for (int i=0; i < n; i++){
      c[i] = a[i] + b[i];
   }
}

