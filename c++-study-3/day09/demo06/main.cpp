/**
 * 函数调用过程中对象背后调用的方法太多
 */

#include <iostream>

using namespace std;

class Test {

public:
    Test(int a = 10) :_ma(a) {
        cout << "Test(int a)" << endl;
    }

    ~Test() {
        cout << "~Test()" << endl;
    }

    Test(const Test& t) {
        cout << "Test(const Test& t)" << endl;
        this->_ma = t._ma;
	}

    void operator=(const Test& t) {
		cout << "operator=(const Test& t)" << endl;
		this->_ma = t._ma;
    }

    int getData() {
        return this->_ma;
    }

private:
    int _ma;
};

Test getObject(Test t) {
    int value = t.getData();
    Test tmp(value);
	return tmp;
}

int main() {
    Test t1;
    Test t2;
	t2 = getObject(t1);
    return 0;
}
