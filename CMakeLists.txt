cmake_minimum_required(VERSION 3.27)
project(feup_da_01)
# Set the C++ standard to 17
set(CMAKE_CXX_STANDARD 17)
# Ensure that the C++ standard is required
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(COPY large-dataSet/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/large-dataSet/)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add source files to the executable
add_executable(feup_da_01
        main.cpp
        include/Graph.h
        include/MutablePriorityQueue.h
        include/Station.h               src/Station.cpp
        include/Reservoir.h             src/Reservoir.cpp
        include/City.h                  src/City.cpp
        include/Pipe.h                  src/Pipe.cpp
        include/Code.h                  src/Code.cpp
        include/Utilities.h             src/Utilities.cpp
        include/ParseData.h             src/ParseData.cpp
        include/BasicServiceMetrics.h   src/BasicServiceMetrics.cpp
        include/Printer.h               src/Printer.cpp
        src/Menu.cpp
        include/Menu.h
)

# Add a target to generate Doxygen documentation
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(DOXYGEN_INPUT ${PROJECT_SOURCE_DIR}/include)
    set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs)
    set(DOXYGEN_GENERATE_HTML YES)
    set(DOXYGEN_GENERATE_MAN NO)
    set(DOXYGEN_EXTRACT_PRIVATE YES)

    add_custom_target(
            docs
            COMMAND ${DOXYGEN_EXECUTABLE} ${PROJECT_SOURCE_DIR}/docs/Doxyfile
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen" VERBATIM
    )

    # Make the 'docs' target a dependency of the 'ALL' target
    add_dependencies(feup_da_01 docs)
endif(DOXYGEN_FOUND)