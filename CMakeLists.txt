cmake_minimum_required(VERSION 3.27)
project(proj_da_01)
# Set the C++ standard to 17
set(CMAKE_CXX_STANDARD 17)
# Ensure that the C++ standard is required
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(COPY small-dataSet/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/small-dataset/)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add source files to the executable
add_executable(proj_da_01
        main.cpp
        include/Graph.h
        include/MutablePriorityQueue.h
        include/Station.h       src/Station.cpp
        include/Reservoir.h     src/Reservoir.cpp
        include/City.h          src/City.cpp
        include/Pipe.h          src/Pipe.cpp
        include/Code.h          src/Code.cpp
        include/Utilities.h     src/Utilities.cpp
        include/ParseData.h     src/ParseData.cpp
)
