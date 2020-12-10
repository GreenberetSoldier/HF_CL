cmake_minimum_required(VERSION 3.17)

include_directories(ucunit ../)

add_executable(hf_cl_test hf_cl_test.c ucunit/System.h ucunit/uCUnit-v1.0.h ucunit/i386/System.c)

target_link_libraries(hf_cl_test HF_CL)

enable_testing()

add_test(all_test hf_cl_test)

