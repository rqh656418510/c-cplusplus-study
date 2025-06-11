#include <iostream>
#include <string>

#include "generated/friendservice.pb.h"
#include "generated/userservice.pb.h"

// 生成代码命令：protoc *.proto --cpp_out=./
// 编译代码命令：g++ *.cc -o main $(pkg-config --cflags --libs protobuf)

using namespace std;
using namespace user;
using namespace friends;

// Protobuf 序列化与反序列化
void test01() {
    cout << "=============test01=============" << endl;

    LoginRequest req1;
    req1.set_name("jim");
    req1.set_pwd("12345");

    // C++对象序列化
    string serizlize_str;
    if (req1.SerializeToString(&serizlize_str)) {
        cout << serizlize_str.c_str() << endl;
    }

    // C++对象反序列化
    LoginRequest req2;
    if (req2.ParseFromString(serizlize_str)) {
        cout << "name: " << req2.name() << ", pwd: " << req2.pwd() << endl;
    }
}

// Protobuf 列表的使用
void test02() {
    cout << "=============test02=============" << endl;

    GetFriendListResponse resp;

    // 设置类成员变量
    ResultCode *res = resp.mutable_result();
    res->set_errormsg("server error");
    res->set_errorno(500);
    res->set_result(false);

    // 往列表添加元素
    User *user1 = resp.add_friendlist();
    user1->set_sex(User::MAN);
    user1->set_name("jim");
    user1->set_id(1);

    // 往列表添加元素
    User *user2 = resp.add_friendlist();
    user2->set_sex(User::MAN);
    user2->set_name("tom");
    user2->set_id(2);

    // 获取列表的大小
    cout << "friend list size: " << resp.friendlist_size() << endl;

    // C++ 对象序列化
    string serialize_str;
    if (!resp.SerializeToString(&serialize_str)) {
        cerr << "protobuf serialize failed" << endl;
    }
}

int main() {
    test01();
    test02();
    return 0;
}