#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[]){
   printf("Goodbye slow serial world and Hello OpenMP!\n");
   #pragma omp parallel
   if (omp_get_thread_num() == 0) {
      printf("  I have %d thread(s) and my thread id is %d\n",
             omp_get_num_threads(), omp_get_thread_num());
   }
}
