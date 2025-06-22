#include "mprpcprovider.h"

#include "mprpccontext.h"
#include "networkutil.h"
#include "rpcheader.pb.h"
#include "zookeeperclient.h"

// 发布 RPC 服务
void RpcProvider::PublishService(google::protobuf::Service* service) {
    // RPC 服务的信息
    ServiceInfo servcieInfo;

    // 获取 RPC 服务的描述信息
    const google::protobuf::ServiceDescriptor* pserviceDesc = service->GetDescriptor();

    // 获取 RPC 服务的完整名称（加上包名），比如 user.UserServiceRpc
    const std::string serviceName(pserviceDesc->full_name());

    // 获取 RPC 服务的方法数量
    int methodCount = pserviceDesc->method_count();

    // 遍历 RPC 服务的所有方法
    for (int i = 0; i < methodCount; i++) {
        // 获取 RPC 服务的方法的描述信息
        const google::protobuf::MethodDescriptor* pmethodDesc = pserviceDesc->method(i);
        // 获取 RPC 服务的方法的名称
        const std::string methodName(pmethodDesc->name());
        // 存储 RPC 服务的方法的描述信息
        servcieInfo.m_methodMap.insert({methodName, pmethodDesc});
    }

    // 存储 RPC 服务的信息
    servcieInfo.m_service = service;
    m_serviceMap.insert({serviceName, servcieInfo});
}

// 启动 RPC 服务节点，开始对外提供 RPC 远程网络调用服务（针对 RPC 服务提供者）
void RpcProvider::Run() {
    // 获取配置信息
    const std::string zk_server_host = MprpcContext::GetInstance().GetConfig().Load(ZK_SERVER_HOST_KEY);
    const std::string zk_server_port = MprpcContext::GetInstance().GetConfig().Load(ZK_SERVER_PORT_KEY);
    const std::string rpc_network_interface = MprpcContext::GetInstance().GetConfig().Load(RPC_NETWORK_INTERFACE_KEY);

    // 获取 RPC 服务提供者的 IP 和端口
    const std::string rpc_server_ip = NetworkUtil::GetInstance().FindLocalIp(rpc_network_interface);
    const int rpc_server_port = NetworkUtil::GetInstance().FindAvailablePort();

    // 判断 RPC 服务提供者的端口是否有效
    if (-1 == rpc_server_port) {
        LOG_ERROR("not found available port for rpc server!");
        return;
    }

    // 创建 TCP 服务器
    muduo::net::InetAddress address(rpc_server_ip, rpc_server_port);
    muduo::net::TcpServer tcpServer(&m_eventloop, address, "RpcProvider");

    // 设置 TCP 连接创建和断开的回调
    tcpServer.setConnectionCallback(bind(&RpcProvider::onConnection, this, std::placeholders::_1));

    // 设置已建立 TCP 连接读写事件的回调
    tcpServer.setMessageCallback(
        bind(&RpcProvider::onMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

    // 设置 EventLoop 的线程数量（比如：1 个 I/O 线程，3 个 Worker 线程）
    tcpServer.setThreadNum(4);

    // 创建 ZK 客户端
    ZkClient zkClient;

    // 启动 ZK 客户端
    bool started = zkClient.Start(zk_server_host, atoi(zk_server_port.c_str()));
    // ZK 服务端连接失败
    if (!started) {
        // 停止往下继续执行，直接返回
        return;
    }

    // 将所有已发布的 RPC 服务注册进 ZK 服务端
    for (auto& service : m_serviceMap) {
        // RPC 服务的 IP 和端口信息
        const std::string rpc_address = rpc_server_ip + ":" + std::to_string(rpc_server_port);

        // RPC 服务的名称（加上包名），比如 user.UserServiceRpc
        const std::string service_name = service.first;

        // ZNode 节点的路径前缀，比如 /mprpc/services/user.UserServiceRpc
        const std::string path_prefix = ZNODE_PATH_PREFIX + "/" + service_name;

        // ZNode 节点的完整路径，比如 /mprpc/services/user.UserServiceRpc/127.0.0.1:7070
        const std::string node_full_path = path_prefix + "/" + rpc_address;

        // ZNode 节点的数据，比如 127.0.0.1:7070
        const char* node_data = rpc_address.c_str();

        // ZNode 节点的数据长度
        const int node_data_len = rpc_address.length();

        // 创建 ZNode 节点（临时节点）
        const std::string created_path =
            zkClient.CreateRecursive(node_full_path.c_str(), node_data, node_data_len, ZOO_EPHEMERAL);

        // 判断 ZNode 节点是否创建成功（即 RPC 服务是否注册成功）
        if (!created_path.empty()) {
            // ZNode 节点创建成功
            LOG_INFO("success to register rpc service, name: %s, path: %s, data: %s", service_name.c_str(),
                     node_full_path.c_str(), node_data);
        } else {
            // ZNode 节点创建失败
            LOG_ERROR("failed to register rpc service, name: %s, path: %s, data: %s", service_name.c_str(),
                      node_full_path.c_str(), node_data);
        }
    }

    // 打印日志信息
    LOG_INFO("rpc provider start at %s:%d", rpc_server_ip.c_str(), rpc_server_port);

    // 启动 TCP 服务器
    tcpServer.start();

    // 以阻塞方式等待新客户端的连接、已连接客户端的读写事件等
    m_eventloop.loop();
}

// 处理 TCP 连接的创建和断开
void RpcProvider::onConnection(const muduo::net::TcpConnectionPtr& conn) {
    if (!conn->connected()) {
        // 断开连接（释放资源）
        conn->shutdown();
    }
}

// 处理 TCP 连接的读写事件（比如接收客户端发送的数据）
void RpcProvider::onMessage(const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* buf, muduo::Timestamp time) {
    // 接收到的字符流，数据格式：header_size（4 字节） + header_str（service_name + method_name + args_size） + args_str
    const std::string recv_buf = buf->retrieveAllAsString();

    // 从字符流中读取前 4 个字节的内容
    uint32_t header_size = 0;
    recv_buf.copy((char*)&header_size, 4, 0);

    // 根据 header_size 读取请求数据头的原始字符流
    const std::string rpc_header_str = recv_buf.substr(4, header_size);

    // RPC 调用的基础信息
    std::string service_name;
    std::string method_name;
    uint32_t args_size;

    // RPC 请求数据头的反序列化
    mprpc::RpcHeader rpcHeader;
    if (rpcHeader.ParseFromString(rpc_header_str)) {
        // 数据反序列化成功
        service_name = rpcHeader.service_name();
        method_name = rpcHeader.method_name();
        args_size = rpcHeader.args_size();
    } else {
        // 数据反序列化失败
        LOG_ERROR("rpc header string %s unserialize error!", rpc_header_str.c_str());
        return;
    }

    // 获取 RPC 调用的参数的字符流数据
    const std::string rpc_args_str = recv_buf.substr(4 + header_size, args_size);

    // 打印日志信息
    LOG_DEBUG("===========================================");
    LOG_DEBUG("header_size: %u", header_size);
    LOG_DEBUG("rpc_header_str: %s", rpc_header_str.c_str());
    LOG_DEBUG("service_name: %s", service_name.c_str());
    LOG_DEBUG("method_name: %s", method_name.c_str());
    LOG_DEBUG("args_size: %u", args_size);
    LOG_DEBUG("args_str: %s", rpc_args_str.c_str());
    LOG_DEBUG("===========================================");

    // 查找 RPC 服务
    auto sit = m_serviceMap.find(service_name);
    // 如果找不到对应的 RPC 服务
    if (sit == m_serviceMap.end()) {
        // 打印日志信息
        LOG_ERROR("rpc service %s is not exist!", service_name.c_str());
        return;
    }

    // 查找 RPC 服务的方法
    auto mit = sit->second.m_methodMap.find(method_name);
    if (mit == sit->second.m_methodMap.end()) {
        // 打印日志信息
        LOG_ERROR("rpc method %s::%s is not exist!", service_name.c_str(), method_name.c_str());
        return;
    }

    // 获取 RPC 调用的服务和方法
    google::protobuf::Service* service = sit->second.m_service;
    const google::protobuf::MethodDescriptor* method = mit->second;

    // 通过反序列化生成本地 RPC 方法调用的请求参数
    google::protobuf::Message* request = service->GetRequestPrototype(method).New();
    if (!request->ParseFromString(rpc_args_str)) {
        // 打印日志信息
        LOG_ERROR("rpc request args '%s' unserialize error!", rpc_args_str.c_str());
        return;
    }

    // 生成本地 RPC 方法调用的响应结果
    google::protobuf::Message* response = service->GetResponsePrototype(method).New();

    // 本地 RPC 方法调用的回调，实际上调用的是 RpcProvider::SendRpcResponse()
    google::protobuf::Closure* done =
        google::protobuf::NewCallback<RpcProvider, const muduo::net::TcpConnectionPtr&, google::protobuf::Message*>(
            this, &RpcProvider::SendRpcResponse, conn, response);

    // 调用 RPC 节点的本地方法
    service->CallMethod(method, nullptr, request, response, done);
}

// 用于序列化 RPC 调用的响应结果和发送网络响应数据
void RpcProvider::SendRpcResponse(const muduo::net::TcpConnectionPtr& conn, google::protobuf::Message* response) {
    // 序列化 RPC 调用的响应结果
    std::string response_str;
    if (response->SerializeToString(&response_str)) {
        // 通过网络将本地 RPC 方法的执行结果发送给 RPC 服务调用方
        conn->send(response_str);
    } else {
        // 打印日志信息
        LOG_ERROR("rpc response serialize error!");
    }
    // 模拟 HTTP 的短连接服务，由 RPC 服务提供方主动断开连接
    conn->shutdown();
}