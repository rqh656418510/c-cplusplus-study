#include <iostream>

#include "user.pb.h"

// RPC 服务提供者，继承基类 UserServiceRpc（由 Protobuf 自动生成）
class UserService : public user::UserServiceRpc {
public:
    // 重写基类 UserServiceRpc（由 Protobuf 自动生成）的虚函数
    void Login(::google::protobuf::RpcController* controller, const ::user::LoginRequest* request,
               ::user::LoginResponse* response, ::google::protobuf::Closure* done) override {
    }

    // 重写基类 UserServiceRpc（由 Protobuf 自动生成）的虚函数
    void Register(::google::protobuf::RpcController* controller, const ::user::RegisterRequest* request,
                  ::user::RegisterResponse* response, ::google::protobuf::Closure* done) override {
    }
};
