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

    auto start_time = chrono::high_resolution_clock::now();

    // 单个线程插入多条记录
    for (int i = 0; i < 1500; i++) {
        shared_ptr<MysqlConnection> connection = pool->getConnection();
        connection->executeUpdate(insertSql.c_str());
        cout << "Insert " << i << " record, current pool size: " << pool->getSize() << endl;
    }

    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> elapsed_time = end_time - start_time;
    cout << "Times: " << elapsed_time.count() << "ms" << endl;

    delete pool;
}

void testConnectionPoolMultiThread() {
    const int num_threads = 15;
    thread threads[num_threads];

    const string insertSql = "INSERT INTO `properties` (`KEY`, `VALUE`, `REMARK`) VALUES ('test_limit_price', '30.5', 'Limit Price')";
    MysqlConnectionPool *pool = MysqlConnectionPool::getInstance();

    auto start_time = chrono::high_resolution_clock::now();

    // 创建多个线程插入多条记录
    for (int i = 0; i < num_threads; i++) {
        threads[i] = thread([&, i]() {
            for (int n = 0; n < 100; n++) {
                shared_ptr<MysqlConnection> connection = pool->getConnection();
                connection->executeUpdate(insertSql.c_str());
                cout << "Thread " << i << ", current pool size: " << pool->getSize() << endl;
            }
        });
    }

    // 等待所有线程完成
    for (int i = 0; i < num_threads; ++i) {
        threads[i].join();
    }

    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> elapsed_time = end_time - start_time;
    cout << "Times: " << elapsed_time.count() << "ms" << endl;

    sleep(20);
    cout << "Pool size: " << pool->getSize() << endl;

    sleep(10);
    delete pool;
}

int main() {
    // testSqlQuery();
    // testConnectionPoolSingleThread();
    testConnectionPoolMultiThread();
    sleep(3600);
    return 0;
}
