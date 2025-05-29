#ifndef OFFLINEMESSAGE_H
#define OFFLINEMESSAGE_H

#include <iostream>

using namespace std;

// OfflineMessage 表映射的实体类
class OfflineMessage {
public:
    OfflineMessage() {
    }

    OfflineMessage(string message, long createtime) {
        this->message = message;
        this->createtime = createtime;
    }

    OfflineMessage(int userid, string message, long createtime) {
        this->userid = userid;
        this->message = message;
        this->createtime = createtime;
    }

    int getUserId() const {
        return this->userid;
    }

    string getMessage() const {
        return this->message;
    }

    long getCreateTime() const {
        return this->createtime;
    }

    void setUserId(int userId) {
        this->userid = userId;
    }

    void setMessage(string message) {
        this->message = message;
    }

    void setCreateTime(long createtime) {
        this->createtime = createtime;
    }

private:
    int userid;       // 离线消息拥有者的用户 ID
    string message;   // 离线消息的内容（存储 JSON 字符串）
    long createtime;  // 离线消息的创建时间
};

#endif  // OFFLINEMESSAGE_H