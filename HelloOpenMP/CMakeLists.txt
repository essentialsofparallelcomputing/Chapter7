cmake_minimum_required (VERSION 3.0)
project (HelloOpenMP)

set (CMAKE_C_STANDARD 99)

# Set vectorization flags for a few compilers
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O3")
if ("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang") # using Clang
   set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fstrict-aliasing -fopenmp -Rpass-analysis=loop-vectorize")
elseif ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU") # using GCC
   set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fstrict-aliasing -fopenmp -fopt-info-loop")
elseif ("${CMAKE_C_COMPILER_ID}" STREQUAL "Intel") # using Intel C
   set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ansi-alias -qopenmp -qopt-report-phase=loop")
elseif (CMAKE_C_COMPILER_ID MATCHES "MSVC")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
elseif (CMAKE_C_COMPILER_ID MATCHES "XL")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
elseif (CMAKE_C_COMPILER_ID MATCHES "Cray")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
endif()

# Adds build target of stream_triad with source code files
add_executable(HelloOpenMP HelloOpenMP.c)
add_executable(HelloOpenMP_fix1 HelloOpenMP_fix1.c)
add_executable(HelloOpenMP_fix2 HelloOpenMP_fix2.c)
add_executable(HelloOpenMP_fix3 HelloOpenMP_fix3.c)
add_executable(HelloOpenMP_fix4 HelloOpenMP_fix4.c)
add_executable(HelloOpenMP_fix5 HelloOpenMP_fix5.c)

# Cleanup
add_custom_target(distclean COMMAND rm -rf CMakeCache.txt CMakeFiles
                  Makefile cmake_install.cmake stream_triad.dSYM ipo_out.optrpt)
