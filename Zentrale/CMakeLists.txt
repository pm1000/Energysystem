cmake_minimum_required(VERSION 3.19)
project(Zentrale)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package (Threads REQUIRED)

add_executable(Zentrale src/cpp/main.cpp src/cpp/Zentrale.cpp src/header/Zentrale.h src/cpp/Webserver.cpp src/header/Webserver.h src/cpp/Komponente.cpp src/header/Komponente.h src/cpp/Erzeuger.cpp src/header/Erzeuger.h src/cpp/Verbraucher.cpp src/header/Verbraucher.h src/cpp/UDPServer.cpp src/header/UDPServer.h src/cpp/WebserverHandler.cpp src/header/WebserverHandler.h src/header/UDPCallback.h src/cpp/HTTPIntepreter.cpp src/header/HTTPIntepreter.h src/header/HTTPCallback.h  src/cpp/KomponentenController.cpp src/header/KomponentenController.h)
target_link_libraries(Zentrale ${CMAKE_THREAD_LIBS_INIT})