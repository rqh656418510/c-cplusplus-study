/**
 * 1. C++ �� C ���Ե���ǿ
 */

#include <iostream>

using namespace std;

int a;

int main() {

    /************************ �������޶������ ******************************/

    float a;
    a = 3.14;
    ::a = 6;
    cout << "local variable a = " << a << endl;
    cout << "global variable a = " << ::a << endl;
    return 0;
}
