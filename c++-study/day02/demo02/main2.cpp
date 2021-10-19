/**
 * 1. C++�е�����֮�����ã�ʹ�ñ�����ʼ�� const ���ã�
 */

#include <iostream>

using namespace std;

struct Teacher {
    char name[64];
    int age;
};

// const�����ñ���(��ָ�ڴ�ռ�)ӵ��ֻ������
void printTe(const Teacher &t) {
    // t.age = 11;   �Ǵ���д�����޷�ͨ������
}

// const ����ָ���ָ��ָ������ݣ���ôָ��ָ������ݶ����ܸ���
void printTe2(const Teacher *const pt) {
    // pt->age = 11;  �Ǵ���д�����޷�ͨ������
}

int main() {
    Teacher t1;
    t1.age = 33;
    printTe(t1);
    printTe2(&t1);
    return 0;
}