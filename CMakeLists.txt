# cmake_minimum_required(VERSION <specify CMake version here>)
project(RISCV)

set(CMAKE_CXX_STANDARD 14)

include_directories(./include)

add_executable(RISCV main.cpp src/Register.cpp include/Register.h include/configure.h)