# Chapter7 OpenMP that performs
This is from Chapter 7 of Parallel and High Performance Computing, Robey and Zamora,
Manning Publications, available at http://manning.com

The book may be obtained at
   http://www.manning.com/?a_aid=ParallelComputingRobey

Copyright 2019-2020 Robert Robey, Yuliana Zamora, and Manning Publications
Emails: brobey@earthlink.net, yzamora215@gmail.com

See License.txt for licensing information.

OpenMP programs
   Requirements: a compiler that supports OpenMP. Most compilers have it built in

   HelloOpenMP (Book: listing 7.1-7.6)
      Build with either cmake or make
      This is a series of examples trying to correctly get our thread number
      Run the programs ./Hello_OpenMP and ./Hello_OpenMP_fix1 through 5

   VecAdd (Book: listing 7.7 and 7.8)
      Build with cmake
      A series of examples for OpenMP threading
      Run the programs ./VecAdd and ./VecAdd_opt1 through 3

   StreamTriad (Book: listing 7.9)
      Build with cmake
      A series of examples for OpenMP threading
      Run the programs ./StreamTriad and ./StreamTriad_opt1 through 2

   Stencil (Book: listing 7.10)
      Build with cmake
      A series of examples for OpenMP threading
      Run the programs ./stencil and ./stencil_opt1 through 2

   GlobalSums (Book: listing 7.11)
      Build with cmake
      Example for reduction operaions with OpenMP threading
      Run the program ./globalsums

   Private (Book: listing 7.12)
      Build with cmake
      Example of private clause
      Run the program ./private
      Note that x and z are not defined outside the loop

   FunctionLevel (Book: listing 7.13 and 7.14)
      Build with cmake
      Example of function level variable scoping with OpenMP
      Run ./FunctionLevel and ./FunctionLevelFort
      No output -- just example of variable scoping

   HighLevelOpenMP_stencil (Book: listing 7.15 through 7.16)
      Build with cmake
      Examples of combining parallel regions into a high level OpenMP approach
      Run ./stencil_opt2 through opt6

   StreamTriad (Book: listing 7.17)
      Examples stream_triad_opt3 and 4
      Build with cmake
      Run ./stream_triad_opt3 and ./stream_triad_opt4

   HybridOpenMP_stencil (Book: listing 7.18)
      Build with cmake
      Examples of hybrid threading and vectorization
      Run ./stencil_hybrid and ./stencil_threads

   SplitStencil (Book: listing 7.19 and listing 7.20)
      Build with cmake
      Examples of advanced OpenMP variable scoping
      Run ./SplitStencil and ./SplitStencil_opt1

   GlobalSums (Book: listing 7.21)
      See kahan_sum.c for an advanced reduction example
      Build with cmake
      Example for reduction operations with OpenMP threading
      Run the program ./globalsums

   PrefixScan (Book: listing 7.22)
      Build with cmake
      Example for an advanced reduction with OpenMP threading
      Run the program ./PrefixScan

   PairwiseSumByTask (Book: listing 7.23)
      Build with cmake
      Tasking example in OpenMP
      Run the program with ./PairwiseSumByTask
