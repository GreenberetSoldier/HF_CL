cmake_minimum_required(VERSION 3.17)
project(HF_CL C)

set(CMAKE_C_STANDARD 99)

add_library(HF_CL gate_control.c gate_control.h hardware.h)

enable_testing()

add_subdirectory(all_test)