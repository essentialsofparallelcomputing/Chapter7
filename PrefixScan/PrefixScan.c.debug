#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include "timer.h"

#define MIN(a,b) ((a) < (b) ? (a) : (b))

void PrefixScan (int *input , int *output , int length);

int main(int argc, char *argv[]){
   #pragma omp parallel
      if (omp_get_thread_num() == 0)
         printf("Running with %d thread(s)\n",omp_get_num_threads());

   struct timespec tstart;
   double time_serial, time_threaded;
   // large enough to force into main memory
#define ARRAY_SIZE 8000000
   int *input_serial, *input_threaded, *output;
   input_serial = (int *)malloc(ARRAY_SIZE*sizeof(int));
   input_threaded = (int *)malloc(ARRAY_SIZE*sizeof(int));
   output = (int *)malloc(ARRAY_SIZE*sizeof(int));
   for (int i=0; i<ARRAY_SIZE; i++) {
      input_serial[i] = 1+i%2;
   }
#pragma omp parallel for
   for (int i=0; i<ARRAY_SIZE; i++) {
      input_threaded[i] = 1+i%2;
   }

   cpu_timer_start(&tstart);
   PrefixScan(input_serial, output, ARRAY_SIZE);
   time_serial += cpu_timer_stop(tstart);
   cpu_timer_start(&tstart);
#pragma omp parallel
   PrefixScan(input_threaded, output, ARRAY_SIZE);

// for (int i=0; i<ARRAY_SIZE; i++){
//    printf("DEBUG -- i %d input value %d scan value %d\n",i,input_threaded[i],output[i]);
//    if (i>0 && output[i]-output[i-1] != input_threaded[i-1])
//       printf("       DEBUG -- i %d input value %d scan value %d\n",i,input_threaded[i],output[i]);
// }
   time_threaded = cpu_timer_stop(tstart);

   printf("Runtime is for serial %lf threaded %lf speedup %lf msecs\n",
      time_serial, time_threaded, time_serial/time_threaded);
   free(input_serial);
   free(input_threaded);
   free(output);
}

void PrefixScan (int *input, int *output, int length) 
{
   // Get the total number of threads and thread_id
   int nthreads = 1;
   int thread_id   = 0;
#ifdef _OPENMP
   nthreads = omp_get_num_threads();
   thread_id = omp_get_thread_num();
#endif

   // Compute the range for which this thread is responsible.
   int itsize = length/nthreads;

   int tbegin = length * ( thread_id     ) / nthreads;
   int tend   = length * ( thread_id + 1 ) / nthreads;
// printf("%d:DEBUG -- tbegin %d tend %d\n",thread_id,tbegin,tend);

   // Only perform this operation if there is a postive number of entries.
   if ( tbegin < tend ) {

       // Do an exclusive scan for each thread
       output[tbegin] = 0;
       for ( int i = tbegin + 1 ; i < tend ; i++ ) {
          output[i] = output[i-1] + input[i-1];
       }
   }
   if (nthreads == 1 ) return;

   // Do adjustment to prefix scan for the tbegining value for each thread
#ifdef _OPENMP
   // Wait until all threads get here. 
#pragma omp barrier
    
   // Use a single thread to compute the tbegining offset for each thread
#pragma omp single
   for ( int i = 1 ; i < nthreads ; i ++ ) {
      int ibegin = length * ( i - 1 ) / nthreads;
      int iend   = length * ( i     ) / nthreads;
//    printf("%d:DEBUG -- ibegin %d iend %d\n",thread_id,ibegin,iend);

      if ( ibegin < iend ) 
         output[iend] = output[ibegin] + input[iend-1];

      if ( ibegin < iend - 1 )
         output[iend] += output[iend-1];
   } // #end pragma omp single loop
   // Barrier is implicit from omp single

   // Start all threads again
   // Apply the offset to the range for this thread.
#pragma omp simd
   for ( int i = tbegin + 1 ; i < tend ; i++ ) {
      output[i] += output[tbegin];
    }
#endif
}

