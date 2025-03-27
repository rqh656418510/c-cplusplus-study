/**
 * Lambda表达式的应用实践
 */

#include <iostream>
#include <memory>
#include <map>
#include <queue>
#include <functional>

using namespace std;

class Data {

public:
    Data(int a, int b) : _a(a), _b(b) {

    }

    int getA() {
        return _a;
    }

    int getB() {
        return _b;
    }

private:
    int _a;
    int _b;

};

void test01() {
    // 使用 function 存储 Lambda 表达式
    map<int, function<int(int, int)>> map;

    map[0] = [](int a, int b) -> int { return a + b; };
    map[1] = [](int a, int b) -> int { return a - b; };
    map[2] = [](int a, int b) -> int { return a * b; };
    map[3] = [](int a, int b) -> int { return a / b; };

    cout << "30 + 15 = " << map[0](30, 15) << endl;
    cout << "30 - 15 = " << map[1](30, 15) << endl;
    cout << "30 * 15 = " << map[2](30, 15) << endl;
    cout << "30 / 15 = " << map[3](30, 15) << endl;
}

void test02() {
    // 智能指针自定义删除器
    unique_ptr<FILE, function<void(FILE *)>> ptr1(fopen("data.txt", "w"), [](FILE *p) -> void {
        fclose(p);
        cout << "Closed File" << endl;
    });
}

void test03() {
    // 优先级队列自定义元素排序规则
    using FUNC = function<bool(Data &, Data &)>;
    priority_queue<Data, vector<Data>, FUNC> queue([](Data &data1, Data &data2) {
        return data1.getA() < data2.getA();
    });
    queue.push(Data(10, 20));
    queue.push(Data(18, 25));
    queue.push(Data(15, 23));
    queue.push(Data(19, 28));

    while (!queue.empty()) {
        Data data = queue.top();
        queue.pop();
        cout << "a = " << data.getA() << ", b = " << data.getB() << endl;
    }
}

int main() {
    test01();
    cout << "----------------" << endl;
    test02();
    cout << "----------------" << endl;
    test03();
    cout << "----------------" << endl;
    return 0;
}
