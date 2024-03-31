/**
 * 单例模式使用案例之二
 */

#include <iostream>
#include <string>

using namespace std;

class Printer {

private:

    // 私有的默认构造函数
    Printer() {

    }

    // 私有的拷贝造函数
    Printer(const Printer &p) {

    }

public:
    void printText(string str) {
        cout << str << endl;
        times++;
    }

    long getTimes() {
        return times;
    }

public:
    static Printer *getInstance() {
        return singleton;
    }

private:
    // 打印次数
    long times = 0;

    // 声明静态变量（单例）
    static Printer *singleton;
};

// 初始化静态变量（单例），分配内存空间
Printer *Printer::singleton = new Printer();

int main() {
    Printer *printer1 = Printer::getInstance();
    Printer *printer2 = Printer::getInstance();
    // 判断内存地址是否相同
    cout << (printer1 == printer2 ? "true" : "false") << endl;

    printer1->printText("C++ Guilde");
    printer1->printText("Think in Java");
    long times = printer1->getTimes();
    cout << "times = " << times << endl;

    return 0;
}
