#include <iostream>
#include <string>

#include "generated/addressbook.pb.h"
#include "generated/friendservice.pb.h"
#include "generated/groupservice.pb.h"
#include "generated/userservice.pb.h"

using namespace std;

// Protobuf 序列化与反序列化
void test01() {
    cout << "=============test01=============" << endl;

    // LoginRequest 类的代码由 protoc 命令根据 .proto 文件编译生成
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

    // GetFriendListResponse 类的代码由 protoc 命令根据 .proto 文件编译生成
    friends::GetFriendListResponse resp;

    // 设置 ResultCode
    friends::ResultCode* res = resp.mutable_result();
    res->set_errormsg("success");
    res->set_errorno(200);
    res->set_result(true);

    // 往列表添加元素
    friends::User* user1 = resp.add_friendlist();
    user1->set_sex(friends::User::MAN);
    user1->set_name("jim");
    user1->set_id(1);

    // 往列表添加元素
    friends::User* user2 = resp.add_friendlist();
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

// Protobuf Map 的使用
void test03() {
    cout << "=============test03=============" << endl;

    // GetGroupResponse 类的代码由 protoc 命令根据 .proto 文件编译生成
    group::GetGroupResponse resp;

    // 设置 ResultCode
    group::ResultCode* result = resp.mutable_result();
    result->set_errormsg("server error");
    result->set_errorno(500);
    result->set_result(false);

    // 设置 Group
    group::Group* group = resp.mutable_group();
    group->set_id(1001);
    group->set_groupname("AI Team");
    group->set_groupdesc("A group for AI");

    // Map 中的 User
    group::User user1;
    user1.set_id(1);
    user1.set_name("Jim");
    user1.set_sex(group::User::MAN);

    // Map 中的 User
    group::User user2;
    user2.set_id(2);
    user2.set_name("Tom");
    user2.set_sex(group::User::MAN);

    // 向 Map 添加成员（注意：这里使用的是指针引用）
    (*group->mutable_users())[user1.id()] = user1;
    (*group->mutable_users())[user2.id()] = user2;

    // 获取 Map 的大小
    cout << "group user map size: " << resp.group().users().size() << endl;

    // C++ 对象序列化
    string serialize_str;
    if (!resp.SerializeToString(&serialize_str)) {
        cerr << "protobuf map serialize failed" << endl;
    }
}

// Protobuf 嵌套定义 Message
void test04() {
    cout << "=============test04=============" << endl;

    // AddressBook 类的代码由 protoc 命令根据 .proto 文件编译生成
    address::AddressBook addressBook;

    // 添加第一个人
    address::Person* person1 = addressBook.add_people();
    person1->set_id(1001);
    person1->set_name("jim");
    person1->set_sex(address::Person::MAN);
    person1->set_email("jim@example.com");

    // 添加第一个人的手机号码
    address::Person::PhoneNumber* phone1 = person1->add_phones();
    phone1->set_number("1234567890");
    phone1->set_type(address::Person::PHONE_TYPE_MOBILE);

    // 添加第一个人的家庭电话
    address::Person::PhoneNumber* phone2 = person1->add_phones();
    phone2->set_number("0987 - 654321");
    phone2->set_type(address::Person::PHONE_TYPE_HOME);

    // 添加第二个人
    address::Person* person2 = addressBook.add_people();
    person2->set_name("Tom");
    person2->set_id(1002);
    person2->set_email("tom@example.com");

    // 添加第二个人的手机号码
    address::Person::PhoneNumber* phone3 = person2->add_phones();
    phone3->set_number("9876543210");
    phone3->set_type(address::Person::PHONE_TYPE_MOBILE);

    // 添加第二个人的家庭电话
    address::Person::PhoneNumber* phone4 = person2->add_phones();
    phone4->set_number("0865 - 123456");
    phone4->set_type(address::Person::PHONE_TYPE_HOME);

    // C++ 对象序列化
    string serialize_str;
    if (!addressBook.SerializeToString(&serialize_str)) {
        cerr << "address book serialize failed" << endl;
    }
}

int main() {
    test01();
    test02();
    test03();
    test04();
    return 0;
}