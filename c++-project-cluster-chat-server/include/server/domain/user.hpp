#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>

using namespace std;

// User 表映射的实体类
class User {
public:
    User() {
        this->id = -1;
        this->name = "";
        this->password = "";
        this->state = "offline";
    }

    User(string name, string password) {
        this->id = -1;
        this->name = name;
        this->password = password;
        this->state = "offline";
    }

    User(int id, string name, string state) {
        this->id = id;
        this->name = name;
        this->password = "";
        this->state = state;
    }

    User(int id, string name, string password, string state) {
        this->id = id;
        this->name = name;
        this->password = password;
        this->state = state;
    }

    int getId() const {
        return this->id;
    }

    string getName() const {
        return this->name;
    }

    string getPassword() const {
        return this->password;
    }

    string getState() const {
        return this->state;
    }

    void setId(int id) {
        this->id = id;
    }

    void setName(string name) {
        this->name = name;
    }

    void setPassword(string password) {
        this->password = password;
    }

    void setState(string state) {
        this->state = state;
    }

private:
    int id;           // 用户 ID
    string name;      // 用户名称
    string password;  // 用户密码
    string state;     // 用户登录状态
};

#endif  // USER_H