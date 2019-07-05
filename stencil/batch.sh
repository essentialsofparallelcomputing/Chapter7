#!/bin/sh

export OMP_PLACES=cores;
export OMP_CPU_BIND=true;

export OMP_NUM_THREADS=1; ./stencil
echo ""
echo ""
export OMP_NUM_THREADS=1; ./stencil_opt1
export OMP_NUM_THREADS=2; ./stencil_opt1
export OMP_NUM_THREADS=4; ./stencil_opt1
export OMP_NUM_THREADS=8; ./stencil_opt1
export OMP_NUM_THREADS=16; ./stencil_opt1
export OMP_NUM_THREADS=22; ./stencil_opt1
export OMP_NUM_THREADS=32; ./stencil_opt1
export OMP_NUM_THREADS=44; ./stencil_opt1
export OMP_NUM_THREADS=64; ./stencil_opt1
export OMP_NUM_THREADS=88; ./stencil_opt1
echo ""
echo ""
export OMP_NUM_THREADS=1; ./stencil_opt2
export OMP_NUM_THREADS=2; ./stencil_opt2
export OMP_NUM_THREADS=4; ./stencil_opt2
export OMP_NUM_THREADS=8; ./stencil_opt2
export OMP_NUM_THREADS=16; ./stencil_opt2
export OMP_NUM_THREADS=22; ./stencil_opt2
export OMP_NUM_THREADS=32; ./stencil_opt2
export OMP_NUM_THREADS=44; ./stencil_opt2
export OMP_NUM_THREADS=64; ./stencil_opt2
export OMP_NUM_THREADS=88; ./stencil_opt2
