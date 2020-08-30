#include <stdio.h>
#include <stdlib.h>

#include "malloc2D.h"
#include "timer.h"

#define SWAP_PTR(xnew,xold,xtmp) (xtmp=xnew, xnew=xold, xold=xtmp)
void SplitStencil(double **a, int imax, int jmax);

int main(int argc, char *argv[])
{
   printf("Serial run with no threads\n");
   struct timespec tstart_init, tstart_flush, tstart_stencil, tstart_total;
   double init_time, flush_time, stencil_time, total_time;
   int imax=2002, jmax = 2002;
   char string[60];

   double** a = malloc2D(jmax, imax);
   int *flush = (int *)malloc(jmax*imax*sizeof(int)*4);

   cpu_timer_start(&tstart_total);
   cpu_timer_start(&tstart_init);
   for (int j = 0; j < jmax; j++){
      for (int i = 0; i < imax; i++){
         a[j][i] = 5.0;
      }
   }

   for (int j = jmax/2 - 5; j < jmax/2 + 5; j++){
      for (int i = imax/2 - 5; i < imax/2 -1; i++){
         a[j][i] = 400.0;
      }
   }
   init_time += cpu_timer_stop(tstart_init);

   for (int iter = 0; iter < 10000; iter++){
      cpu_timer_start(&tstart_flush);
      for (int l = 1; l < jmax*imax*4; l++){
          flush[l] = 1.0;
      }
      flush_time += cpu_timer_stop(tstart_flush);
      sprintf(string,"flush %d\n",flush[5]);
      flush[1]=flush[2];
      cpu_timer_start(&tstart_stencil);
      SplitStencil(a, imax, jmax);
      stencil_time += cpu_timer_stop(tstart_stencil);
      sprintf(string,"a %lf\n",a[5][5]);

      if (iter%1000 == 0) printf("Iter %d\n",iter);
   }
   total_time += cpu_timer_stop(tstart_total);

   printf("Timing is init %f flush %f stencil %f total %f\n",
          init_time,flush_time,stencil_time,total_time);

   free(a);
   free(flush);
}

void SplitStencil(double **a, int imax, int jmax)
{
   double** xface = malloc2D(jmax, imax);
   double** yface = malloc2D(jmax, imax);
   for (int j = 1; j < jmax-1; j++){
      for (int i = 0; i < imax-1; i++){
         xface[j][i] = (a[j][i+1]+a[j][i])/2.0;
      }
   }
   for (int j = 0; j < jmax-1; j++){
      for (int i = 1; i < imax-1; i++){
         yface[j][i] = (a[j+1][i]+a[j][i])/2.0;
      }
   }
   for (int j = 1; j < jmax-1; j++){
      for (int i = 1; i < imax-1; i++){
         a[j][i] = (a[j][i]+xface[j][i]+xface[j][i-1]+yface[j][i]+yface[j-1][i])/5.0;
      }
   }
   free(xface);
   free(yface);
}

