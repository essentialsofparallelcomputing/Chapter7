#include <stdlib.h>
#include <omp.h>

double do_kahan_sum(double* restrict var, long ncells)
{
   struct esum_type{
      double sum;
      double correction;
   };

   // Get the total number of threads and thread_id
   int nthreads = 1; 
   int thread_id   = 0;
#ifdef _OPENMP
   nthreads = omp_get_num_threads();
   thread_id = omp_get_thread_num();
#endif
   
   struct esum_type local;
   local.sum = 0.0;
   local.correction = 0.0;

   // Compute the range for which this thread is responsible.
   int tbegin = ncells * ( thread_id     ) / nthreads;
   int tend   = ncells * ( thread_id + 1 ) / nthreads;

   for (long i = tbegin; i < tend; i++) {
      double corrected_next_term = var[i] + local.correction;
      double new_sum             = local.sum + local.correction;
      local.correction   = corrected_next_term - (new_sum - local.sum);
      local.sum          = new_sum;
   }

   static struct esum_type *thread;
   static double sum;

#ifdef _OPENMP
#pragma omp master 
   thread = malloc(nthreads*sizeof(struct esum_type));
#pragma omp barrier

   thread[thread_id].sum = local.sum;
   thread[thread_id].correction = local.correction;

   // Now do sum across threads
   // Wait until all threads get here.
#pragma omp barrier

   // Use a single thread to compute the sum of all threads
   static struct esum_type global;
#pragma omp master 
   {
      global.sum = 0.0;
      global.correction = 0.0;
      for ( int i = 0 ; i < nthreads ; i ++ ) {
         double corrected_next_term = thread[i].sum + thread[i].correction +
                                      global.correction;
         double new_sum             = global.sum + global.correction;
         global.correction   = corrected_next_term - (new_sum - global.sum);
         global.sum          = new_sum;
      }

      sum = global.sum + global.correction;
      free(thread);
   } // end omp master
#pragma omp barrier
#else
   sum = local.sum + local.correction;
#endif

   return(sum);
}
