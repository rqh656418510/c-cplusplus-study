#include "MysqlConnection.h"

// 构造函数
MysqlConnection::MysqlConnection() {

}

// 析构函数
MysqlConnection::~MysqlConnection() {
    // 关闭数据连接
    if (this->_connection && !this->_connection->isClosed()) {
        this->_connection->close();
        LOG("# INFO: %s\n", "Closed mysql connection");
    }
}

// 用于执行任何 SQL 语句，返回一个 bool 值，表明执行该 SQL 语句是否返回了 ResultSet
// 如果执行后第一个结果是 ResultSet，则返回 true，否则返回 false
bool MysqlConnection::execute(const char *sql) {
    try {
        if (this->_connection) {
            unique_ptr<Statement> statement(this->_connection->createStatement());
            if (statement) {
                return statement->execute(sql);
            }
        }
    }
    catch (SQLException &e) {
        LOG("# ERR: SQLException in %s(%s) on line %d \n", __FILE__, __FUNCTION__, __LINE__);
        LOG("# ERR: %s\n", e.what());
    }
    return false;
}

// 用于执行 INSERT、UPDATE 或 DELETE 语句以及 SQL DDL（数据定义语言）语句，例如 CREATE TABLE 和 DROP TABLE
// 函数的返回值是一个整数，指示受影响的行数，对于 CREATE TABLE 或 DROP TABLE 等不操作行的语句，返回值总为零
int MysqlConnection::executeUpdate(const char *sql) {
    try {
        if (this->_connection) {
            unique_ptr<Statement> statement(this->_connection->createStatement());
            if (statement) {
                return statement->executeUpdate(sql);
            }
        }
    }
    catch (SQLException &e) {
        LOG("# ERR: SQLException in %s(%s) on line %d \n", __FILE__, __FUNCTION__, __LINE__);
        LOG("# ERR: %s\n", e.what());
    }
    return 0;
}

// 基于 SQL 的预编译机制，执行查询单个结果集（ResultSet）的 SQL 语句，例如 SELECT 语句
unique_ptr<ResultSet> MysqlConnection::query(const char *sql, const vector<string> parameters) {
    unique_ptr<ResultSet> resultSet = nullptr;
    try {
        if (this->_connection) {
            int index = 0;
            unique_ptr<PreparedStatement> statement(this->_connection->prepareStatement(sql));
            if (statement) {
                for (auto iterator = parameters.cbegin(); iterator != parameters.cend(); iterator++) {
                    index++;
                    statement->setString(index, (*iterator).c_str());
                }
                resultSet.reset(statement->executeQuery());
            }
        }
    }
    catch (SQLException &e) {
        LOG("# ERR: SQLException in %s(%s) on line %d \n", __FILE__, __FUNCTION__, __LINE__);
        LOG("# ERR: %s\n", e.what());
    }
    return resultSet;
}

// 连接 MySQL 数据库
bool MysqlConnection::connect(const string host, const string username, const string password, const string dbname) {
    // 初始化MySQL的连接信息
    this->_host = "tcp://" + host;
    this->_username = username;
    this->_password = password;
    this->_dbname = dbname;

    try {
        // 加载MySQL驱动
        this->_driver = get_driver_instance();
        if (!this->_driver) {
            LOG("# ERR: %s\n", "Failed to load mysql _driver");
            return false;
        }

        // 连接MySQL实例
        this->_connection = _driver->connect(this->_host.c_str(), this->_username.c_str(), this->_password.c_str());
        if (!this->_connection) {
            LOG("# ERR: %s\n", "Failed to connect mysql server");
            return false;
        } else {
            // 设置默认数据库
            this->_connection->setSchema(this->_dbname.c_str());
            LOG("# INFO: %s\n", "Inited mysql connection");
            return true;
        }
    }
    catch (SQLException &e) {
        LOG("# ERR: SQLException in %s(%s) on line %d \n", __FILE__, __FUNCTION__, __LINE__);
        LOG("# ERR: %s\n", e.what());
    }
    return false;
}

// 刷新连接进入空闲状态后的起始存活时间点
void MysqlConnection::refreshAliveTime() {
    this->_aliveTime = chrono::system_clock::now();
}

// 获取连接的空闲存活时间（单位毫秒）
long MysqlConnection::getAliveTime() const {
    chrono::milliseconds active_timestamp_ms = chrono::duration_cast<chrono::milliseconds>(this->_aliveTime.time_since_epoch());
    chrono::milliseconds now_timestamp_ms = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch());
    return now_timestamp_ms.count() - active_timestamp_ms.count();
}
