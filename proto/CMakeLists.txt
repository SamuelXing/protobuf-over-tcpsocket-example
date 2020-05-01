find_package(Protobuf REQUIRED)
message(status "-- FOUND Protobuf: ${PROTOBUF_INCLUDE_DIR}")
include_directories(${PROTOBUF_INCLUDE_DIR})
PROTOBUF_GENERATE_CPP(PROTO_SRC PROTO_HEADER messages.proto)
add_library(proto_msg ${PROTO_HEADER} ${PROTO_SRC})
target_link_libraries(proto_msg PUBLIC 
${PROTOBUF_LIBRARIES}
)