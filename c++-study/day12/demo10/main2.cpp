/*
 * 1. 函数对象（仿函数）结合容器使用的案例
*/

#include <iostream>
#include <set>

using namespace std;

class CStudent {
public:
    CStudent(int id, string name) {
        this->id = id;
        this->name = name;
    }

    int getId() const {
        return this->id;
    }

    string getName() const {
        return this->name;
    }

private:
    int id;
    string name;
};

// 函数对象
class StuFunctor {

public:
    // 重载 () 操作符
    bool operator()(const CStudent &stu1, const CStudent &stu2) {
        // 排序规则
        return stu1.getId() > stu2.getId();
    }

};

void printSet(set<CStudent, StuFunctor> &s) {
    // 遍历容器
    for (set<CStudent, StuFunctor>::iterator it = s.begin(); it != s.end(); it++) {
        cout << "id: " << it->getId() << ", name: " << it->getName() << endl;
    }
}

int main() {
    set<CStudent, StuFunctor> setStu;
    setStu.insert(CStudent(3, "小张"));
    setStu.insert(CStudent(1, "小李"));
    setStu.insert(CStudent(5, "小王"));
    setStu.insert(CStudent(2, "小刘"));
    printSet(setStu);
    return 0;
}
