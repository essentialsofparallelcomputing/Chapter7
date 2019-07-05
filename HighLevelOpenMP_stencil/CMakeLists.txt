cmake_minimum_required (VERSION 3.0)
project (stencil)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set (CMAKE_C_STANDARD 99)

if (NOT VECTOR_TYPE)
   set (VECTOR_TYPE full_vectorize)
endif (NOT VECTOR_TYPE)
if (VECTOR_TYPE STREQUAL "none")
   set (VECTOR_TYPE none)
endif (VECTOR_TYPE STREQUAL "none")
if (VECTOR_TYPE STREQUAL "default")
   set (VECTOR_TYPE default)
endif (VECTOR_TYPE STREQUAL "default")

# Set vectorization flags for a few compilers
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O3")
if ("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang") # using Clang
   set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fstrict-aliasing -fnovectorize\
       -march=native -mtune=native")
elseif ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU") # using GCC
   set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=native -mtune=native")
   set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fstrict-aliasing -fno-tree-vectorize -fopenmp")
   set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopt-info-loop-optimized")
   set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopt-info-vec-optimized")
elseif ("${CMAKE_C_COMPILER_ID}" STREQUAL "Intel") # using Intel C
   set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -no-vec -ansi-alias -xHost -qopenmp")
elseif (CMAKE_C_COMPILER_ID MATCHES "MSVC")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -openmp:experimental")
elseif (CMAKE_C_COMPILER_ID MATCHES "XL")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -qalias=ansi -qsimd=noauto -qopenmp")
elseif (CMAKE_C_COMPILER_ID MATCHES "Cray")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -h restrict=a -h vector0")
endif()

# Adds build target of stencil with source code files
add_executable(stencil_opt2 stencil_opt2.c timer.c timer.h malloc2D.c malloc2D.h)

add_executable(stencil_opt3 stencil_opt3.c timer.c timer.h malloc2D.c malloc2D.h)

add_executable(stencil_opt4 stencil_opt4.c timer.c timer.h malloc2D.c malloc2D.h)

add_executable(stencil_opt5 stencil_opt5.c timer.c timer.h malloc2D.c malloc2D.h)

# Cleanup
add_custom_target(distclean COMMAND rm -rf CMakeCache.txt CMakeFiles
                  Makefile cmake_install.cmake stencil.dSYM ipo_out.optrpt)
