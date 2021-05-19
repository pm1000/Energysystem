cmake_minimum_required(VERSION 3.16)
project(Verbraucher)

set(CMAKE_CXX_STANDARD 20)

find_package(Threads REQUIRED)

add_executable(Verbraucher src/cpp/main.cpp src/cpp/Komponente/Verbraucher.cpp src/header/Komponente/Verbraucher.h src/cpp/Komponente/Haushalt.cpp src/header/Komponente/Haushalt.h src/cpp/Komponente/Unternehmen.cpp src/header/Komponente/Unternehmen.h src/cpp/Simulator.cpp src/header/Simulator.h src/cpp/ZentralenKommunikation.cpp src/header/ZentralenKommunikation.h src/cpp/UDP/UDPKommunikation.cpp src/header/UDP/UDPKommunikation.h)

target_link_libraries(Verbraucher ${CMAKE_THREAD_LIBS_INIT})