cmake_minimum_required(VERSION 3.0)
project(RISCV)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

include_directories(./include)

aux_source_directory(./src abclzr_src)

aux_source_directory(./test abclzr_test)

add_executable(code ${abclzr_src} ${abclzr_test})