file(GLOB_RECURSE SRCS "*.cc")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/public)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(psjjjj_engine STATIC ${SRCS})
target_link_libraries(psjjjj_engine pthread psjjjj_protobuf)
add_dependencies(psjjjj_engine psjjjj_protobuf)

set(ENGINE_INCLUDE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/public PARENT_SCOPE)

