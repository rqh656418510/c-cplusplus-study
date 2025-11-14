#include <iostream>

#include "InetAddress.h"
#include "TcpServer.h"

void inetAddress() {
    InetAddress addr(8080, "192.168.1.1");
    std::cout << "ip = " + addr.toIp() << std::endl;
    std::cout << "port = " + std::to_string(addr.toPort()) << std::endl;
    std::cout << "address = " + addr.toIpPort() << std::endl;
}

int main() {
    inetAddress();
    return 0;
}