#include <ctime>
#include <iostream>

#include "userdao.h"

// 打印用户
void printUser(const User& user) {
    std::cout << "id: " << user.getId() << ", name: " << user.getName() << ", password: " << user.getPassword()
              << ", state: " << user.getState() << std::endl;
}

int main() {
    // 初始化随机数种子
    std::srand(std::time(nullptr));

    // 生成随机整数
    int randNum = std::rand() + std::rand();

    // 用户名称
    std::string userName = "User" + std::to_string(randNum);

    // 用户
    User user;
    user.setName(userName);
    user.setPassword("123456");
    user.setState("offline");

    UserDao userDao;

    // 插入数据
    userDao.insert(user);

    // 查询数据
    User user1 = userDao.select(user.getId());
    printUser(user1);

    // 查询数据
    User user2 = userDao.selectByName(userName);
    printUser(user2);

    // 更新数据
    user.setState("online");
    userDao.updateState(user);

    // 查询数据
    User user3 = userDao.select(user.getId());
    printUser(user3);

    return 0;
}