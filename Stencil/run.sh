#!/bin/sh
export OMP_PLACES=cores
export OMP_CPU_BIND=true
./stencil
./stencil_opt1
./stencil_opt2
