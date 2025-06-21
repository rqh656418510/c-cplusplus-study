#include "mprpcchannel.h"

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cerrno>
#include <cstdlib>
#include <random>
#include <string>

#include "logger.h"
#include "mprpcapplication.h"
#include "rpcheader.pb.h"
#include "zookeeperclient.h"

// 随机生成一个整数，范围 [0, range-1]
int MprpcChannel::randomInt(int range) {
    if (range > 0) {
        static thread_local std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<> dis(0, range - 1);
        return dis(gen);
    }
    return 0;
}

// 统一实现 RPC 方法调用的数据序列化和网络数据发送（针对 RPC 服务调用者）
void MprpcChannel::CallMethod(const google::protobuf::MethodDescriptor* method,
                              google::protobuf::RpcController* controller, const google::protobuf::Message* request,
                              google::protobuf::Message* response, google::protobuf::Closure* done) {
    // 获取 RPC 服务的完整名称（加上包名），比如 user.UserServiceRpc
    const std::string service_name(method->service()->full_name());

    // 获取 RPC 调用的方法名称
    const std::string method_name(method->name());

    // 获取 RPC 调用参数的序列化字符串的长度
    uint32_t args_size = 0;
    std::string rpc_args_str;
    if (request->SerializeToString(&rpc_args_str)) {
        args_size = rpc_args_str.size();
    } else {
        // 设置 RPC 调用状态
        controller->SetFailed("rpc request serialize error!");
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
        // 设置 RPC 调用状态
        controller->SetFailed("rpc header serialize error!");
        return;
    }

    // 通过网络发送的数据，格式：header_size（4 字节） + header_str（service_name + method_name + args_size） + args_str
    std::string rpc_send_str;
    rpc_send_str.insert(0, std::string((char*)&header_size, 4));
    rpc_send_str += rpc_header_str;
    rpc_send_str += rpc_args_str;

    // 打印日志信息
    LOG_DEBUG("===========================================");
    LOG_DEBUG("header_size: %u", header_size);
    LOG_DEBUG("rpc_header_str: %s", rpc_header_str.c_str());
    LOG_DEBUG("service_name: %s", service_name.c_str());
    LOG_DEBUG("method_name: %s", method_name.c_str());
    LOG_DEBUG("args_size: %u", args_size);
    LOG_DEBUG("args_str: %s", rpc_args_str.c_str());
    LOG_DEBUG("===========================================");

    // 本地创建一个 TCP 客户端
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == clientfd) {
        char errtxt[512] = {0};
        sprintf(errtxt, "create socket failed, errno is %d", errno);
        // 设置 RPC 调用状态
        controller->SetFailed(errtxt);
        return;
    }

    // 获取 ZK 服务端的连接信息
    const std::string zk_server_host = MprpcApplication::GetInstance().GetConfig().Load(ZK_SERVER_HOST_KEY);
    const std::string zk_server_port = MprpcApplication::GetInstance().GetConfig().Load(ZK_SERVER_PORT_KEY);

    // 创建 ZK 客户端
    ZkClient zkClient;

    // 启动 ZK 客户端
    bool started = zkClient.Start(zk_server_host, atoi(zk_server_port.c_str()));

    // 如果 ZK 服务端启动失败
    if (!started) {
        // 设置 RPC 调用状态
        controller->SetFailed("zookeeper client connect failed");
        return;
    }

    // RPC 服务对应的 ZNode 节点的路径，比如 /mprpc/services/user.UserServiceRpc
    const std::string node_path = ZNODE_PATH_PREFIX + "/" + service_name;

    // 获取 ZNode 子节点列表（即已注册的 RPC 服务列表），比如 127.0.0.1:7070
    std::vector<std::string> child_list = zkClient.GetChildren(node_path.c_str());

    // 如果 ZNode 子节点列表为空（即查找不到已注册的 RPC 服务）
    if (child_list.empty()) {
        char errtxt[512] = {0};
        sprintf(errtxt, "not found rpc service %s", service_name.c_str());
        // 设置 RPC 调用状态
        controller->SetFailed(errtxt);
        return;
    }

    // 随机获取一个 RPC 服务提供者的地址，比如 127.0.0.1:7070
    const int index = child_list.size() == 1 ? 0 : randomInt(child_list.size());
    const std::string rpc_provider_addr = child_list[index];

    // 解析 PRC 服务提供者的 IP 和端口
    const size_t pos = rpc_provider_addr.find(":");
    // 如果 RPC 服务提供者的地址无效
    if (std::string::npos == pos) {
        char errtxt[512] = {0};
        sprintf(errtxt, "invalid rpc service address %s", rpc_provider_addr.c_str());
        // 设置 RPC 调用状态
        controller->SetFailed(errtxt);
        return;
    }
    const std::string rpc_provider_ip = rpc_provider_addr.substr(0, pos);
    const std::string rpc_provider_port = rpc_provider_addr.substr(pos + 1);

    // 打印日志信息
    LOG_INFO("ready to invoke rpc service, name: %s, address: %s", service_name.c_str(), rpc_provider_addr.c_str());

    // 封装 TCP 客户端的连接信息
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(rpc_provider_port.c_str()));
    server_addr.sin_addr.s_addr = inet_addr(rpc_provider_ip.c_str());

    // 通过 TCP 客户端连接 RPC 服务节点
    if (-1 == connect(clientfd, (struct sockaddr*)&server_addr, sizeof(server_addr))) {
        // 关闭连接
        close(clientfd);
        // 设置 RPC 调用状态
        char errtxt[512] = {0};
        sprintf(errtxt, "connect server failed, errno is %d", errno);
        controller->SetFailed(errtxt);
        return;
    }

    // 通过网络发送 RPC 调用的请求参数
    if (-1 == send(clientfd, rpc_send_str.c_str(), rpc_send_str.size(), 0)) {
        // 关闭连接
        close(clientfd);
        // 设置 RPC 调用状态
        char errtxt[512] = {0};
        sprintf(errtxt, "send rpc rquest failed, errno is %d", errno);
        controller->SetFailed(errtxt);
        return;
    }

    // 通过网络接收 RPC 调用的响应结果
    int recv_size = 0;
    char recv_buf[1024] = {0};
    if (-1 == (recv_size = recv(clientfd, recv_buf, 1024, 0))) {
        // 关闭连接
        close(clientfd);
        // 设置 RPC 调用状态
        char errtxt[512] = {0};
        sprintf(errtxt, "receive rpc response failed, errno is %d", errno);
        controller->SetFailed(errtxt);
        return;
    }

    // 反序列化 RPC 调用的响应结果
    if (!response->ParseFromArray(recv_buf, recv_size)) {
        // 关闭连接
        close(clientfd);
        // 设置 RPC 调用状态
        char errtxt[1024] = {0};
        sprintf(errtxt, "rpc response unserialize failed, response content is %s", recv_buf);
        controller->SetFailed(errtxt);
        return;
    }

    // 关闭连接
    close(clientfd);
}
