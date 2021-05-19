cmake_minimum_required(VERSION 3.16)
project(Erzeuger)

set(CMAKE_CXX_STANDARD 20)

find_package(Threads REQUIRED)

add_executable(Erzeuger src/cpp/main.cpp src/cpp/Komponente/Erzeuger.cpp src/header/Komponente/Erzeuger.h src/cpp/Komponente/Solar.cpp src/header/Komponente/Solar.h src/cpp/Komponente/Wind.cpp src/header/Komponente/Wind.h src/cpp/Komponente/Kohle.cpp src/header/Komponente/Kohle.h src/cpp/Komponente/Atom.cpp src/header/Komponente/Atom.h src/cpp/ZentralenKommunikation.cpp src/header/ZentralenKommunikation.h src/cpp/UDP/UDPKommunikation.cpp src/header/UDP/UDPKommunikation.h src/cpp/Simulator.cpp src/header/Simulator.h)

target_link_libraries(Erzeuger ${CMAKE_THREAD_LIBS_INIT})