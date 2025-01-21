/**
 * 理解虚基类和虚继承
 */

#include <iostream>

using namespace std;

// 虚基类（被虚继承的类称为虚基类）
class A {

private:
    int ma;

};

// 虚继承
class B : virtual public A {

private :
    int mb;

};

int main() {
    cout << "size : " << sizeof(B) << endl;
    return 0;
}
