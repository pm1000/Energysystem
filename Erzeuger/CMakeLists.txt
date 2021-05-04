cmake_minimum_required(VERSION 3.19)
project(Erzeuger)

set(CMAKE_CXX_STANDARD 20)

add_executable(Erzeuger src/cpp/main.cpp src/cpp/Erzeuger.cpp src/header/Erzeuger.h src/cpp/Solar.cpp src/header/Solar.h src/cpp/Wind.cpp src/header/Wind.h src/cpp/Kohle.cpp src/header/Kohle.h src/cpp/Atom.cpp src/header/Atom.h src/cpp/ZentralenKommunikation.cpp src/header/ZentralenKommunikation.h src/cpp/UDPKommunikation.cpp src/header/UDPKommunikation.h src/cpp/Simulator.cpp src/header/Simulator.h)