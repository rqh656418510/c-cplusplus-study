/**
 * 1. C++�еĺ���Ĭ�ϲ�����Ϻ���ռλ����
 */

#include <iostream>

using namespace std;

void func(int a, int b, int = 0) {
    printf("a + b = %d\n", a + b);
}

int main() {
    func(1, 2);
    func(1, 2, 3);
    return 0;
}