#include <iostream>

#include "mprpcapplication.h"
#include "mprpcchannel.h"
#include "user.pb.h"

// 测试 RPC 服务的调用
int main(int argc, char** argv) {
    // 调用 RPC 框架的初始化操作（比如加载 RPC 配置文件）
    MprpcApplication::GetInstance().Init(argc, argv);

    // PRC 调用的通道
    google::protobuf::RpcChannel* channel = new MprpcChannel();

    // RPC 调用的代理对象
    user::UserServiceRpc_Stub stub(channel);

    // RPC 调用的请求参数
    user::LoginRequest request;
    request.set_name("jim");
    request.set_password("123456");

    // RPC 调用的响应结果
    user::LoginResponse response;

    // 发起 RPC 调用，底层实际上调用的是 RpcChannel::CallMethod()
    stub.Login(nullptr, &request, &response, nullptr);

    // 获取 RPC 调用的响应结果
    if (0 == response.result().errcode()) {
        std::cout << "rpc Login function invoke success" << std::endl;
    } else {
        std::cout << "rpc Login function invoke error: " << response.result().errmsg() << std::endl;
    }

    return 0;
}