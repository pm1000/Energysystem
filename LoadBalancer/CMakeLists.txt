cmake_minimum_required(VERSION 3.19)
project(LoadBalancer)

set(CMAKE_CXX_STANDARD 20)

# Main target
add_executable(LoadBalancer src/cpp/main.cpp src/cpp/Zentrale/Zentrale.cpp src/header/Zentrale/Zentrale.h src/cpp/WebServer/TcpServer.cpp src/cpp/WebServer/TcpServerSocket.cpp src/cpp/Zentrale/ZentralenController.cpp src/header/Zentrale/ZentralenController.h src/cpp/UDPServer/UDPServer.cpp src/cpp/UDPServer/UDPSender.cpp src/header/UDPServer/UDPSender.h)

# Thread stuff
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package (Threads REQUIRED)
target_link_libraries(LoadBalancer ${CMAKE_THREAD_LIBS_INIT})
