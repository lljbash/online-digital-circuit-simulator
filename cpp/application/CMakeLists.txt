add_executable(psjjjj_server server.cpp)

include_directories(${PROTOBUF_INCLUDE_DIRECTORY})
include_directories(${ENGINE_INCLUDE_DIRECTORY})
include_directories(${GFLAGS_INCLUDE_DIR})

target_link_libraries(psjjjj_server psjjjj_engine psjjjj_protobuf gflags pthread)
add_dependencies(psjjjj_server psjjjj_engine psjjjj_protobuf gflags)

