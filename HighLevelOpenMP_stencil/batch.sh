#!/bin/sh

export OMP_PLACES=cores;
export OMP_CPU_BIND=true;

export OMP_NUM_THREADS=88; ./stencil_opt2
echo ""
echo ""
export OMP_NUM_THREADS=88; ./stencil_opt3
echo ""
echo ""
export OMP_NUM_THREADS=88; ./stencil_opt4
echo ""
echo ""
export OMP_NUM_THREADS=88; ./stencil_opt5
