/*
 * 1. atomicԭ�Ӳ���
 * a) ������ʹ�� Atomic
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

	// ��������߳�
	vector<thread> threads;
	for (int i = 0; i < 10; i++) {
		threads.push_back(thread(threadFun));
	}
	for (auto& thad : threads) {
		thad.join();
	}

	// ���total�Ƿ���ȷ 10000*10 = 100000
	cout << "total number:" << total << endl;

	clock_t end_time = clock();
	cout << "��ʱ��" << end_time - start_time << "ms" << endl;

	return 0;
}