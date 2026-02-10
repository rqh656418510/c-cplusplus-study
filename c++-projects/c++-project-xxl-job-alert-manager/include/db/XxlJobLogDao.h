#pragma once

#include <iostream>
#include <string>

#include "NonCopyable.h"
#include "XxlJobLog.h"

// XXL-JOB任务调度日志表的操作类
class XxlJobLogDao : NonCopyable {
public:
    // 查询最新的任务调度日志记录
    XxlJobLog selectLastest();

    // 查询最新的任务调度失败日志记录
    XxlJobLog selectLastestFatal();
};