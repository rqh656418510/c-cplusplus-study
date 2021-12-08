/*
 * 1. ����ת��
*/

#include <iostream>

using namespace std;

class Tree {

};

class Animal {

public:
    virtual void cry() = 0;

};

class Dog : public Animal {

public:
    void cry() override {
        cout << "dog cry ..." << endl;
    }

    void watchHome() {
        cout << "dog watch home" << endl;
    }

};

class Cat : public Animal {

public:
    void cry() override {
        cout << "cat cry ..." << endl;
    }

    void playBall() {
        cout << "cat play ball ..." << endl;
    }

};

void playAnimal(Animal* animal) {
    animal->cry();
    // ��̬����ת����������ת��Ϊ���࣬����ʱ�������ͼ��
    Dog* dog = dynamic_cast<Dog*>(animal);
    if (dog != NULL) {
        dog->watchHome();
    }
    Cat* cat = dynamic_cast<Cat*>(animal);
    if (cat != NULL) {
        cat->playBall();
    }
}

void printBuf(const char* buf) {
    // const_cast ȥ�������� const ֻ������
    char* m_buf = const_cast<char*>(buf);
    m_buf[0] = 'b';
    cout << buf << endl;
    cout << m_buf << endl;
}

void printBuf2() {
    // ����ָ��ָ��һ������������ĳ������ڴ�ռ䲻���Ը���
    char* buf = "aaaaa";
    // const_cast ȥ�������� const ֻ������
    char* m_buf = const_cast<char*>(buf);
    // ��ʱ������ָ����ָ����ڴ�ռ䣬����������Եĺ��
    m_buf[0] = 'b';
    cout << buf << endl;
    cout << m_buf << endl;
}

int main() {
    char* p1 = "hello";
    double pi = 3.1415926;

    // ��̬����ת���������ʱ�� C++ �������������ͼ��
    int num1 = static_cast<int>(pi);
    cout << "num1 = " << num1 << endl;

    // ��̬����ת�����������Ͷ���ת�������ǲ���ת��ָ�����ͣ���̬���⣩
    // int* p2 = static_cast<int*>(p1);  // ����д����C++ ����������ʧ��

    // ���½������ͣ���ͬ����֮������ǿ������ת��������ת��ָ������
    int* p2 = reinterpret_cast<int*>(p1);
    cout << "p2 = " << p2 << endl;

    // ȥ�������� const ֻ������
    char buf[] = "aaaaa";
    printBuf(buf);
    // printBuf2();

    // ��̬����ת���������������֮��ת��������ʱ�������ͼ��
    Dog dog;
    Cat cat;
    playAnimal(&dog);
    playAnimal(&cat);

    // ��̬������ʹ�ó���
    Animal* pAnimal = NULL;
    pAnimal = &dog;
    pAnimal = static_cast<Animal*>(&dog); // ����ͨ��
    pAnimal->cry();
    pAnimal = reinterpret_cast<Animal*>(&dog); // ����ͨ��
    pAnimal->cry();

    Tree tree;
    // pAnimal = static_cast<Animal*>(&tree); // ����д����C++ ����������ʧ��
    pAnimal = reinterpret_cast<Animal*>(&tree); // ����ͨ��

    return 0;
}