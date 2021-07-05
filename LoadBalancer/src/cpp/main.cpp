#include <iostream>
#include "../header/WebServer/TcpServer.h"

int main() {

    TcpServer tcpServer;
    tcpServer.init(10000, 9000);
    tcpServer();


    std::cout << "Hello, World!" << std::endl;
    return 0;
}
