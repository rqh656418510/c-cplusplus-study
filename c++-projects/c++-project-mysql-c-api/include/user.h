#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>

// User 表映射的实体类
class User {
public:
    User() {
        this->id = -1;
        this->name = "";
        this->password = "";
        this->state = "offline";
    }

    User(const std::string &name, const std::string &password) {
        this->id = -1;
        this->name = name;
        this->password = password;
        this->state = "offline";
    }

    User(int id, const std::string &name, const std::string &state) {
        this->id = id;
        this->name = name;
        this->password = "";
        this->state = state;
    }

    User(int id, const std::string &name, const std::string &password, const std::string &state) {
        this->id = id;
        this->name = name;
        this->password = password;
        this->state = state;
    }

    int getId() const {
        return this->id;
    }

    std::string getName() const {
        return this->name;
    }

    std::string getPassword() const {
        return this->password;
    }

    std::string getState() const {
        return this->state;
    }

    void setId(int id) {
        this->id = id;
    }

    void setName(const std::string &name) {
        this->name = name;
    }

    void setPassword(const std::string &password) {
        this->password = password;
    }

    void setState(const std::string &state) {
        this->state = state;
    }

private:
    int id;                // 用户 ID
    std::string name;      // 用户名称
    std::string password;  // 用户密码
    std::string state;     // 用户登录状态
};

#endif  // USER_H