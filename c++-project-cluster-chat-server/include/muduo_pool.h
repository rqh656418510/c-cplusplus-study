#pragma once

#include <muduo/base/CountDownLatch.h>
#include <muduo/base/ThreadPool.h>

#include <atomic>
#include <iostream>
#include <string>

using ULong = unsigned long long;

// 使用线程池执行多个计算任务
void runSumTasks() {
    const ULong kRange = 100000000;
    const int threadNumber = 8;

    // 创建并启动 Muduo 线程池
    muduo::ThreadPool pool;
    pool.setMaxQueueSize(100);
    pool.start(threadNumber);

    // 用于汇总所有线程的计算结果
    std::atomic<ULong> totalSum(0);

    // 用于等待所有任务执行完成
    muduo::CountDownLatch latch(threadNumber);

    // 将 [1, kRange] 平均分成 N 段，每段提交一个任务
    ULong blockSize = kRange / threadNumber;
    for (int i = 0; i < threadNumber; ++i) {
        ULong start = i * blockSize + 1;
        ULong end = (i == threadNumber - 1) ? kRange : (i + 1) * blockSize;

        // 添加任务到线程池
        pool.run([start, end, &totalSum, &latch]() {
            // 执行累加计算
            ULong localSum = 0;
            for (ULong x = start; x <= end; ++x) {
                localSum += x;
            }
            // 原子地累加到总和
            totalSum.fetch_add(localSum, std::memory_order_relaxed);
            // 标记此任务完成
            latch.countDown();
        });
    }

    // 阻塞等待所有线程完成计算
    latch.wait();

    // 输出计算结果
    std::cout << "1 + 2 + ... + " << kRange << " = " << totalSum.load() << std::endl;

    // 关闭线程池
    pool.stop();
}