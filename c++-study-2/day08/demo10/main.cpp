/**
 * 异常的多态使用
 */
#include <iostream>

using namespace std;

class BaseException {

public:
    virtual void printError() {
        cout << "Base Exception" << endl;
    }

};

class NullPointerException : public BaseException {

    void printError() override {
        cout << "Null Pointer Exception" << endl;
    }

};

void doWrok() {
    throw NullPointerException();
}

int main() {
    try {
        doWrok();
    }
    catch (BaseException &e) {
        // 这里会发生多态，即父类的引用指向子类的对象
        e.printError();
    }
    return 0;
}
