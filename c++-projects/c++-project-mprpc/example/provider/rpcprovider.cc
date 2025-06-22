#include <iostream>

#include "friend.pb.h"
#include "logger.h"
#include "mprpcapplication.h"
#include "mprpcprovider.h"
#include "user.pb.h"
#include "vector"

// RPC 服务，继承基类 UserServiceRpc（由 Protobuf 自动生成）
class UserService : public user::UserServiceRpc {
public:
    // 本地的登录函数
    bool Login(std::string name, std::string password) {
        LOG_INFO("invoke local Login function, name: %s, password: %s", name.c_str(), password.c_str());
        return true;
    }

    // 本地的注册函数
    bool Register(std::string name, std::string password) {
        LOG_INFO("invoke local Register function, name: %s, password: %s", name.c_str(), password.c_str());
        return true;
    }

    // 重写基类 UserServiceRpc（由 Protobuf 自动生成）的虚函数
    void Login(::google::protobuf::RpcController* controller, const ::user::LoginRequest* request,
               ::user::LoginResponse* response, ::google::protobuf::Closure* done) override {
        // 获取 RPC 请求参数
        std::string name = request->name();
        std::string password = request->password();

        // 调用本地业务函数
        bool success = Login(name, password);

        // 设置 RPC 响应结果
        user::ResultCode* result = response->mutable_result();
        result->set_errcode(0);
        result->set_errmsg("");
        response->set_success(success);

        // 执行回调操作，返回响应结果给 RPC 服务调用者
        done->Run();
    }

    // 重写基类 UserServiceRpc（由 Protobuf 自动生成）的虚函数
    void Register(::google::protobuf::RpcController* controller, const ::user::RegisterRequest* request,
                  ::user::RegisterResponse* response, ::google::protobuf::Closure* done) override {
        // 获取 RPC 请求参数
        std::string name = request->name();
        std::string password = request->password();

        // 调用本地业务函数
        bool success = Register(name, password);

        // 设置 RPC 响应结果
        user::ResultCode* result = response->mutable_result();
        result->set_errcode(0);
        result->set_errmsg("");
        response->set_success(success);

        // 执行回调操作，返回响应结果给RPC服务调用者
        done->Run();
    }
};

// RPC 服务，继承基类 FriendServiceRpc（由 Protobuf 自动生成）
class FriendServcie : public friends::FriendServiceRpc {
    // 本地获取好友列表的函数
    std::vector<friends::Friend> GetFriendList(uint32_t userid) {
        LOG_INFO("invoke local GetFriendList function, userid: %u", userid);

        // 返回结果
        std::vector<friends::Friend> result;

        friends::Friend f1;
        f1.set_userid(1);
        f1.set_username("Jim");
        f1.set_sex(friends::Friend::MAN);
        result.push_back(f1);

        friends::Friend f2;
        f2.set_userid(2);
        f2.set_username("Tom");
        f2.set_sex(friends::Friend::MAN);
        result.push_back(f2);

        return result;
    }

    // 重写基类 FriendServiceRpc（由 Protobuf 自动生成）的虚函数
    void GetFriendList(::google::protobuf::RpcController* controller, const ::friends::GetFriendListRequest* request,
                       ::friends::GetFriendListResponse* response, ::google::protobuf::Closure* done) {
        // 获取 RPC 请求参数
        uint32_t userid = request->userid();

        // 调用本地业务函数
        std::vector<friends::Friend> friends = GetFriendList(userid);

        // 设置 RPC 响应结果
        friends::ResultCode* result = response->mutable_result();
        result->set_errcode(0);
        result->set_errmsg("");

        // 设置响应的数据
        for (friends::Friend& item : friends) {
            friends::Friend* f = response->add_friends();
            f->set_sex(item.sex());
            f->set_userid(item.userid());
            f->set_username(item.username());
        }

        // 执行回调操作，返回响应结果给RPC服务调用者
        done->Run();
    }
};

// 测试 RPC 服务的发布
int main(int argc, char** argv) {
    // 设置日志级别
    Logger::GetInstance().SetLogLevel(INFO);

    // 调用 RPC 框架的初始化操作（比如加载 RPC 配置文件）
    LOG_INFO("init rpc framework...");
    MprpcApplication::GetInstance().Init(argc, argv);

    // 创建用来发布 RPC 服务的网络对象类
    RpcProvider provider;

    // 发布 RPC 服务
    provider.PublishService(new UserService());

    // 发布 RPC 服务
    provider.PublishService(new FriendServcie());

    // 启动 RPC 服务节点，开始对外提供 RPC 远程网络调用服务（针对 RPC 服务提供者）
    provider.Run();

    return 0;
}