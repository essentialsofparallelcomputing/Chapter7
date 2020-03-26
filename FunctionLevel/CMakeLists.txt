cmake_minimum_required (VERSION 3.0)
project (private)
enable_language(Fortran)

set (CMAKE_C_STANDARD 99)

find_package(OpenMP)

# Adds build target of FunctionLevel with source code files
add_executable(FunctionLevel FunctionLevel.c)
set_target_properties(FunctionLevel PROPERTIES COMPILE_FLAGS ${OpenMP_C_FLAGS})
set_target_properties(FunctionLevel PROPERTIES LINK_FLAGS "${OpenMP_C_FLAGS}")

# Adds build target of FunctionLevel with source code files
add_executable(FunctionLevelFort FunctionLevelFort.F90)
set_target_properties(FunctionLevelFort PROPERTIES COMPILE_FLAGS ${OpenMP_Fortran_FLAGS})
set_target_properties(FunctionLevelFort PROPERTIES LINK_FLAGS "${OpenMP_Fortran_FLAGS}")

# Cleanup
add_custom_target(distclean COMMAND rm -rf CMakeCache.txt CMakeFiles
                  Makefile cmake_install.cmake FunctionLevel.dSYM FunctionLevelFort.dSYM ipo_out.optrpt)
