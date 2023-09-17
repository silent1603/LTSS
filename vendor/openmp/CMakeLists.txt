cmake_minimum_required(VERSION 3.14)
add_library(OpenMP STATIC )
target_sources(OpenMP PRIVATE omp-tools.h omp.h ompd-types.h stubs.c)