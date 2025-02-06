#include <iostream>
#include "MysqlConnection.h"
#include "MysqlConnectionPool.h"

using namespace std;

void testSqlQuery() {
    MysqlConnection *connection = new MysqlConnection();
    connection->connect("192.168.56.112:3307", "root", "123456", "cxx_study");

    const string querySql = "select * from properties where `KEY` = ?";
    unique_ptr<ResultSet> result = connection->query(querySql.c_str(), {"test_limit_number"});
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

void testConnectionPoolSingleThread() {
    const string insertSql = "INSERT INTO `properties` (`KEY`, `VALUE`, `REMARK`) VALUES ('test_limit_price', '30.5', 'Limit Price')";
    MysqlConnectionPool *pool = MysqlConnectionPool::getInstance();

    clock_t startTime = clock();

    // 单个线程插入多条记录
    for (int i = 0; i < 1000; i++) {
        shared_ptr<MysqlConnection> connection = pool->getConnection();
        connection->executeUpdate(insertSql.c_str());
        cout << "Insert " << i << " record, pool size: " << pool->getSize() << endl;
    }

    clock_t endTime = clock();
    cout << "Times : " << endTime - startTime << "ms" << endl;

    delete pool;
}

void testConnectionPoolMultiThread() {
    const int num_threads = 10;
    thread threads[num_threads];

    const string insertSql = "INSERT INTO `properties` (`KEY`, `VALUE`, `REMARK`) VALUES ('test_limit_price', '30.5', 'Limit Price')";
    MysqlConnectionPool *pool = MysqlConnectionPool::getInstance();

    clock_t startTime = clock();

    // 创建多个线程插入多条记录
    for (int i = 0; i < num_threads; i++) {
        threads[i] = thread([&, i]() {
            for (int n = 0; n < 100; n++) {
                shared_ptr<MysqlConnection> connection = pool->getConnection();
                connection->executeUpdate(insertSql.c_str());
                cout << "Thread " << i << ", pool size: " << pool->getSize() << endl;
            }
        });
    }

    // 等待所有线程完成
    for (int i = 0; i < num_threads; ++i) {
        threads[i].join();
    }

    clock_t endTime = clock();
    cout << "Times : " << endTime - startTime << "ms" << endl;

    delete pool;
}

int main() {
    // testSqlQuery();
    // testConnectionPoolSingleThread();
    testConnectionPoolMultiThread();
    sleep(3600);
    return 0;
}
