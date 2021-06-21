cmake_minimum_required(VERSION 3.8)
project(Zentrale)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package (Threads REQUIRED)

# main target
add_executable(Zentrale src/cpp/main.cpp src/cpp/Zentrale.cpp src/header/Zentrale.h src/cpp/WebServer/Webserver.cpp src/header/WebServer/Webserver.h src/cpp/Komponenten/Komponente.cpp src/header/Komponenten/Komponente.h src/cpp/Komponenten/Erzeuger.cpp src/header/Komponenten/Erzeuger.h src/cpp/Komponenten/Verbraucher.cpp src/header/Komponenten/Verbraucher.h src/cpp/UDPServer/UDPServer.cpp src/header/UDPServer/UDPServer.h src/header/UDPServer/UDPCallback.h src/cpp/WebServer/HTTPIntepreter.cpp src/header/WebServer/HTTPIntepreter.h src/cpp/Komponenten/KomponentenController.cpp src/header/Komponenten/KomponentenController.h src/cpp/WebServer/HttpContextHandlerController.cpp src/header/WebServer/HttpContextHandlerController.h src/header/WebServer/HttpContextHandler.h  src/cpp/WebServer/HTMLGenerator.cpp src/header/WebServer/HTMLGenerator.h src/cpp/UDPSender/UDPSender.cpp src/header/UDPSender/UDPSender.h src/cpp/UDPSender/KomponentenUdpSender.cpp src/header/UDPSender/KomponentenUdpSender.h src/cpp/Rpc/RpcServer.cpp src/header/Rpc/RpcServer.h src/cpp/Rpc/ErzeugerRpcClient.cpp src/header/Rpc/ErzeugerRpcClient.h)

target_link_libraries(Zentrale ${CMAKE_THREAD_LIBS_INIT})

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
file(GLOB protoFiles "src/proto/*.proto")
foreach(filename ${protoFiles})

    get_filename_component(hw_proto "${filename}" ABSOLUTE)
    get_filename_component(hw_proto_path "${hw_proto}" PATH)
    get_filename_component(hw_proto_filename "${filename}" NAME_WE)

    # Generated sources
    set(hw_proto_srcs "${CMAKE_CURRENT_SOURCE_DIR}/generated/${hw_proto_filename}.pb.cc")
    set(hw_proto_hdrs "${CMAKE_CURRENT_SOURCE_DIR}/generated/${hw_proto_filename}.pb.h")
    set(hw_grpc_srcs "${CMAKE_CURRENT_SOURCE_DIR}/generated/${hw_proto_filename}.grpc.pb.cc")
    set(hw_grpc_hdrs "${CMAKE_CURRENT_SOURCE_DIR}/generated/${hw_proto_filename}.grpc.pb.h")
    add_custom_command(
            OUTPUT "${hw_proto_srcs}" "${hw_proto_hdrs}" "${hw_grpc_srcs}" "${hw_grpc_hdrs}"
            COMMAND ${_PROTOBUF_PROTOC}
            ARGS --grpc_out "${CMAKE_CURRENT_SOURCE_DIR}/generated"
            --cpp_out "${CMAKE_CURRENT_SOURCE_DIR}/generated"
            -I "${hw_proto_path}"
            --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
            "${hw_proto}"
            DEPENDS "${hw_proto}")

    # hw_grpc_proto
    add_library(proto_${hw_proto_filename}
            ${hw_grpc_srcs}
            ${hw_grpc_hdrs}
            ${hw_proto_srcs}
            ${hw_proto_hdrs})
    target_link_libraries(proto_${hw_proto_filename}
            ${_REFLECTION}
            ${_GRPC_GRPCPP}
            ${_PROTOBUF_LIBPROTOBUF})

    target_link_libraries(Zentrale
            proto_${hw_proto_filename}
            ${_REFLECTION}
            ${_GRPC_GRPCPP}
            ${_PROTOBUF_LIBPROTOBUF})
endforeach()

# Include generated *.pb.h files
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/generated")
