double do_sum_novec(double* restrict var, long ncells)
{
   double sum = 0.0;
   #pragma omp parallel for reduction(+:sum)
   for (long i = 0; i < ncells; i++){
      sum += var[i];
   }

   return(sum);
}
