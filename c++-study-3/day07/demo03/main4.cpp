/**
 * 有序关联容器
 *
 * <p> map 容器的使用（存储自定义类型）
 */

#include <iostream>
#include <string>
#include <map>

using namespace std;

// 自定义数据类型
class Student {

public:

    // 默认构造函数
    Student() {
        this->_id = 0;
        this->_name = "";
    }

    Student(long id, string name) : _id(id), _name(name) {

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
    // 有序的键值对容器（键不允许重复）
    map<int, Student> map1;

    // 插入键值对
    map1.insert({1001, Student(1001, "Jim")});
    map1.insert({1002, Student(1002, "Peter")});
    map1.insert({1003, Student(1003, "David")});

    // 获取指定键的值，如果 key 不存在，会自动插入一个键值对 [key, Student()]
    cout << map1[1002] << endl;

    // 遍历容器
    for (auto it = map1.begin(); it != map1.end(); ++it) {
        // 获取 key 和 value
        cout << "key: " << it->first << ", value: " << it->second << endl;
    }
    cout << endl;

    return 0;
}
