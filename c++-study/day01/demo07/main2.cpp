/**
 * 1. C++�е�����֮��������������
 */

#include <iostream>

using namespace std;

struct Teacher {
    char name[64];
    int age;
};

// pT��ָ��t1��ָ�룬�����൱���޸���t1
void printfT(Teacher *pT) {
    cout << pT->age << endl;
    pT->age = 23;
}

// pT��t1�ı����������൱���޸���t1
void printfT2(Teacher & pT) {
    cout << pT.age << endl;
    pT.age = 33;
}

// pT��t1����������ͬ�ı���������ֻ���޸�pT�����������޸�t1����
void printfT3(Teacher pT) {
    cout << pT.age << endl;
    pT.age = 43;
}

int main() {
    Teacher t1;
    t1.age = 35;

    // pT��ָ��t1��ָ��
    printfT(&t1);
    printf("t1.age:%d \n", t1.age);

    // pT��t1�ı���
    printfT2(t1);
    printf("t1.age:%d \n", t1.age);

    // pT���βΣ��൱��t1����һ�����ݸ�pT ---> pT = t1
    printfT3(t1);
    printf("t1.age:%d \n", t1.age);
    return 0;
}