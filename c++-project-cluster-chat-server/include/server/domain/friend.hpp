#ifndef FRIEND_H
#define FRIEND_H

// Friend 表映射的实体类
class Friend {
public:
    Friend() {
    }

    Friend(int userid, int friendid) {
        this->userid = userid;
        this->friendid = friendid;
    }

    int getUserId() const {
        return this->userid;
    }

    int getFriendId() const {
        return this->friendid;
    }

    void setUserId(int userid) {
        this->userid = userid;
    }

    void setFriendId(int friendid) {
        this->friendid = friendid;
    }

private:
    int userid;    // 用户 ID
    int friendid;  // 好友的 ID
};

#endif  // FRIEND_H