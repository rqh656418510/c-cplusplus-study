#include "mprpcchannel.h"

#include <arpa/inet.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <string>

#include "mprpcapplication.h"
#include "rpcheader.pb.h"

// 统一实现 RPC 方法调用的数据序列化和网络数据发送
void MprpcChannel::CallMethod(const google::protobuf::MethodDescriptor* method,
                              google::protobuf::RpcController* controller, const google::protobuf::Message* request,
                              google::protobuf::Message* response, google::protobuf::Closure* done) {
    // 获取 RPC 调用的服务名称
    std::string service_name(method->service()->name());

    // 获取 RPC 调用的方法名称
    std::string method_name(method->name());

    // 获取 RPC 调用参数的序列化字符串的长度
    uint32_t args_size = 0;
    std::string rpc_args_str;
    if (request->SerializeToString(&rpc_args_str)) {
        args_size = rpc_args_str.size();
    } else {
        // 打印日志信息
        std::cout << "rpc request serialize error!" << std::endl;
        return;
    }

    // 定义 RPC 调用的请求数据头
    mprpc::RpcHeader rpcHeader;
    rpcHeader.set_service_name(service_name);
    rpcHeader.set_method_name(method_name);
    rpcHeader.set_args_size(args_size);

    // 获取 RPC 请求数据头的序列化字符串的长度
    uint32_t header_size = 0;
    std::string rpc_header_str;
    if (rpcHeader.SerializeToString(&rpc_header_str)) {
        header_size = rpc_header_str.size();
    } else {
        // 打印日志信息
        std::cout << "rpc header serialize error!" << std::endl;
        return;
    }

    // 网络发送的数据，格式：header_size（4 字节） + header_str（service_name + method_name + args_size） + args_str
    std::string rpc_send_str;
    rpc_header_str.insert(0, std::string((char*)&header_size, 4));
    rpc_send_str += rpc_header_str;
    rpc_send_str += rpc_args_str;

    // 打印日志信息
    std::cout << "===========================================" << std::endl;
    std::cout << "header_size: " << header_size << std::endl;
    std::cout << "rpc_header_str: " << rpc_header_str << std::endl;
    std::cout << "service_name: " << service_name << std::endl;
    std::cout << "method_name: " << method_name << std::endl;
    std::cout << "args_size: " << args_size << std::endl;
    std::cout << "args_str: " << rpc_args_str << std::endl;
    std::cout << "===========================================" << std::endl;

    // 本地启动一个 TCP 客户端
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == clientfd) {
        // 打印日志信息
        std::cout << "create socket failed, errno is " << errno << std::endl;
        exit(EXIT_FAILURE);
    }

    // TCP 客户端的连接信息
    std::string ip = MprpcApplication::GetInstance().GetConfig().Load("rpc-server-ip");
    std::string port = MprpcApplication::GetInstance().GetConfig().Load("rpc-server-port");

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(port.c_str()));
    server_addr.sin_addr.s_addr = inet_addr(ip.c_str());

    // 连接 RPC 服务节点
    if (-1 == connect(clientfd, (struct sockaddr*)&server_addr, sizeof(server_addr))) {
        // 打印日志信息
        std::cout << "connect rpc server failed, errno is" << errno << std::endl;
        // 关闭连接
        close(clientfd);
        exit(EXIT_FAILURE);
    }

    // 发送 RPC 调用的请求参数
    if (-1 == send(clientfd, rpc_send_str.c_str(), rpc_send_str.size(), 0)) {
        // 打印日志信息
        std::cout << "send rpc rquest failed, errno is" << errno << std::endl;
        // 关闭连接
        close(clientfd);
        return;
    }

    // 接收 RPC 调用的响应结果
    int recv_size = 0;
    char recv_buf[1024] = {0};
    if (-1 == (recv_size = recv(clientfd, recv_buf, 1024, 0))) {
        // 打印日志信息
        std::cout << "receive rpc response failed, errno is" << errno << std::endl;
        // 关闭连接
        close(clientfd);
        return;
    }

    std::string response_str(recv_buf, 0, recv_size);

    // 反序列化 RPC 调用的响应结果
    if (!response->ParseFromString(response_str)) {
        // 打印日志信息
        std::cout << "rpc response unserialize failed, response_str: " << response_str << std::endl;
        // 关闭连接
        close(clientfd);
        return;
    }

    // 关闭连接
    close(clientfd);
}