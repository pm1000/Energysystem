cmake_minimum_required(VERSION 3.19)
project(Zentrale)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package (Threads REQUIRED)

add_executable(Zentrale src/cpp/main.cpp src/cpp/Zentrale.cpp src/header/Zentrale.h src/cpp/WebServer/Webserver.cpp src/header/WebServer/Webserver.h src/cpp/Komponenten/Komponente.cpp src/header/Komponenten/Komponente.h src/cpp/Komponenten/Erzeuger.cpp src/header/Komponenten/Erzeuger.h src/cpp/Komponenten/Verbraucher.cpp src/header/Komponenten/Verbraucher.h src/cpp/UDPServer/UDPServer.cpp src/header/UDPServer/UDPServer.h src/header/UDPServer/UDPCallback.h src/cpp/WebServer/HTTPIntepreter.cpp src/header/WebServer/HTTPIntepreter.h src/header/WebServer/HTTPCallback.h src/cpp/Komponenten/KomponentenController.cpp src/header/Komponenten/KomponentenController.h)
target_link_libraries(Zentrale ${CMAKE_THREAD_LIBS_INIT})