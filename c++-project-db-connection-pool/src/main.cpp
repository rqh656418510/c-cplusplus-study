#include <iostream>
#include "MysqlConnection.h"

using namespace std;

void test01() {
    unique_ptr<MysqlConnection> db(new MysqlConnection());
    bool connected = db->connect("192.168.56.112:3307", "root", "123456", "edu");
    assert(connected);

    string querySql = "select * from properties where `KEY` = ?";
    unique_ptr<ResultSet> result = db->query(querySql.c_str(), {"test_limit_price"});
    if (result) {
        cout << "Query: " << querySql << endl;
        while (result->next()) {
            cout << result->getInt("ID") << " | ";
            cout << result->getString("KEY").c_str() << " | ";
            cout << result->getString("VALUE").c_str() << " | ";
            cout << result->getString("REMARK").c_str() << " | ";
            cout << endl;
        }
    }
}

int main() {
    test01();
    return 0;
}