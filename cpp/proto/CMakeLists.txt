include(FindProtobuf)
find_package(Protobuf REQUIRED)

file(GLOB PROTOS "*.proto")
 
foreach(FIL ${PROTOS})
    get_filename_component(FIL_WE ${FIL} NAME_WE)
    
    list(APPEND PROTO_SRCS "${CMAKE_SOURCE_DIR}/build/proto/${FIL_WE}.pb.cc")
    
    execute_process(
        COMMAND protoc --proto_path=${CMAKE_CURRENT_SOURCE_DIR} --cpp_out=${CMAKE_SOURCE_DIR}/build/proto ${FIL}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
endforeach()
 
add_library(psjjjj_protobuf STATIC ${PROTO_SRCS})
target_link_libraries(psjjjj_protobuf protobuf)
set(PROTOBUF_INCLUDE_DIRECTORY ${CMAKE_SOURCE_DIR}/build/proto PARENT_SCOPE)

