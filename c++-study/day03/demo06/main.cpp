/**
 * 1. ��̬��Ա������ʹ��
 */

#include <iostream>

using namespace std;

class Counter {
private:
    // ������̬��Ա����
    static int num;

public :

    // ��Ա�������ʾ�̬��Ա����
    void setNum(int i) {
        num = i;
    }

    void showNum() {
        cout << num << endl;
    }
};

// ���徲̬��Ա����
int Counter::num = 0;

int main() {
    Counter a, b;
    a.showNum();
    b.showNum();
    a.setNum(10);
    a.showNum();
    b.showNum();
    return 0;
}