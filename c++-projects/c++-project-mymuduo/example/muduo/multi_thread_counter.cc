/**
 * 基于 Muduo 官方网络库的线程池实现并行计算
 */

#include "multi_thread_counter.h"

ULong MultiThreadCounter::count(const int threadNumber, const ULong countRange) {
    // 创建并启动 Muduo 线程池
    muduo::ThreadPool pool;
    pool.setMaxQueueSize(100);
    pool.start(threadNumber);

    // 用于汇总所有线程的计算结果
    std::atomic<ULong> totalSum(0);

    // 用于等待所有任务执行完成
    muduo::CountDownLatch latch(threadNumber);

    // 将 [1, countRange] 平均分成 N 段，每段提交一个任务
    ULong blockSize = countRange / threadNumber;
    for (int i = 0; i < threadNumber; ++i) {
        ULong start = i * blockSize + 1;
        ULong end = (i == threadNumber - 1) ? countRange : (i + 1) * blockSize;

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

    // 关闭线程池
    pool.stop();

    return totalSum.load();
}