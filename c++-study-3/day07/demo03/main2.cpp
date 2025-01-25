/**
 * 有序关联容器
 *
 * <p> set 容器的使用（存储自定义类型）
 */

#include <iostream>
#include <set>
#include <string>

using namespace std;

// 自定义数据类型
class Student {

public:
    Student(long id, string name) : _id(id), _name(name) {

    }

    // 由于 set 容器是有序的，因此自定义类型都需要重载小于运算符，否则 set 容器将不知道如何对自定义类型进行排序
    bool operator<(const Student &other) const {
        return this->_id < other._id;
    }

    friend ostream &operator<<(ostream &out, const Student &student);

private :
    long _id;
    string _name;

};

ostream &operator<<(ostream &out, const Student &student) {
    cout << "id: " << student._id << ", name: " << student._name;
    return out;
}

int main() {
    // 存储唯一键值（不允许重复）的有序容器
    set<Student> set1;

    // 插入元素
    set1.insert(Student(1001, "Tom"));
    set1.insert(Student(1002, "Jim"));
    set1.insert(Student(1003, "Peter"));

    // 遍历容器
    for (auto it = set1.begin(); it != set1.end(); ++it) {
        cout << *it << endl;
    }

    return 0;
}
