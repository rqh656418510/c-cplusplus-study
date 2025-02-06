#include <iostream>
#include "MysqlConnection.h"

using namespace std;

void test01() {
    MysqlConnection *connection = new MysqlConnection();
    connection->connect("192.168.56.112:3307", "root", "123456", "edu");

    const string querySql = "select * from properties where `KEY` = ?";
    unique_ptr<ResultSet> result = connection->query(querySql.c_str(), {"test_limit_price"});
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

    delete connection;
}

int main() {
    test01();
    sleep(3600);
    return 0;
}