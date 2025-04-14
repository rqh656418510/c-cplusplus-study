/*
 * 1. 作业 - 员工分组
 *
 * 公司今天招聘了 5 个员工，5 名员工进入公司之后，需要指派员工在哪个部门工作
 * 员工信息：姓名、工资等
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <ctime>

using namespace std;

// 部门
enum {
    RENLI, YANFA, SHEJI
};

// 员工
class Employee {

public:
    Employee(string name, int money) {
        this->name = name;
        this->money = money;
    }

    string getName() const {
        return this->name;
    }

    int getMoney() const {
        return this->money;
    }

private:
    string name;
    int money;

};

// 创建员工
void createEmployees(vector<Employee> &v) {
    string nameSpeed = "ABCDE";
    for (int i = 0; i < 5; i++) {
        string name = "员工";
        name += nameSpeed[i];
        int money = rand() % 10000 + 10000;

        Employee employee(name, money);
        v.push_back(employee);
    }
}

// 设置员工分组
void setGroup(vector<Employee> &v, multimap<int, Employee> &m) {
    for (vector<Employee>::iterator it = v.begin(); it != v.end(); it++) {
        // 随机生成部门 ID
        int departmentId = rand() % 3;
        // 将员工放入 multimap 容器中
        m.insert(make_pair(departmentId, *it));
    }
}

// 显示员工信息
void showEmployees(vector<Employee> &v) {
    cout << "全部员工信息如下：" << endl;
    for (vector<Employee>::iterator it = v.begin(); it != v.end(); it++) {
        cout << "姓名: " << it->getName() << ", 工资: " << it->getMoney() << endl;
    }
    cout << "------------------------" << endl;
}

// 显示员工分组信息
void showGroup(multimap<int, Employee> &g) {
    cout << "人力部门的员工信息如下：" << endl;
    multimap<int, Employee>::iterator pos = g.find(RENLI);
    int index = 0;
    int num = g.count(RENLI);
    for (; pos != g.end(), index < num; pos++, index++) {
        cout << "姓名: " << pos->second.getName() << ", 工资: " << pos->second.getMoney() << endl;
    }

    cout << "------------------------" << endl;

    cout << "研发部门的员工信息如下：" << endl;
    pos = g.find(YANFA);
    index = 0;
    num = g.count(YANFA);
    for (; pos != g.end(), index < num; pos++, index++) {
        cout << "姓名: " << pos->second.getName() << ", 工资: " << pos->second.getMoney() << endl;
    }

    cout << "------------------------" << endl;

    cout << "设计部门的员工信息如下：" << endl;
    pos = g.find(SHEJI);
    index = 0;
    num = g.count(SHEJI);
    for (; pos != g.end(), index < num; pos++, index++) {
        cout << "姓名: " << pos->second.getName() << ", 工资: " << pos->second.getMoney() << endl;
    }

}

int main() {

    // 初始化随机种子
    srand((unsigned int) time(NULL));

    vector<Employee> employees;

    // 创建员工信息
    createEmployees(employees);

    // 显示员工信息
    showEmployees(employees);

    multimap<int, Employee> group;

    // 设置员工分组
    setGroup(employees, group);

    // 显示员工分组信息
    showGroup(group);

    return 0;
}
