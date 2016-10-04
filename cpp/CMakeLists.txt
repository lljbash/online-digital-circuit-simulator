project(psjjjj)
cmake_minimum_required(VERSION 2.8)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_COMPILER g++-5)
list(APPEND CMAKE_CXX_FLAGS "-std=c++14 -pthread -Wall -Wextra -Wno-unused-param")

message("+-------------------------------------")
message("| BUILD_TYPE: " ${CMAKE_BUILD_TYPE})
message("+-------------------------------------")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

add_subdirectory(proto)
add_subdirectory(engine)
add_subdirectory(application)

