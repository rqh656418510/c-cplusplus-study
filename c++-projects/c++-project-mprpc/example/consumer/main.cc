#include <iostream>

#include "friend.pb.h"
#include "mprpcapplication.h"
#include "mprpcchannel.h"
#include "user.pb.h"

void Register() {
    // RPC 调用的通道
    google::protobuf::RpcChannel* channel = new MprpcChannel();

    // RPC 调用的代理对象
    user::UserServiceRpc_Stub stub(channel);

    // RPC 调用的请求参数
    user::RegisterRequest request;
    request.set_name("jim");
    request.set_password("123456");

    // RPC 调用的响应结果
    user::RegisterResponse response;

    // 发起 RPC 调用，底层实际上调用的是 RpcChannel::CallMethod()
    stub.Register(nullptr, &request, &response, nullptr);

    // 获取 RPC 调用的响应结果
    if (0 == response.result().errcode()) {
        std::cout << "rpc Register function invoke success" << std::endl;
    } else {
        std::cout << "rpc Register function invoke error: " << response.result().errmsg() << std::endl;
    }
}

void Login() {
    // RPC 调用的通道
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
}

void GetFriendList() {
    // RPC 调用通道
    google::protobuf::RpcChannel* channel = new MprpcChannel();

    // RPC 调用的代理对象
    friends::FriendServiceRpc_Stub stub(channel);

    // RPC 调用的请求参数
    friends::GetFriendListRequest request;
    request.set_userid(3);

    // RPC 调用的响应结果
    friends::GetFriendListResponse response;

    // 发起 RPC 调用，底层实际上调用的是 RpcChannel::CallMethod()
    stub.GetFriendList(nullptr, &request, &response, nullptr);

    // 获取 RPC 调用的响应结果
    if (0 == response.result().errcode()) {
        std::cout << "rpc GetFriendList function invoke success" << std::endl;
        // 获取返回的数据
        auto friends = response.friends();
        for (auto& item : friends) {
            std::cout << "userid: " << item.userid() << ", username: " << item.username() << ", sex: " << item.sex()
                      << std::endl;
        }
    } else {
        std::cout << "rpc GetFriendList function invoke error: " << response.result().errmsg() << std::endl;
    }
}

// 测试 RPC 服务的调用
int main(int argc, char** argv) {
    // 调用 RPC 框架的初始化操作（比如加载 RPC 配置文件）
    MprpcApplication::GetInstance().Init(argc, argv);

    // 调用 RPC 注册方法
    Register();
    std::cout << std::endl;

    // 调用 RPC 登录方法
    Login();
    std::cout << std::endl;

    // 调用 RPC 获取好友列表方法
    GetFriendList();
    std::cout << std::endl;

    return 0;
}