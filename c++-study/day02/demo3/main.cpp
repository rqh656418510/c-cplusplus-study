/**
 * 1. C++�е���������
 */

#include <iostream>

using namespace std;

// �궨�庯��������
#define MAXFUNC(x, y) (x > y) ? x : y

// ��������������
inline int Max(int x, int y) {
    return (x > y) ? x : y;
}

int main() {
    // ���������ĵ���
    cout << "Max (20,10): " << Max(20, 10) << endl;
    cout << "Max (0,200): " << Max(0, 200) << endl;
    cout << "Max (100,1010): " << Max(100, 1010) << endl;

    // �궨�庯���ĵ���
    printf("Max (10,30): %d\n", MAXFUNC(10, 30));
    return 0;
}