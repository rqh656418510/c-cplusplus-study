#include <muduo/base/Logging.h>

void outlog() {
    LOG_INFO << "这是一个 info 日志";
    LOG_WARN << "这是一个 warn 日志";
    LOG_ERROR << "这是一个 error 日志";
}