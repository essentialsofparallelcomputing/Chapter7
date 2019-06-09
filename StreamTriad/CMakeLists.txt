cmake_minimum_required (VERSION 3.0)
project (stream_triad)

set (CMAKE_C_STANDARD 99)

# Set vectorization flags for a few compilers
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O3")
if ("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang") # using Clang
   set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fstrict-aliasing -fno-tree-vectorize -fopenmp -Rpass-analysis=loop-vectorize")
elseif ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU") # using GCC
   set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fstrict-aliasing -fopenmp -fopt-info-loop-optimized")
elseif ("${CMAKE_C_COMPILER_ID}" STREQUAL "Intel") # using Intel C
   set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ansi-alias -qopenmp -qopt-report-phase=openmp,loop,vec")
elseif (CMAKE_C_COMPILER_ID MATCHES "PGI")
   set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mp ")
elseif (CMAKE_C_COMPILER_ID MATCHES "MSVC")
   set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -openmp")
elseif (CMAKE_C_COMPILER_ID MATCHES "XL")
   set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -qsmp=omp")
elseif (CMAKE_C_COMPILER_ID MATCHES "Cray")
   set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
endif()

# Adds build target of stream_triad with source code files
add_executable(stream_triad stream_triad timer.c timer.h)
add_executable(stream_triad_opt1 stream_triad_opt1.c timer.c timer.h)
add_executable(stream_triad_opt2 stream_triad_opt2.c timer.c timer.h)
add_executable(stream_triad_opt3 stream_triad_opt3.c timer.c timer.h)

# Cleanup
add_custom_target(distclean COMMAND rm -rf CMakeCache.txt CMakeFiles
                  Makefile cmake_install.cmake stream_triad.dSYM ipo_out.optrpt)
