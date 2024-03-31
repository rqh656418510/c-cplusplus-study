/**
 * 单例模式使用案例之一
 */

#include <iostream>

using namespace std;

class ChairMan {

private:
    // 私有的默认构造函数
    ChairMan() {
        cout << "创建主席" << endl;
    }

    // 私有的拷贝造函数
    ChairMan(const ChairMan &c) {

    }

public:
    // 获取单例
    static ChairMan *getInstance() {
        return singleton;
    }

private:
    // 声明静态变量（单例）
    static ChairMan *singleton;

};

// 初始化静态变量（单例），分配内存空间
ChairMan *ChairMan::singleton = new ChairMan();

void test01() {
    ChairMan *man1 = ChairMan::getInstance();
    ChairMan *man2 = ChairMan::getInstance();
    // 判断内存地址是否相同
    cout << (man1 == man2 ? "true" : "false") << endl;
}

int main() {
    cout << "---- main ----" << endl;
    test01();
    return 0;
}
