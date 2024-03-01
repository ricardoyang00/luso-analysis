cmake_minimum_required(VERSION 3.27)
project(proj_da_01)
# Set the C++ standard to 17
set(CMAKE_CXX_STANDARD 17)
# Ensure that the C++ standard is required
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add source files to the executable
add_executable(proj_da_01
        main.cpp
        include/Station.h
        include/Reservoir.h
        include/Graph.h
        include/City.h
        include/Pipe.h
        include/Code.h
        include/MutablePriorityQueue.h
)
