#include <iostream>
#include <memory>

#include "friend.pb.h"
#include "logger.h"
#include "mprpccontext.h"
#include "mprpccontroller.h"
#include "user.pb.h"

// 调用 RPC 注册方法
void Register() {
    // RPC 调用的通道
    std::unique_ptr<google::protobuf::RpcChannel> channel = std::make_unique<MprpcChannel>();

    // RPC 调用的状态控制器
    std::unique_ptr<google::protobuf::RpcController> controller = std::make_unique<MprpcController>();

    // RPC 调用的代理对象
    user::UserServiceRpc_Stub stub(channel.get());

    // RPC 调用的请求参数
    user::RegisterRequest request;
    request.set_name("jim");
    request.set_password("123456");

    // RPC 调用的响应结果
    user::RegisterResponse response;

    // 发起 RPC 调用，底层实际上调用的是 MprpcChannel::CallMethod()
    stub.Register(controller.get(), &request, &response, nullptr);

    // 判断 RPC 调用是否成功
    if (controller->Failed()) {
        return;
    }

    // 获取 RPC 调用的响应结果
    if (0 == response.result().errcode()) {
        LOG_INFO("rpc function Register invoke success");
    } else {
        LOG_ERROR("rpc function Register invoke error: %s", response.result().errmsg().c_str());
    }
}

// 调用 RPC 登录方法
void Login() {
    // RPC 调用的通道
    std::unique_ptr<google::protobuf::RpcChannel> channel = std::make_unique<MprpcChannel>();

    // RPC 调用的状态控制器
    std::unique_ptr<google::protobuf::RpcController> controller = std::make_unique<MprpcController>();

    // RPC 调用的代理对象
    user::UserServiceRpc_Stub stub(channel.get());

    // RPC 调用的请求参数
    user::LoginRequest request;
    request.set_name("jim");
    request.set_password("123456");

    // RPC 调用的响应结果
    user::LoginResponse response;

    // 发起 RPC 调用，底层实际上调用的是 MprpcChannel::CallMethod()
    stub.Login(controller.get(), &request, &response, nullptr);

    // 判断 RPC 调用是否成功
    if (controller->Failed()) {
        return;
    }

    // 获取 RPC 调用的响应结果
    if (0 == response.result().errcode()) {
        LOG_INFO("rpc function Login invoke success");
    } else {
        LOG_ERROR("rpc function Login invoke error: %s", response.result().errmsg().c_str());
    }
}

// 调用 RPC 获取好友列表方法
void GetFriendList() {
    // RPC 调用的通道
    std::unique_ptr<google::protobuf::RpcChannel> channel = std::make_unique<MprpcChannel>();

    // RPC 调用的状态控制器
    std::unique_ptr<google::protobuf::RpcController> controller = std::make_unique<MprpcController>();

    // RPC 调用的代理对象
    friends::FriendServiceRpc_Stub stub(channel.get());

    // RPC 调用的请求参数
    friends::GetFriendListRequest request;
    request.set_userid(3);

    // RPC 调用的响应结果
    friends::GetFriendListResponse response;

    // 发起 RPC 调用，底层实际上调用的是 MprpcChannel::CallMethod()
    stub.GetFriendList(controller.get(), &request, &response, nullptr);

    // 判断 RPC 调用是否成功
    if (controller->Failed()) {
        return;
    }

    // 获取 RPC 调用的响应结果
    if (0 == response.result().errcode()) {
        LOG_INFO("rpc function GetFriendList invoke success");

        // 获取返回的数据
        auto friends = response.friends();
        for (auto& item : friends) {
            LOG_INFO("userid: %u, username: %s, sex: %d", item.userid(), item.username().c_str(), item.sex());
        }
    } else {
        LOG_ERROR("rpc function GetFriendList invoke error: %s", response.result().errmsg().c_str());
    }
}

// 测试 RPC 服务的调用
int main(int argc, char** argv) {
    // 设置日志级别
    Logger::GetInstance().SetLogLevel(INFO);

    // 调用 RPC 框架的初始化操作（比如加载 RPC 配置文件）
    LOG_INFO("init rpc framework...");
    MprpcContext::GetInstance().Init(argc, argv);

    // 调用远程的 RPC 注册方法
    Register();
    std::cout << std::endl;

    // 调用远程的 RPC 登录方法
    Login();
    std::cout << std::endl;

    // 调用远程的 RPC 获取好友列表方法
    GetFriendList();
    std::cout << std::endl;

    // 阻塞等待一段时间，在程序结束之前，尽量让日志信息都被写入日志文件
    sleep(1);

    return 0;
}