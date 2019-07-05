#!/bin/sh

export OMP_PLACES=cores;
export OMP_CPU_BIND=true;

export OMP_NUM_THREADS=2; ./stencil
