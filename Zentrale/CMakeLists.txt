cmake_minimum_required(VERSION 3.16)
project(Zentrale)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package (Threads REQUIRED)


# RPC stuff
include(FetchContent)
FetchContent_Declare(
        gRPC
        GIT_REPOSITORY https://github.com/grpc/grpc
        GIT_TAG        v1.38.0
)

set(FETCHCONTENT_QUIET OFF)
FetchContent_MakeAvailable(gRPC)

# Since FetchContent uses add_subdirectory under the hood, we can use
# the grpc targets directly from this build.
set(_PROTOBUF_LIBPROTOBUF libprotobuf)
set(_REFLECTION grpc++_reflection)
set(_PROTOBUF_PROTOC $<TARGET_FILE:protoc>)
set(_GRPC_GRPCPP grpc++)
if(CMAKE_CROSSCOMPILING)
    find_program(_GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)
else()
    set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:grpc_cpp_plugin>)
endif()

# Proto file
get_filename_component(hw_proto "src/proto/rpcServer.proto" ABSOLUTE)
get_filename_component(hw_proto_path "${hw_proto}" PATH)

# Generated sources
set(hw_proto_srcs "${CMAKE_CURRENT_SOURCE_DIR}/generated/rpcServer.pb.cc")
set(hw_proto_hdrs "${CMAKE_CURRENT_SOURCE_DIR}/generated/rpcServer.pb.h")
set(hw_grpc_srcs "${CMAKE_CURRENT_SOURCE_DIR}/generated/rpcServer.grpc.pb.cc")
set(hw_grpc_hdrs "${CMAKE_CURRENT_SOURCE_DIR}/generated/rpcServer.grpc.pb.h")
add_custom_command(
        OUTPUT "${hw_proto_srcs}" "${hw_proto_hdrs}" "${hw_grpc_srcs}" "${hw_grpc_hdrs}"
        COMMAND ${_PROTOBUF_PROTOC}
        ARGS --grpc_out "${CMAKE_CURRENT_SOURCE_DIR}/generated"
        --cpp_out "${CMAKE_CURRENT_SOURCE_DIR}/generated"
        -I "${hw_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${hw_proto}"
        DEPENDS "${hw_proto}")

# Include generated *.pb.h files
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/generated")

# hw_grpc_proto
add_library(hw_grpc_proto
        ${hw_grpc_srcs}
        ${hw_grpc_hdrs}
        ${hw_proto_srcs}
        ${hw_proto_hdrs})
target_link_libraries(hw_grpc_proto
        ${_REFLECTION}
        ${_GRPC_GRPCPP}
        ${_PROTOBUF_LIBPROTOBUF})

# main target
add_executable(Zentrale src/cpp/main.cpp src/cpp/Zentrale.cpp src/header/Zentrale.h src/cpp/WebServer/Webserver.cpp src/header/WebServer/Webserver.h src/cpp/Komponenten/Komponente.cpp src/header/Komponenten/Komponente.h src/cpp/Komponenten/Erzeuger.cpp src/header/Komponenten/Erzeuger.h src/cpp/Komponenten/Verbraucher.cpp src/header/Komponenten/Verbraucher.h src/cpp/UDPServer/UDPServer.cpp src/header/UDPServer/UDPServer.h src/header/UDPServer/UDPCallback.h src/cpp/WebServer/HTTPIntepreter.cpp src/header/WebServer/HTTPIntepreter.h src/cpp/Komponenten/KomponentenController.cpp src/header/Komponenten/KomponentenController.h src/cpp/WebServer/HttpContextHandlerController.cpp src/header/WebServer/HttpContextHandlerController.h src/header/WebServer/HttpContextHandler.h  src/cpp/WebServer/HTMLGenerator.cpp src/header/WebServer/HTMLGenerator.h src/cpp/UDPSender/UDPSender.cpp src/header/UDPSender/UDPSender.h src/cpp/UDPSender/KomponentenUdpSender.cpp src/header/UDPSender/KomponentenUdpSender.h src/cpp/Rpc/RpcServer.cpp src/header/Rpc/RpcServer.h)

target_link_libraries(Zentrale ${CMAKE_THREAD_LIBS_INIT})

target_link_libraries(Zentrale
        hw_grpc_proto
        ${_REFLECTION}
        ${_GRPC_GRPCPP}
        ${_PROTOBUF_LIBPROTOBUF})