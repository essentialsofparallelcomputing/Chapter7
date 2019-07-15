#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <omp.h>

double do_sum_novec(double *var, long ncells);
double do_sum(double *var, long ncells);
double do_kahan_sum(double *var, long ncells);
double do_serial_sum_fog_v(double *var, long ncells);
double do_serial_sum_fog_v8(double *var, long ncells);

void cpu_timer_start(struct timespec *tstart_cpu);
double cpu_timer_stop(struct timespec tstart_cpu);

#define ORDERS_OF_MAGNITUDE 1.0e9;

typedef unsigned int uint;

int main(int argc, char *argv[])
{
#pragma omp parallel
   if (omp_get_thread_num() == 0) printf("\n  Running with %d thread(s)\n\n",omp_get_num_threads());

   //for (int pow_of_two = 8; pow_of_two < 31; pow_of_two++){
   for (int pow_of_two = 30; pow_of_two < 31; pow_of_two++){
      long ncells = (long)pow((double)2,(double)pow_of_two);
      long ncellsdiv2 = ncells/2;

      printf("SETTINGS INFO -- ncells %ld log %d\n",ncells,(int)log2((double)ncells));

      double high_value = 1.0e-1;
      double low_value  = 1.0e-1/ORDERS_OF_MAGNITUDE;
      double accurate_sum = (double)ncellsdiv2 * high_value +
                            (double)ncellsdiv2 * low_value;

      double *energy = (double *)malloc(ncells*sizeof(double));

      // Initialize with high values first
      printf("Initializing mesh with Leblanc problem, high values first\n");
      for (long i = 0; i < ncells; i++){
         energy[i] = (i < ncellsdiv2) ? high_value : low_value;
      }

      double test_sum;
      struct timespec cpu_timer;
      double cpu_time;

//******************************************************

      cpu_timer_start(&cpu_timer);

      test_sum = do_sum_novec(energy, ncells);

      cpu_time = cpu_timer_stop(cpu_timer);
   
      printf("  accurate sum %-17.16lg sum %-17.16lg diff %10.4lg relative diff %10.4lg runtime %lf",
             accurate_sum,test_sum,(test_sum-accurate_sum),((test_sum-accurate_sum)/accurate_sum), cpu_time);
      printf("   Serial sum\n");

//******************************************************

      cpu_timer_start(&cpu_timer);

      test_sum = do_kahan_sum(energy, ncells);

      cpu_time = cpu_timer_stop(cpu_timer);
   
      printf("  accurate sum %-17.16lg sum %-17.16lg diff %10.4lg relative diff %10.4lg runtime %lf",
             accurate_sum,test_sum,(test_sum-accurate_sum),((test_sum-accurate_sum)/accurate_sum), cpu_time);
      printf("   Kahan sum serial with double double accumulator\n");

//******************************************************

      cpu_timer_start(&cpu_timer);

      #pragma omp parallel
      test_sum = do_kahan_sum(energy, ncells);

      cpu_time = cpu_timer_stop(cpu_timer);
   
      printf("  accurate sum %-17.16lg sum %-17.16lg diff %10.4lg relative diff %10.4lg runtime %lf",
             accurate_sum,test_sum,(test_sum-accurate_sum),((test_sum-accurate_sum)/accurate_sum), cpu_time);
      printf("   Kahan sum threaded with double double accumulator\n");

//******************************************************
      printf(" 4 wide vectors serial sum\n");
//******************************************************

      cpu_timer_start(&cpu_timer);

      test_sum = do_sum(energy, ncells);

      cpu_time = cpu_timer_stop(cpu_timer);
   
      printf("  accurate sum %-17.16lg sum %-17.16lg diff %10.4lg relative diff %10.4lg runtime %lf",
             accurate_sum,test_sum,(test_sum-accurate_sum),((test_sum-accurate_sum)/accurate_sum), cpu_time);
      printf("   Serial sum (OpenMP SIMD pragma)\n");

//******************************************************
      free(energy);

      printf("\n");
   }
}

void cpu_timer_start(struct timespec *tstart_cpu){
   clock_gettime(CLOCK_MONOTONIC, tstart_cpu);
}

double cpu_timer_stop(struct timespec tstart_cpu){
   struct timespec tstop_cpu, tresult;
   clock_gettime(CLOCK_MONOTONIC, &tstop_cpu);
   tresult.tv_sec = tstop_cpu.tv_sec - tstart_cpu.tv_sec;
   tresult.tv_nsec = tstop_cpu.tv_nsec - tstart_cpu.tv_nsec;
   double result = (double)tresult.tv_sec + (double)tresult.tv_nsec*1.0e-9;

   return(result);
}
