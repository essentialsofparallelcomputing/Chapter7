#!/bin/sh
export OMP_PLACES=cores
export OMP_CPU_BIND=true
./SplitStencil

for i in 1 2 4 8 16 22 32 44 64 88
do
   export OMP_NUM_THREADS=$i
   ./SplitStencil_opt1
done
