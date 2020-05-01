cmake_minimum_required (VERSION 3.2)
project(protobuf_over_tcp_socket)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(proto)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/proto)

add_executable(client ${PROJECT_ROOT}/client.cc)
target_link_libraries (client proto_msg ${CPP_SHARED_LIBRARIES})

add_executable(server ${PROJECT_ROOT}/server.cc)
target_link_libraries (server proto_msg ${CPP_SHARED_LIBRARIES})
