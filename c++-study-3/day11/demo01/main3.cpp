/**
 * function函数对象类型的应用示例
 */

#include <iostream>
#include <functional>
#include <string>
#include <map>

using namespace std;

void doShowAllBooks() {
	cout << "查看所有书籍" << endl;
};

void doBorrowBook() {
    cout << "借书" << endl;
};

void doBackBook() {
    cout << "还书" << endl;
}

void doQueryBook() {
    cout << "查询书籍" << endl;
}

void doLoginOut() {
	cout << "注销" << endl;
}

int main() {
    int choice = 0;

    map<int, function<void()>> actionMap;
	actionMap.insert({ 1, doShowAllBooks });
    actionMap.insert({ 2, doBorrowBook });
    actionMap.insert({ 3, doBackBook });
    actionMap.insert({ 4, doQueryBook });
    actionMap.insert({ 5, doLoginOut });

    for (;;) {
        cout << "\n-------------------" << endl;
        cout << "1. 查看所有书籍" << endl;
        cout << "2. 借书" << endl;
        cout << "3. 还书" << endl;
        cout << "4. 查询书籍" << endl;
        cout << "5. 注销" << endl;
        cout << "-------------------" << endl;
        cout << "请选择: ";

        // 检测输入是否合法
        if (!(cin >> choice)) {
            cout << "输入数字无效，请重新输入!" << endl;
            // 清除错误状态
            cin.clear();
			// 丢弃错误输入
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        auto it = actionMap.find(choice);
        if (it == actionMap.end()) {
            cout << "输入数字无效，请重新输入!" << endl;
            continue;
        }
        
        it->second();
    }
    return 0;
}