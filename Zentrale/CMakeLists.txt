cmake_minimum_required(VERSION 3.19)
project(Zentrale)

set(CMAKE_CXX_STANDARD 20)

add_executable(Zentrale src/cpp/main.cpp src/cpp/Zentrale.cpp src/header/Zentrale.h src/cpp/Webserver.cpp src/header/Webserver.h src/cpp/Komponente.cpp src/header/Komponente.h src/cpp/Erzeuger.cpp src/header/Erzeuger.h src/cpp/Verbraucher.cpp src/header/Verbraucher.h src/cpp/UDPSocket.cpp src/header/UDPSocket.h src/cpp/TCPSocket.cpp src/header/TCPSocket.h src/cpp/Socket.cpp src/header/Socket.h src/cpp/WebserverHandler.cpp src/header/WebserverHandler.h)