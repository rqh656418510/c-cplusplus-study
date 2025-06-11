#include <iostream>
#include <string>

#include "generated/friendservice.pb.h"
#include "generated/groupservice.pb.h"
#include "generated/userservice.pb.h"

using namespace std;

// Protobuf 序列化与反序列化
void test01() {
    cout << "=============test01=============" << endl;

    user::LoginRequest req1;
    req1.set_name("jim");
    req1.set_pwd("12345");

    // C++对象序列化
    string serizlize_str;
    if (req1.SerializeToString(&serizlize_str)) {
        cout << serizlize_str.c_str() << endl;
    }

    // C++对象反序列化
    user::LoginRequest req2;
    if (req2.ParseFromString(serizlize_str)) {
        cout << "name: " << req2.name() << ", pwd: " << req2.pwd() << endl;
    }
}

// Protobuf 列表的使用
void test02() {
    cout << "=============test02=============" << endl;

    friends::GetFriendListResponse resp;

    // 设置 ResultCode
    friends::ResultCode *res = resp.mutable_result();
    res->set_errormsg("success");
    res->set_errorno(200);
    res->set_result(true);

    // 往列表添加元素
    friends::User *user1 = resp.add_friendlist();
    user1->set_sex(friends::User::MAN);
    user1->set_name("jim");
    user1->set_id(1);

    // 往列表添加元素
    friends::User *user2 = resp.add_friendlist();
    user2->set_sex(friends::User::MAN);
    user2->set_name("tom");
    user2->set_id(2);

    // 获取列表的大小
    cout << "friend list size: " << resp.friendlist_size() << endl;

    // C++ 对象序列化
    string serialize_str;
    if (!resp.SerializeToString(&serialize_str)) {
        cerr << "protobuf list serialize failed" << endl;
    }
}

// Protobuf 列表的使用
void test03() {
    cout << "=============test03=============" << endl;
    group::GetGroupResponse resp;

    // 设置 ResultCode
    group::ResultCode *result = resp.mutable_result();
    result->set_errormsg("server error");
    result->set_errorno(500);
    result->set_result(false);

    // 设置 Group
    group::Group *group = resp.mutable_group();
    group->set_id(1001);
    group->set_groupname("AI Team");
    group->set_groupdesc("A group for AI");

    // 插入 map 中的 User
    group::User user1;
    user1.set_id(1);
    user1.set_name("Jim");
    user1.set_sex(group::User::MAN);

    // 插入 map 中的 User
    group::User user2;
    user2.set_id(2);
    user2.set_name("Tom");
    user2.set_sex(group::User::MAN);

    // 向 map 添加成员（注意：这里使用的是指针引用）
    (*group->mutable_users())[user1.id()] = user1;
    (*group->mutable_users())[user2.id()] = user2;

    // 获取 map 的大小
    cout << "group user map size: " << resp.group().users().size() << endl;

    // C++ 对象序列化

    string serialize_str;
    if (!resp.SerializeToString(&serialize_str)) {
        cerr << "protobuf map serialize failed" << endl;
    }
}

int main() {
    test01();
    test02();
    test03();
    return 0;
}