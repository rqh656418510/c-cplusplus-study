/**
 * 一个简单的基于 epoll 的 C++ 回声（echo）服务器示例，使用 level-triggered（水平触发）与非阻塞 socket。
 * 包含创建监听 socket、将 socket 设置为非阻塞、将监听 socket 和客户端 socket 注册到 epoll、以及基本的读写和关闭处理。
 *
 * Linux 上运行程序：./epoll_example 8080
 */

#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

static int set_nonblocking(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1) return -1;
    return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <port>\n";
        return 1;
    }
    int port = std::atoi(argv[1]);

    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd < 0) {
        perror("socket");
        return 1;
    }

    int opt = 1;
    setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in addr {};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    if (bind(listen_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind");
        close(listen_fd);
        return 1;
    }

    if (listen(listen_fd, SOMAXCONN) < 0) {
        perror("listen");
        close(listen_fd);
        return 1;
    }

    if (set_nonblocking(listen_fd) < 0) {
        perror("set_nonblocking");
        close(listen_fd);
        return 1;
    }

    int epfd = epoll_create1(0);
    if (epfd < 0) {
        perror("epoll_create1");
        close(listen_fd);
        return 1;
    }

    epoll_event ev{};
    ev.events = EPOLLIN;  // level-triggered（水平触发）
    ev.data.fd = listen_fd;
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, listen_fd, &ev) < 0) {
        perror("epoll_ctl: listen_fd");
        close(listen_fd);
        close(epfd);
        return 1;
    }

    std::vector<epoll_event> events(64);
    const size_t BUF_SZ = 4096;
    char buf[BUF_SZ];

    std::cout << "epoll echo server listening on port " << port << "\n";

    while (true) {
        int n = epoll_wait(epfd, events.data(), (int)events.size(), -1);
        if (n < 0) {
            if (errno == EINTR) continue;
            perror("epoll_wait");
            break;
        }

        for (int i = 0; i < n; ++i) {
            int fd = events[i].data.fd;
            uint32_t evts = events[i].events;

            if (fd == listen_fd) {
                // accept 循环（非阻塞）
                while (true) {
                    struct sockaddr_in cli_addr {};
                    socklen_t cli_len = sizeof(cli_addr);
                    int conn = accept(listen_fd, (struct sockaddr*)&cli_addr, &cli_len);
                    if (conn < 0) {
                        if (errno == EAGAIN || errno == EWOULDBLOCK) break;
                        perror("accept");
                        break;
                    }
                    set_nonblocking(conn);
                    epoll_event cev{};
                    cev.events = EPOLLIN;  // 可以添加 EPOLLRDHUP 来检测远端关闭
                    cev.data.fd = conn;
                    if (epoll_ctl(epfd, EPOLL_CTL_ADD, conn, &cev) < 0) {
                        perror("epoll_ctl: conn");
                        close(conn);
                    } else {
                        char addrstr[INET_ADDRSTRLEN];
                        inet_ntop(AF_INET, &cli_addr.sin_addr, addrstr, sizeof(addrstr));
                        std::cout << "accepted " << addrstr << ":" << ntohs(cli_addr.sin_port) << " fd=" << conn
                                  << "\n";
                    }
                }
            } else {
                if (evts & (EPOLLERR | EPOLLHUP)) {
                    // 套接字发生错误或挂断
                    std::cerr << "epoll error on fd " << fd << "\n";
                    epoll_ctl(epfd, EPOLL_CTL_DEL, fd, nullptr);
                    close(fd);
                    continue;
                }

                if (evts & EPOLLIN) {
                    // 读取所有可用数据
                    while (true) {
                        ssize_t count = read(fd, buf, BUF_SZ);
                        if (count == 0) {
                            // 对端关闭连接
                            std::cout << "peer closed fd=" << fd << "\n";
                            epoll_ctl(epfd, EPOLL_CTL_DEL, fd, nullptr);
                            close(fd);
                            break;
                        } else if (count < 0) {
                            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                                // 数据已全部读取
                                break;
                            } else {
                                perror("read");
                                epoll_ctl(epfd, EPOLL_CTL_DEL, fd, nullptr);
                                close(fd);
                                break;
                            }
                        } else {
                            // 回显：write 可能为部分写入，尝试写入剩余数据
                            ssize_t written = 0;
                            while (written < count) {
                                ssize_t w = write(fd, buf + written, count - written);
                                if (w < 0) {
                                    if (errno == EAGAIN || errno == EWOULDBLOCK) {
                                        // 会阻塞；跳过剩余（生产环境应注册 EPOLLOUT）
                                        break;
                                    } else {
                                        perror("write");
                                        epoll_ctl(epfd, EPOLL_CTL_DEL, fd, nullptr);
                                        close(fd);
                                        goto next_event;
                                    }
                                }
                                written += w;
                            }
                        }
                    }
                }

            // 标签：在嵌套循环中关闭连接后用于继续外层循环
            next_event:
                continue;
            }
        }
    }

    close(epfd);
    close(listen_fd);
    return 0;
}