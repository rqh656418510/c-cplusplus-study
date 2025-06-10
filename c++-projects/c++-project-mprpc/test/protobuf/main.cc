#include <iostream>
#include <string>

#include "userservice.pb.h"

using namespace std;
using namespace user;

int main() {
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

    return 0;
}