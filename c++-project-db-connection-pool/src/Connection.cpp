#include "public.h"
#include "Connection.h"

// 构造函数
MySQL::MySQL(const string host, const string username, const string password, const string database) {

    // 初始化MySQL的连接信息
    this->host = host;
    this->username = username;
    this->password = password;
    this->database = database;

    try {
        // 加载MySQL驱动
        this->driver = get_driver_instance();
        if (!this->driver) {
            throw "failed to load mysql driver";
        }

        // 连接MySQL实例
        this->connection.reset(driver->connect(this->host.c_str(), this->username.c_str(), this->password.c_str()));
        if (!this->connection) {
            throw "failed to connect mysql server";
        }
        else {
            // 设置默认数据库
            this->connection->setSchema(this->database.c_str());
        }
    }
    catch (SQLException& e) {
        LOG("# ERR: SQLException in %s(%s) on line %d \n", __FILE__, __FUNCTION__, __LINE__);
        LOG("# ERR: %s\n", e.what());
    };
}

// 析构函数
MySQL::~MySQL() {

}

// 用于执行任何 SQL 语句，返回一个 bool 值，表明执行该 SQL 语句是否返回了 ResultSet
// 如果执行后第一个结果是 ResultSet，则返回 true，否则返回 false
bool MySQL::Execute(const char* sql) {
    try {
        if (this->connection) {
            unique_ptr<Statement> statement = nullptr;
            statement.reset(this->connection->createStatement());
            if (statement)
            {
                return statement->execute(sql);
            }
        }
    }
    catch (SQLException& e) {
        LOG("# ERR: SQLException in %s(%s) on line %d \n", __FILE__, __FUNCTION__, __LINE__);
        LOG("# ERR: %s\n", e.what());
    }
    return false;
}

// 用于执行 INSERT、UPDATE 或 DELETE 语句以及 SQL DDL（数据定义语言）语句，例如 CREATE TABLE 和 DROP TABLE
// 函数的返回值是一个整数，指示受影响的行数，对于 CREATE TABLE 或 DROP TABLE 等不操作行的语句，返回值总为零
int MySQL::ExecuteUpdate(const char* sql) {
    try {
        if (this->connection) {
            unique_ptr<Statement> statement = nullptr;
            statement.reset(this->connection->createStatement());
            if (statement)
            {
                return statement->executeUpdate(sql);
            }
        }
    }
    catch (SQLException& e) {
        LOG("# ERR: SQLException in %s(%s) on line %d \n", __FILE__, __FUNCTION__, __LINE__);
        LOG("# ERR: %s\n", e.what());
    }
    return 0;
}

// 基于 SQL 的预编译机制，执行查询单个结果集（ResultSet）的 SQL 语句，例如 SELECT 语句
unique_ptr<ResultSet> MySQL::Query(const char* sql, const vector<string> parameters) {
    unique_ptr<ResultSet> resultSet = nullptr;
    try {
        if (this->connection) {
            int index = 0;
            unique_ptr<PreparedStatement> statement = nullptr;
            statement.reset(this->connection->prepareStatement(sql));
            if (statement) {
                for (auto iterator = parameters.cbegin(); iterator != parameters.cend(); iterator++) {
                    index++;
                    statement->setString(index, (*iterator).c_str());
                }
                resultSet.reset(statement->executeQuery());
            }
        }
    }
    catch (SQLException& e) {
        LOG("# ERR: SQLException in %s(%s) on line %d \n", __FILE__, __FUNCTION__, __LINE__);
        LOG("# ERR: %s\n", e.what());
    }
    return resultSet;
}