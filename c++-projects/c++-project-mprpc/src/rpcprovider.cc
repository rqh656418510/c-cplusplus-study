#include "rpcprovider.h"

#include "mprpcapplication.h"
#include "rpcheader.pb.h"

// 注册 RPC 服务
void RpcProvider::RegisterService(google::protobuf::Service* service) {
    // RPC 服务的信息
    ServiceInfo servcieInfo;

    // 获取 RPC 服务的描述信息
    const google::protobuf::ServiceDescriptor* pserviceDesc = service->GetDescriptor();

    // 获取 RPC 服务的名称
    const std::string serviceName(pserviceDesc->name());

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
        // 打印日志信息
        std::cout << "register rpc service " << serviceName << ":" << methodName << std::endl;
    }

    // 存储 RPC 服务的信息
    servcieInfo.m_service = service;
    m_serviceMap.insert({serviceName, servcieInfo});
}

// 启动 RPC 服务节点，开始对外提供 RPC 远程网络调用服务
void RpcProvider::Run() {
    // 创建 TCP 服务器
    std::string ip = MprpcApplication::GetInstance().GetConfig().Load("rpc-server-ip");
    std::string port = MprpcApplication::GetInstance().GetConfig().Load("rpc-server-port");
    muduo::net::InetAddress address(ip, atoi(port.c_str()));
    muduo::net::TcpServer tcpServer(&m_eventloop, address, "RpcProvider");

    // 设置 TCP 连接创建和断开的回调
    tcpServer.setConnectionCallback(bind(&RpcProvider::onConnection, this, std::placeholders::_1));

    // 设置已建立 TCP 连接读写事件的回调
    tcpServer.setMessageCallback(
        bind(&RpcProvider::onMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

    // 设置 EventLoop 的线程数量（比如：1 个 I/O 线程，3 个 Worker 线程）
    tcpServer.setThreadNum(4);

    // 打印日志信息
    std::cout << "RpcProvider start service at " << ip << ":" << port << std::endl;

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
    std::string recv_buf = buf->retrieveAllAsString();

    // 从字符流中读取前 4 个字节的内容
    uint32_t header_size = 0;
    recv_buf.copy((char*)&header_size, 4, 0);

    // 根据 header_size 读取请求数据头的原始字符流
    std::string rpc_header_str = recv_buf.substr(4, header_size);

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
        std::cout << "rpc_header_str " << rpc_header_str << " unserialize error!" << std::endl;
        return;
    }

    // 获取 RPC 调用的参数的字符流数据
    std::string rpc_args_str = recv_buf.substr(4 + header_size, args_size);

    // 打印日志信息
    std::cout << "===========================================" << std::endl;
    std::cout << "header_size: " << header_size << std::endl;
    std::cout << "rpc_header_str: " << rpc_header_str << std::endl;
    std::cout << "service_name: " << service_name << std::endl;
    std::cout << "method_name: " << method_name << std::endl;
    std::cout << "args_size: " << args_size << std::endl;
    std::cout << "args_str: " << rpc_args_str << std::endl;
    std::cout << "===========================================" << std::endl;

    // 查找 RPC 服务
    auto sit = m_serviceMap.find(service_name);
    if (sit == m_serviceMap.end()) {
        // 打印日志信息
        std::cout << "rpc service " << service_name << " is not exist!" << std::endl;
        return;
    }

    // 查找 RPC 服务的方法
    auto mit = sit->second.m_methodMap.find(method_name);
    if (mit == sit->second.m_methodMap.end()) {
        // 打印日志信息
        std::cout << "rpc method " << service_name << ":" << method_name << " is not exist!" << std::endl;
        return;
    }

    // 获取 RPC 调用的服务和方法
    google::protobuf::Service* service = sit->second.m_service;
    const google::protobuf::MethodDescriptor* method = mit->second;

    // 通过反序列化生成本地 RPC 方法调用的请求参数
    google::protobuf::Message* request = service->GetRequestPrototype(method).New();
    if (!request->ParseFromString(rpc_args_str)) {
        // 打印日志信息
        std::cout << "rpc request args '" << rpc_args_str << "' unserialize error!" << std::endl;
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
        std::cout << "rpc response serialize error!" << std::endl;
    }
    // 模拟 HTTP 的短连接服务，由 RPC 服务提供方主动断开连接
    conn->shutdown();
}