#include <omp.h>

double PairwiseSumBySubtask(double* restrict var, long nstart, long nend);

double PairwiseSumByTask(double* restrict var, long ncells)
{
   double sum;
   #pragma omp parallel
   {
      #pragma omp master
      {
         sum = PairwiseSumBySubtask(var, 0, ncells);
      }
   }
   return(sum);
}

double PairwiseSumBySubtask(double* restrict var, long nstart, long nend)
{
   long nsize = nend - nstart;
   long nmid = nsize/2;
   double x,y;
   if (nsize == 1){
      return(var[nstart]);
   }

   #pragma omp task shared(x) mergeable final(nsize > 10)
   x = PairwiseSumBySubtask(var, nstart, nstart + nmid);
   #pragma omp task shared(y) mergeable final(nsize > 10)
   y = PairwiseSumBySubtask(var, nend - nmid, nend);
   #pragma omp taskwait

   return(x+y);
}
