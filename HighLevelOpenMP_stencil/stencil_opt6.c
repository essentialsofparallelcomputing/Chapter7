#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#include "malloc2D.h"
#include "timer.h"

#define SWAP_PTR(xnew,xold,xtmp) (xtmp=xnew, xnew=xold, xold=xtmp)
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))

int main(int argc, char *argv[])
{
   #pragma omp parallel
      if (omp_get_thread_num() == 0)
         printf("Running with %d thread(s)\n",omp_get_num_threads());

   struct timespec tstart_init, tstart_flush, tstart_stencil, tstart_total;
   double init_time, flush_time, stencil_time, total_time;
   int imax=2002, jmax = 2002;

   double** xtmp;
   double** x = malloc2D(jmax, imax);
   double** xnew = malloc2D(jmax, imax);
   int *flush = (int *)malloc(jmax*imax*sizeof(int)*4);

   cpu_timer_start(&tstart_total);
   #pragma omp parallel
   {
      int thread_id = omp_get_thread_num();
      int nthreads = omp_get_num_threads();

      int jltb = 1 + (jmax-2) * ( thread_id     ) / nthreads;
      int jutb = 1 + (jmax-2) * ( thread_id + 1 ) / nthreads;

      int ifltb = (jmax*imax*4) * ( thread_id     ) / nthreads;
      int ifutb = (jmax*imax*4) * ( thread_id + 1 ) / nthreads;

      int jltb0 = jltb;
      if (thread_id == 0) jltb0--;
      int jutb0 = jutb;
      if (thread_id == nthreads-1) jutb0++;

      int kmin = MAX(jmax/2-5,jltb);
      int kmax = MIN(jmax/2+5,jutb);

      if (thread_id == 0) cpu_timer_start(&tstart_init);
      for (int j = jltb0; j < jutb0; j++){
         for (int i = 0; i < imax; i++){
            xnew[j][i] = 0.0;
            x[j][i] = 5.0;
         }
      }

      for (int j = kmin; j < kmax; j++){
         for (int i = imax/2 - 5; i < imax/2 -1; i++){
            x[j][i] = 400.0;
         }
      }
      #pragma omp barrier
      if (thread_id == 0) init_time += cpu_timer_stop(tstart_init);

      for (int iter = 0; iter < 10000; iter++){
         if (thread_id == 0) cpu_timer_start(&tstart_flush);
         for (int l = ifltb; l < ifutb; l++){
            flush[l] = 1.0;
         }
         if (thread_id == 0){
            flush_time += cpu_timer_stop(tstart_flush);
            cpu_timer_start(&tstart_stencil);
         }
         for (int j = jltb; j < jutb; j++){
            for (int i = 1; i < imax-1; i++){
               xnew[j][i] = ( x[j][i] + x[j][i-1] + x[j][i+1] + x[j-1][i] + x[j+1][i] )/5.0;
            }
         }
         #pragma omp barrier
         if (thread_id == 0){
            stencil_time += cpu_timer_stop(tstart_stencil);

            SWAP_PTR(xnew, x, xtmp);
            if (iter%1000 == 0) printf("Iter %d\n",iter);
         }
         #pragma omp barrier
      }
   } // end omp parallel
   total_time += cpu_timer_stop(tstart_total);

   printf("Timing is init %f flush %f stencil %f total %f\n",
          init_time,flush_time,stencil_time,total_time);

   free(x);
   free(xnew);
   free(flush);
}
