#include <iostream>
#include "MysqlConnection.h"
#include "MysqlConnectionPool.h"

using namespace std;

void testQuerySingleThread() {
    MysqlConnection *connection = new MysqlConnection();
    connection->connect("192.168.56.112:3307", "root", "123456", "cxx_study");

    // 单个线程查询记录
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
        MysqlConnectionPtr connection = pool->getConnection();
        connection->executeUpdate(insertSql.c_str());
        cout << "Insert " << i << " record, current pool size: " << pool->getSize() << endl;
    }

    auto end_time = chrono::high_resolution_clock::now();

    // 统计执行耗时
    chrono::duration<double, milli> elapsed_time = end_time - start_time;
    cout << "Total Times: " << elapsed_time.count() << "ms" << endl;

    delete pool;
}

void testConnectionPoolMultiThread() {
    const int num_threads = 30;
    thread threads[num_threads];

    const string insertSql = "INSERT INTO `properties` (`KEY`, `VALUE`, `REMARK`) VALUES ('test_limit_price', '30.5', 'Limit Price')";
    MysqlConnectionPool *pool = MysqlConnectionPool::getInstance();

    auto start_time = chrono::high_resolution_clock::now();

    // 多个线程插入多条记录
    for (int i = 0; i < num_threads; i++) {
        threads[i] = thread([&, i]() {
            for (int n = 0; n < 100; n++) {
                MysqlConnectionPtr connection = pool->getConnection();
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

    // 统计执行耗时
    chrono::duration<double, milli> elapsed_time = end_time - start_time;
    cout << "Total Times: " << elapsed_time.count() << "ms" << endl;

    // 等待一段时间，触发数据库连接池回收空闲连接
    cout << "Waiting to collect idle connection..." << endl;
    sleep(15);
    cout << "Pool final size: " << pool->getSize() << endl;

    delete pool;
}

int main() {
    // 不使用数据库连接池，单个线程查询记录
    // testQuerySingleThread();

    // 使用数据库连接池，单个线程插入多条记录
    // testConnectionPoolSingleThread();

    // 使用数据库连接池，多个线程插入多条记录
    testConnectionPoolMultiThread();

    // 阻塞主线程，直到用户按下任意键才结束程序
    char c = getchar();

    return 0;
}
