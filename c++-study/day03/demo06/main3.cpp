/**
 * 1. ��̬��Ա������ʹ��
 */

#include <iostream>

using namespace std;

class Counter {
private:
    int num;

public:
    // ������̬��Ա����
    static int getNum(Counter *p);

    static void setNum(int i, Counter *p);
};

// ���徲̬��Ա����
int Counter::getNum(Counter *p) {
    return p->num;
}

void Counter::setNum(int i, Counter *p) {
    p->num = i;
}

int main() {
    Counter obj;

    // ���ʾ�̬��Ա�����ķ���1��ͨ������ֱ�ӷ��ʣ�
    Counter::setNum(1, &obj);
    cout << "num = " << Counter::getNum(&obj) << endl;

    // ���ʾ�̬��Ա�����ķ���2��ͨ��������ʣ�
    obj.setNum(3, &obj);
    cout << "num = " << obj.getNum(&obj) << endl;
    return 0;
}
