cmake_minimum_required(VERSION 3.27)
project(proj_da_01)

set(CMAKE_C_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(.)

add_executable(proj_da_01
        include/Station.h
        include/Reservoir.h
        include/Graph.h
        include/City.h
        include/Pipe.h)
