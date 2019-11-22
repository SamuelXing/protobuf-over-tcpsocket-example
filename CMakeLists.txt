cmake_minimum_required (VERSION 3.2)
project(protobuf-transmission)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++0x -Wall -I/usr/local/include")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(PROJECT_ROOT /home/novo1/misc)

include_directories(${PROJECT_ROOT})
find_package(Protobuf REQUIRED)

add_library(protobuf-transmission ${PROJECT_ROOT}/messages.pb.cc)
target_link_libraries(protobuf-transmission ${PROTOBUF_LIBRARIES} ${CPP_SHARED_LIBRARIES})

add_executable(client client.cc)
target_link_libraries (client protobuf-transmission ${CPP_SHARED_LIBRARIES})

add_executable(server server.cc)
target_link_libraries (server protobuf-transmission ${CPP_SHARED_LIBRARIES})
