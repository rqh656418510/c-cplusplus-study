#include <iostream>

#include "mprpcapplication.h"
#include "rpcprovider.h"
#include "user.pb.h"

// RPC 服务提供者，继承基类 UserServiceRpc（由 Protobuf 自动生成）
class UserService : public user::UserServiceRpc {
public:
    // 本地的登录函数
    bool Login(std::string name, std::string password) {
        std::cout << "invoke local Login function" << std::endl;
        std::cout << "name: " << name << ", password: " << password << std::endl;
        return true;
    }

    // 本地的注册函数
    bool Register(std::string name, std::string password) {
        std::cout << "invoke local Register function" << std::endl;
        std::cout << "name: " << name << ", password: " << password << std::endl;
        return true;
    }

    // 重写基类 UserServiceRpc（由 Protobuf 自动生成）的虚函数
    void Login(::google::protobuf::RpcController* controller, const ::user::LoginRequest* request,
               ::user::LoginResponse* response, ::google::protobuf::Closure* done) override {
        // 获取 RPC 请求参数
        std::string name = request->name();
        std::string password = request->password();

        // 调用本地业务逻辑
        bool success = Login(name, password);

        // 设置响应结果
        user::ResultCode* result = response->mutable_result();
        result->set_errcode(0);
        result->set_errmsg("");
        response->set_success(success);

        // 执行回调操作，返回响应结果给RPC服务调用者
        done->Run();
    }

    // 重写基类 UserServiceRpc（由 Protobuf 自动生成）的虚函数
    void Register(::google::protobuf::RpcController* controller, const ::user::RegisterRequest* request,
                  ::user::RegisterResponse* response, ::google::protobuf::Closure* done) override {
        // 获取 RPC 请求参数
        std::string name = request->name();
        std::string password = request->password();

        // 调用本地业务逻辑
        bool success = Register(name, password);

        // 设置响应结果
        user::ResultCode* result = response->mutable_result();
        result->set_errcode(0);
        result->set_errmsg("");
        response->set_success(success);

        // 执行回调操作，返回响应结果给RPC服务调用者
        done->Run();
    }
};

int main(int argc, char** argv) {
    // 调用 RPC 框架的初始化操作
    MprpcApplication::Init(argc, argv);

    // 用来发布 RPC 服务的网络对象类
    RpcProvider provider;

    // 发布 RPC 服务
    // provider.NotifyService(new UserService());

    // 启动 RPC 服务节点，开始对外提供 RPC 远程网络调用服务
    // provider.Run();

    return 0;
}