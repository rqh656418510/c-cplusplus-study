/**
 * 继承中的对象模型
 *
 * <p> 在 Visual Studio 开发人员命令提示窗口内，可以使用以下命令可以查看派生类的详细信息，其中的 `xxx` 是 C++ 源文件的名称
 * <p> cl /d1 reportSingleClassLayout xxx.cpp
 */
#include <iostream>

using namespace std;

class Base {

public:
    int m_A;

protected:
    int m_B;

private:
    int m_C;

};

class Son : public Base {

public:
    int m_D;

};

int main() {
    cout << sizeof(Base) << endl;
    return 0;
}
