#include <iostream>

#include "InetAddress.h"
#include "Logger.h"
#include "TcpServer.h"
#include "Timestamp.h"

void inetAddress() {
    InetAddress addr(8080, "192.168.1.1");
    std::cout << "ip = " + addr.toIp() << std::endl;
    std::cout << "port = " + std::to_string(addr.toPort()) << std::endl;
    std::cout << "address = " + addr.toIpPort() << std::endl;
}

void timestamp() {
    Timestamp time = Timestamp::now();
    std::cout << time.toString() << std::endl;
}

void logger() {
    LOG_DEBUG("%s", "output debug log msg");
    LOG_INFO("%s", "output info log msg");
    LOG_ERROR("%s", "output error log msg");
}

int main() {
    // inetAddress();
    // timestamp();
    logger();

    // 等待退出程序
    getchar();

    return 0;
}