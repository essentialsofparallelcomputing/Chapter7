#include <stdio.h>
#include <time.h>
#include <omp.h>
#include "timer.h"

#define NTIMES 16
// large enough to force into main memory
#define STREAM_ARRAY_SIZE 80000000
static double a[STREAM_ARRAY_SIZE], b[STREAM_ARRAY_SIZE], c[STREAM_ARRAY_SIZE];

int main(int argc, char *argv[]){
   #pragma omp parallel
      if (omp_get_thread_num() == 0)
         printf("Running with %d thread(s)\n",omp_get_num_threads());

   struct timespec tstart;
   // initializing data and arrays
   double scalar = 3.0, time_sum = 0.0;
   #pragma omp parallel
   {
      #pragma omp for simd
      for (int i=0; i<STREAM_ARRAY_SIZE; i++) {
         a[i] = 1.0;
         b[i] = 2.0;
      }

      for (int k=0; k<NTIMES; k++){
         #pragma omp master
         cpu_timer_start(&tstart);
         // stream triad loop
         #pragma omp for
         for (int i=0; i<STREAM_ARRAY_SIZE; i++){
            c[i] = a[i] + scalar*b[i];
         }
         #pragma omp master
         time_sum += cpu_timer_stop(tstart);
         // to keep the compiler from optimizing out the loop
         #pragma omp master
         c[1]=c[2];
      }

      #pragma omp master
      printf("Average runtime is %lf msecs\n", time_sum/NTIMES);
   } // end omp parallel
}

