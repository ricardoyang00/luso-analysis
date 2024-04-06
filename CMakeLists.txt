cmake_minimum_required(VERSION 3.27)
project(feup_da_01)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
file(COPY data/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/data/)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(feup_da_01
        main.cpp
        include/Graph.h
        include/MutablePriorityQueue.h
        include/Station.h               src/Station.cpp
        include/Reservoir.h             src/Reservoir.cpp
        include/City.h                  src/City.cpp
        include/Code.h                  src/Code.cpp
        include/Utilities.h             src/Utilities.cpp
        include/ParseData.h             src/ParseData.cpp
        include/BasicServiceMetrics.h   src/BasicServiceMetrics.cpp
        include/Printer.h               src/Printer.cpp
        include/Menu.h                  src/Menu.cpp
)

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

    add_dependencies(feup_da_01 docs)
endif(DOXYGEN_FOUND)