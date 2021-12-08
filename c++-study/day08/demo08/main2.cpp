/*
 * 1. atomic原子操作
 * a) 不加锁使用 Atomic
*/

#include <iostream>
#include <ctime>
#include <mutex>
#include <vector>
#include <thread>

using namespace std;

atomic<size_t> total(0);

void threadFun()
{
	for (int i = 0; i < 1000000; i++) {
		total++;
	}
}

int main(void)
{
	clock_t start_time = clock();

	// 启动多个线程
	vector<thread> threads;
	for (int i = 0; i < 10; i++) {
		threads.push_back(thread(threadFun));
	}
	for (auto& thad : threads) {
		thad.join();
	}

	// 检测total是否正确 10000*10 = 100000
	cout << "total number:" << total << endl;

	clock_t end_time = clock();
	cout << "耗时：" << end_time - start_time << "ms" << endl;

	return 0;
}