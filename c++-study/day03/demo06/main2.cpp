/**
 * 1. ��̬��Ա������ʹ��
 */

#include <iostream>

using namespace std;

class Counter {
public:
    int mem;             // ���г�Ա����
    static int smem;     // ���о�̬��Ա����

public :
    Counter(int num) {
        mem = num;
    }
};

// ���徲̬��Ա����
int  Counter::smem = 0;

int main() {
    Counter c(5);
    for (int i = 0; i < 5; i++) {
        // ���ʾ�̬��Ա�����ķ���1��ͨ������ֱ�ӷ��ʣ�
        Counter::smem += i;
        cout << "Counter::smem = "<< Counter::smem << endl;
    }

    // ���ʾ�̬��Ա�����ķ���2��ͨ��������ʣ�
    cout << "c.smem = " << c.smem << endl;
    return 0;
}