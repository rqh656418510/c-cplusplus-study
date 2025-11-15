/**
 * 基于 Muduo 官方网络库的线程池实现并行计算
 */

#pragma once

#include <muduo/base/CountDownLatch.h>
#include <muduo/base/ThreadPool.h>

#include <atomic>
#include <iostream>

using ULong = unsigned long long;

class MultiThreadCounter {
public:
    static ULong count(const int threadNumber, const ULong countRange);
};
