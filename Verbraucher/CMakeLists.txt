cmake_minimum_required(VERSION 3.16)
project(Verbraucher)

set(CMAKE_CXX_STANDARD 20)

# Main target
add_executable(Verbraucher src/cpp/main.cpp src/cpp/Komponente/Verbraucher.cpp src/header/Komponente/Verbraucher.h src/cpp/Komponente/Haushalt.cpp src/header/Komponente/Haushalt.h src/cpp/Komponente/Unternehmen.cpp src/header/Komponente/Unternehmen.h src/cpp/Simulator.cpp src/header/Simulator.h src/cpp/Kommunikation/ZentralenKommunikation.cpp src/header/Kommunikation/ZentralenKommunikation.h src/cpp/Kommunikation/UDPKommunikation.cpp src/header/Kommunikation/UDPKommunikation.h src/cpp/Kommunikation/UDPServer.cpp)


# Thread stuff
find_package(Threads REQUIRED)
target_link_libraries(Verbraucher ${CMAKE_THREAD_LIBS_INIT})


#Mqtt stuff
find_package(PahoMqttCpp REQUIRED)
target_link_libraries(Verbraucher paho-mqttpp3)
target_link_libraries(Verbraucher paho-mqtt3a)
target_link_libraries(Verbraucher paho-mqtt3c)

