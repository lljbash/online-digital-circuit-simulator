file(GLOB_RECURSE SRCS "*.cc")

include_directories(${CMAKE_SOURCE_DIR}/engine/public)
include_directories(${CMAKE_SOURCE_DIR}/engine)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${PROTOBUF_INCLUDE_DIRECTORY})
include_directories(${GTEST_INCLUDE_DIR})

add_executable(psjjjj_engine_test ${SRCS})
target_link_libraries(psjjjj_engine_test psjjjj_engine gtest gtest_main)
add_dependencies(psjjjj_engine_test psjjjj_engine gtest gtest_main)

