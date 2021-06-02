cmake_minimum_required(VERSION 3.19)
project(Energieversorger)

set(CMAKE_CXX_STANDARD 20)

add_executable(Energieversorger src/cpp/main.cpp src/cpp/Komponenten/Komponente.cpp src/header/Komponenten/Komponente.h src/cpp/Komponenten/KomponentenController.cpp src/header/Komponenten/KomponentenController.h src/cpp/Komponenten/Erzeuger.cpp src/header/Komponenten/Erzeuger.h src/cpp/Komponenten/Verbraucher.cpp src/header/Komponenten/Verbraucher.h src/cpp/Client.cpp src/header/Client.h)