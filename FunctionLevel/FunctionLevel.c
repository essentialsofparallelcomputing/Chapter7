#include <stdlib.h>
#include <omp.h>
int main(int argc, char*argv[]){
}
void function_level_OpenMP(int n, double *y)
{
   double *x;
   static double *x1;

   int thread_id;
#pragma omp parallel
   thread_id = omp_get_thread_num();

   if (thread_id == 0) x = (double *)malloc(100*sizeof(double));
   if (thread_id == 0) x1 = (double *)malloc(100*sizeof(double));

// lots of code
   if (thread_id ==0) free(x);
   if (thread_id ==0) free(x1);
}
