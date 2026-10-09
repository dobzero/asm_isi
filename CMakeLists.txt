cmake_minimum_required(VERSION 4.0)
project(asm_isi LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_library(asm_isi STATIC arm_v8a_all.h arm_v8a_math.h arm_v8a_functions.h types.h arm_v8a_all.cpp)
