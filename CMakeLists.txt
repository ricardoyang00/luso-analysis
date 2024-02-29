cmake_minimum_required(VERSION 3.27)
project(proj_da_01 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(proj_da_01
        include/reservoir.h)
