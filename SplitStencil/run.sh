#!/bin/sh
export OMP_PLACES=cores
export OMP_CPU_BIND=true
./SplitStencil
./SplitStencil_opt1
