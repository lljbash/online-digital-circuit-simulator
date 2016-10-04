add_executable(psjjjj_server server.cpp)

find_package(gflags REQUIRED)
target_link_libraries(psjjjj_server gflags)

include_directories(${PROTOBUF_INCLUDE_DIRECTORY})
include_directories(${ENGINE_INCLUDE_DIRECTORY})

target_link_libraries(psjjjj_server psjjjj_engine psjjjj_protobuf pthread)
add_dependencies(psjjjj_server psjjjj_engine psjjjj_protobuf)

