#pragma once

#include <google/protobuf/service.h>

#include "logger.h"

// RPC 调用的状态控制器
class MprpcController : public google::protobuf::RpcController {
public:
    MprpcController();
    void Reset();
    bool Failed() const;
    std::string ErrorText() const;
    void SetFailed(const std::string& reason);

    // 目前未实现具体的功能
    void StartCancel();
    bool IsCanceled() const;
    void NotifyOnCancel(google::protobuf::Closure* callback);

private:
    bool m_failed;          // RPC 方法执行过程中的状态
    std::string m_errText;  // RPC 方法执行过程中的错误信息
};
