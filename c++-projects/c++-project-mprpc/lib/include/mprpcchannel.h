#pragma once

#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>
#include <google/protobuf/service.h>

class MprpcChannel : public google::protobuf::RpcChannel {
public:
    // 随机生成一个整数，范围 [0, range-1]
    int randomInt(int range);

    // 统一实现 RPC 方法调用的数据序列化和网络数据发送（针对 RPC 服务调用者）
    void CallMethod(const google::protobuf::MethodDescriptor* method, google::protobuf::RpcController* controller,
                    const google::protobuf::Message* request, google::protobuf::Message* response,
                    google::protobuf::Closure* done);
};