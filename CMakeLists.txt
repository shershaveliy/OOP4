cmake_minimum_required(VERSION 3.16)
project(GeometricFigures)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fconcepts")
endif()

add_executable(main main.cpp)

enable_testing()
add_subdirectory(test)