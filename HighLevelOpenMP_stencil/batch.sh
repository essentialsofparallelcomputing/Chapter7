#!/bin/sh

export OMP_PLACES=cores;
export OMP_CPU_BIND=true;

echo "Running stencil_opt2"
export OMP_NUM_THREADS=88; ./stencil_opt2
echo ""
echo ""
echo "Running stencil_opt3"
export OMP_NUM_THREADS=88; ./stencil_opt3
echo ""
echo ""
echo "Running stencil_opt4"
export OMP_NUM_THREADS=88; ./stencil_opt4
echo ""
echo ""
echo "Running stencil_opt5"
export OMP_NUM_THREADS=88; ./stencil_opt5
echo ""
echo ""
echo "Running stencil_opt6"
export OMP_NUM_THREADS=88; ./stencil_opt6
