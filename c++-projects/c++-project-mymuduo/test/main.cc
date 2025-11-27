#include <iostream>
#include <thread>

#include "CurrentThread.h"
#include "InetAddress.h"
#include "Logger.h"
#include "TcpServer.h"
#include "Timestamp.h"

class LoggerTest {
public:
    void log() {
        LOG_DEBUG("%s => %s", __PRETTY_FUNCTION__, "output debug log msg");
        LOG_INFO("%s => %s", __PRETTY_FUNCTION__, "output info log msg");
        LOG_ERROR("%s => %s", __PRETTY_FUNCTION__, "output error log msg");
    }
};

void inetAddressTest() {
    InetAddress addr(8080, "192.168.1.1");
    std::cout << "ip = " + addr.toIp() << std::endl;
    std::cout << "port = " + std::to_string(addr.toPort()) << std::endl;
    std::cout << "address = " + addr.toIpPort() << std::endl;
}

void timestampTest() {
    Timestamp time = Timestamp::now();
    std::cout << "timestamp = " << time.toString() << std::endl;
}

void logTest() {
    LoggerTest logger;
    logger.log();
}

void threadIdTest() {
    std::thread t1([] { LOG_INFO("I'm thread 1"); });
    std::thread t2([] { LOG_INFO("I'm thread 2"); });
    t1.join();
    t2.join();
}

int main() {
    inetAddressTest();
    timestampTest();
    logTest();
    threadIdTest();

    // 等待退出程序
    getchar();

    return 0;
}