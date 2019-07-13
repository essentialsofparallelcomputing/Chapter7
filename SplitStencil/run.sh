#!/bin/sh
export OMP_PLACES=cores
export OMP_CPU_BIND=true
./SplitStencil
export OMP_NUM_THREADS=8
./SplitStencil_opt1
export OMP_NUM_THREADS=16
./SplitStencil_opt1
unset OMP_NUM_THREADS
./SplitStencil_opt1
