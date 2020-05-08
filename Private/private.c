#include <stdio.h>
int main(int argc, char *argv[]){
   int n=20000;
   double x;
   #pragma omp parallel for private(x)
   for (int i=0; i < n; i++){
      x = 1.0;
      double y = x*2.0;
   }
   double z = x;
   printf("Outside parallel loop x is %lf z is %lf\n",x,z);
}
