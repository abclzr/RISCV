cmake_minimum_required(VERSION 3.0)
project(RISCV)

set(CMAKE_CXX_STANDARD 14)

include_directories(./include)

aux_source_directory(./src abclzr_src)

add_executable(code main.cpp ${abclzr_src})