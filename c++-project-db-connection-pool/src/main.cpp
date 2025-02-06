#include <iostream>
#include "MysqlConnection.h"
#include "MysqlConnectionPool.h"

using namespace std;

void testQuery() {
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

void testConnectionPool() {
    MysqlConnectionPool *pool = MysqlConnectionPool::getInstance();

    for (int i = 0; i < 20; i++) {
        pool->getConnection();
        cout << pool->getSize() << endl;
    }

    delete pool;
}

int main() {
    // testQuery();
    testConnectionPool();
    sleep(3600);
    return 0;
}