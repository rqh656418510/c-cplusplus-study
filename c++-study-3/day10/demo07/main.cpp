/**
 * 建议用make_shared代替shared_ptr
 */

#include <iostream>
#include <memory>

using namespace std;

class Test {

public:
    Test(int a) : _a(a) {
        cout << "Test(int)" << endl;
    }

private:
    int _a;

};

int main() {
    shared_ptr<int> sp1(new int(10));
    shared_ptr<Test> sp2(new Test(20));

    shared_ptr<int> sp3 = make_shared<int>(30);
    *sp3 = 40;
    cout << *sp3 << endl;

    shared_ptr<Test> sp4 = make_shared<Test>(50);

    return 0;
}