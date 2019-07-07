#!/bin/sh
export OMP_PLACES=cores
export OMP_CPU_BIND=true
./vecadd
./vecadd_opt1
./vecadd_opt2
./vecadd_opt3
