cmake_minimum_required(VERSION 4.0)
project(asm_isi LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
enable_language(CXX)

add_library(asm_isi STATIC arm_v8_a.h types.h types.cpp)
