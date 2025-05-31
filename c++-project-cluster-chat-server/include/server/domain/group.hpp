#ifndef GROUP_H
#define GROUP_H

#include <iostream>

using namespace std;

// Group 表映射的实体类
class Group {
public:
    Group() {
    }

    Group(string groupname, string groupdesc) {
        this->groupname = groupname;
        this->groupdesc = groupdesc;
    }

    Group(int id, string groupname, string groupdesc) {
        this->id = id;
        this->groupname = groupname;
        this->groupdesc = groupdesc;
    }

    int getId() const {
        return this->id;
    }

    string getGroupName() const {
        return this->groupname;
    }

    string getGroupDesc() const {
        return this->getGroupDesc();
    }

    void setId(int id) {
        this->id = id;
    }

    void setGroupName(string groupname) {
        this->groupname = groupname;
    }

    void setGroupDesc(string groupdesc) {
        this->groupdesc = groupdesc;
    }

private:
    int id;            // 群组 ID
    string groupname;  // 群组的名称
    string groupdesc;  // 群组的描述
};

#endif  // GROUP_H