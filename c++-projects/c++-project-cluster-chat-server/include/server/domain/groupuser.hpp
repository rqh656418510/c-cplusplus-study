#ifndef GROUPUSER_H
#define GROUPUSER_H

#include <iostream>

using namespace std;

// GroupUser 表映射的实体类
class GroupUser {
public:
    GroupUser() {
        this->groupid = -1;
        this->userid = -1;
        this->grouprole = "";
    }

    GroupUser(int groupid, int userid, string grouprole) {
        this->groupid = groupid;
        this->userid = userid;
        this->grouprole = grouprole;
    }

    int getGroupId() const {
        return this->groupid;
    }

    int getUserId() const {
        return this->userid;
    }

    string getGroupRole() const {
        return this->grouprole;
    }

    void setGroupId(int groupid) {
        this->groupid = groupid;
    }

    void setUserId(int userid) {
        this->userid = userid;
    }

    void setGroupRole(string grouprole) {
        this->grouprole = grouprole;
    }

private:
    int groupid;       // 群组 ID
    int userid;        // 用户 ID
    string grouprole;  // 群组内的角色
};

#endif  // GROUPUSER_H