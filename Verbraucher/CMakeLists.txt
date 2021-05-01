cmake_minimum_required(VERSION 3.19)
project(Verbraucher)

set(CMAKE_CXX_STANDARD 20)

find_package(Threads REQUIRED)

add_executable(Verbraucher src/cpp/main.cpp src/cpp/Verbraucher.cpp src/header/Verbraucher.h src/cpp/Haushalt.cpp src/header/Haushalt.h src/cpp/Unternehmen.cpp src/header/Unternehmen.h src/cpp/Simulator.cpp src/header/Simulator.h)

target_link_libraries(Verbraucher ${CMAKE_THREAD_LIBS_INIT})