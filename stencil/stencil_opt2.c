#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "malloc2D.h"
#include "timer.h"

#ifdef LIKWID_PERFMON
#include "likwid.h"
#else
#define LIKWID_MARKER_INIT
#define LIKWID_MARKER_THREADINIT
#define LIKWID_MARKER_REGISTER(regionTag)
#define LIKWID_MARKER_START(regionTag)
#define LIKWID_MARKER_STOP(regionTag)
#define LIKWID_MARKER_CLOSE
#define LIKWID_MARKER_GET(regionTag, nevents, events, time, count)
#endif

#define SWAP_PTR(xnew,xold,xtmp) (xtmp=xnew, xnew=xold, xold=xtmp)

int main(int argc, char *argv[])
{
   LIKWID_MARKER_INIT;
   // Fails with exit and no message?
   //LIKWID_MARKER_REGISTER("STENCIL");
   struct timeval tstart_cpu, tstop_cpu;
   double cpu_time;
   int imax=2002, jmax = 2002;

   double** xtmp;
   double** restrict x = malloc2D(jmax, imax);
   double** restrict xnew = malloc2D(jmax, imax);
   int *flush = (int *)malloc(jmax*imax*sizeof(int)*10);

   for (int j = 0; j < jmax; j++){
      for (int i = 0; i < imax; i++){
         xnew[j][i] = 0.0;
         x[j][i] = 5.0;
      }
   }

   for (int j = jmax/2 - 5; j < jmax/2 + 5; j++){
      for (int i = imax/2 - 5; i < imax/2 -1; i++){
         x[j][i] = 400.0;
      }
   }


   for (int iter = 0; iter < 10000; iter++){
      for (int l = 1; l < jmax*imax*10; l++){
          flush[l] = 1.0;
      }
      cpu_timer_start(&tstart_cpu);
      LIKWID_MARKER_START("STENCIL");
      for (int j = 1; j < jmax-1; j++){
         for (int i = 1; i < imax-1; i++){
            xnew[j][i] = ( x[j][i] + x[j][i-1] + x[j][i+1] + x[j-1][i] + x[j+1][i] )/5.0;
         }
      }
      LIKWID_MARKER_STOP("STENCIL");
      cpu_time += cpu_timer_stop(tstart_cpu);

      SWAP_PTR(xnew, x, xtmp);
      if (iter%100 == 0) printf("Iter %d\n",iter);
   }

   printf("Timing is %f\n",cpu_time);

   LIKWID_MARKER_CLOSE;
}
