#include "MysqlConnectionPool.h"

#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

// 私有构造函数
MysqlConnectionPool::MysqlConnectionPool() : _connectionCount(0), _closed(false) {
    // 加载配置文件
    if (!loadConfigFile()) {
        LOG("# ERR: %s\n", "Failed to load config file mysql.ini");
        return;
    }

    // 创建初始化数量的 MySQL 连接
    for (int i = 0; i < this->_initSize; i++) {
        MysqlConnection *connection = new MysqlConnection();
        // 连接数据库
        bool connected = connection->connect(this->_host, this->_username, this->_password, this->_dbname);
        // 判断是否连接成功
        if (connected) {
            // 刷新连接进入空闲状态后的起始存活时间点
            connection->refreshAliveTime();
            // 入队操作
            this->_connectionQueue.push(connection);
            // 计数器加一
            this->_connectionCount++;
        }
    }

    // 创建生产 MySQL 连接的线程
    _produceThread = thread(bind(&MysqlConnectionPool::produceConnection, this));

    // 创建扫描空闲连接的线程
    _scanIdleThread = thread(bind(&MysqlConnectionPool::scanIdleConnection, this));
}

// 私有析构函数
MysqlConnectionPool::~MysqlConnectionPool() {
    try {
        // 关闭连接池，释放所有连接
        this->close();
    } catch (...) {
        // 析构函数禁止抛异常
        LOG("# ERR: %s\n", "Failed to destroy connection pool");
    }
}

// 获取连接池单例对象
MysqlConnectionPool *MysqlConnectionPool::getInstance() {
    // 静态局部变量（线程安全）
    static MysqlConnectionPool instatnce;
    return &instatnce;
}

// 加载配置文件
bool MysqlConnectionPool::loadConfigFile() {
    // 配置文件的路径
    fs::path configPath = fs::current_path().concat("/mysql.ini");

    // 读取配置文件
    FILE *file = fopen(configPath.c_str(), "r");
    if (file == nullptr) {
        LOG("# ERR: %s %s\n", configPath.c_str(), "file is not exist");
        return false;
    }

    LOG("======== mysql.ini ========\n")
    while (!feof(file)) {
        char buffer[1024] = {0};
        fgets(buffer, 1024, file);
        string line = buffer;

        // 配置格式：username=root
        int index = line.find('=', 0);

        // 无效配置项
        if (index == -1) {
            continue;
        }

        int endIndex = line.find('\n', index);

        // 处理配置项
        string key = line.substr(0, index);
        string value = line.substr(index + 1, endIndex - index - 1);
        if (key == "host") {
            this->_host = value;
        } else if (key == "username") {
            this->_username = value;
        } else if (key == "password") {
            this->_password = value;
        } else if (key == "dbname") {
            this->_dbname = value;
        } else if (key == "initSize") {
            this->_initSize = stoi(value);
        } else if (key == "maxSize") {
            this->_maxSize = stoi(value);
        } else if (key == "maxIdleTime") {
            this->_maxIdleTime = stoi(value);
        } else if (key == "connectionTimeout") {
            this->_connectionTimeout = stoi(value);
        }
        LOG("%s=%s\n", key.c_str(), value.c_str());
    }
    LOG("======== mysql.ini ========\n\n")

    fclose(file);

    return true;
}

// 关闭连接池
void MysqlConnectionPool::close() {
    // 判断连接池是否已关闭
    if (this->_closed) {
        return;
    }

    // 设置关闭状态
    this->_closed = true;

    // 通知所有线程连接池关闭
    _cv.notify_all();

    // 等待生产线程结束运行
    if (_produceThread.joinable()) {
        _produceThread.join();
    }

    // 等待空闲扫描线程结束运行
    if (_scanIdleThread.joinable()) {
        _scanIdleThread.join();
    }

    // 获取互斥锁
    unique_lock<mutex> lock(this->_queueMutex);

    while (!(this->_connectionQueue.empty())) {
        // 获取队头的连接
        MysqlConnection *phead = this->_connectionQueue.front();
        // 出队操作
        this->_connectionQueue.pop();
        // 计数器减一
        this->_connectionCount--;
        // 释放连接占用的内存空间
        delete phead;
    }
}

// 判断连接池是否已关闭
bool MysqlConnectionPool::isClosed() const {
    return this->_closed;
}

// 获取连接池中的连接数量
int MysqlConnectionPool::getSize() const {
    return this->_connectionCount;
}

// 获取 MySQL 连接
MysqlConnectionPtr MysqlConnectionPool::getConnection() {
    // 判断连接池是否已关闭
    if (this->_closed) {
        LOG("# ERR: %s\n", "Connection pool has closed");
        return nullptr;
    }

    // 获取互斥锁
    unique_lock<mutex> lock(this->_queueMutex);

    // 使用 While 循环来避免线程虚假唤醒
    while (this->_connectionQueue.empty()) {
        // 如果连接队列为空，则等待指定的时间
        cv_status status = this->_cv.wait_for(lock, chrono::milliseconds(this->_connectionTimeout));
        if (cv_status::timeout == status) {
            // 如果等待超时，再次判断连接队列是否为空
            if (this->_connectionQueue.empty()) {
                LOG("# ERR: %s\n", "Failed to get mysql connection, queue is empty");
                return nullptr;
            }
        }
    }

    // 如果连接池已经关闭，则直接返回
    if (this->_closed) {
        return nullptr;
    }

    // 获取队头的连接，并返回智能指针，同时自定义智能指针释放资源的方式，将连接归还到队列中
    MysqlConnectionPtr ptr_conn(this->_connectionQueue.front(), [this](MysqlConnection *pconn) {
        // 获取互斥锁
        std::unique_lock<std::mutex> lock(this->_queueMutex);

        // 判断连接池是否已关闭
        if (!this->_closed) {
            // 刷新连接进入空闲状态后的起始存活时间点
            pconn->refreshAliveTime();
            // 入队操作（将连接归还到队列中）
            this->_connectionQueue.push(pconn);
            // 通知正在等待获取连接的线程
            this->_cv.notify_all();
        } else {
            // 连接池已关闭，释放连接
            delete pconn;
        }
    });

    // 出队操作
    this->_connectionQueue.pop();

    if (this->_connectionQueue.empty()) {
        // 如果连接队列为空，则通知生产线程生产连接
        this->_cv.notify_all();
    }

    return ptr_conn;
}

// 生产 MySQL 连接
void MysqlConnectionPool::produceConnection() {
    while (!this->_closed) {
        // 获取互斥锁
        unique_lock<mutex> lock(this->_queueMutex);

        // 使用While循环来避免线程虚假唤醒
        while (!this->_closed && (!this->_connectionQueue.empty() || this->_connectionCount >= this->_maxSize)) {
            // 如果队列中有空闲连接，或者连接数量达到上限，生产者线程进入等待状态
            this->_cv.wait(lock);
        }

        // 如果连接池已经关闭，则退出生产线程
        if (this->_closed) {
            break;
        }

        // 创建数据库连接
        MysqlConnection *connection = new MysqlConnection();

        // 连接数据库
        bool connected = connection->connect(this->_host, this->_username, this->_password, this->_dbname);

        // 判断是否连接成功
        if (connected) {
            // 刷新连接进入空闲状态后的起始存活时间点
            connection->refreshAliveTime();
            // 入队操作
            this->_connectionQueue.push(connection);
            // 计数器加一
            this->_connectionCount++;
            // 通知消费者线程可以消费连接了
            this->_cv.notify_all();
        } else {
            // 连接失败后，释放连接
            delete connection;
            // 连接失败后，解锁再休眠，避免阻塞其他线程
            lock.unlock();
            // 连接失败后，休眠一会避免循环过快
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
}

// 扫描多余的空闲连接，并释放连接
void MysqlConnectionPool::scanIdleConnection() {
    while (!this->_closed) {

        // 获取互斥锁
        unique_lock<mutex> lock(this->_queueMutex);

        // 使用条件变量进行可中断的定时等待，在每次被唤醒（包括虚假唤醒）时都会检查关闭标志；若检测到连接池已关闭则立即返回，以保证扫描线程能够安全退出
        if (this->_cv.wait_for(lock, std::chrono::seconds(this->_maxIdleTime), [this]() { return this->_closed.load(); })) {
            // 当被唤醒且连接池已经关闭时，退出扫描线程
            break;
        }

        // wait_for() 超时返回后，如果连接池已经关闭，则退出扫描线程
        if (this->_closed) {
            break;
        }

        // 判断当前的连接总数量是否大于初始连接数量
        while (this->_connectionCount > this->_initSize) {
            // 扫描队头的连接是否超过最大空闲时间
            MysqlConnection *phead = this->_connectionQueue.front();
            if (phead->getAliveTime() >= this->_maxIdleTime * 1000) {
                // 出队操作
                this->_connectionQueue.pop();
                // 计数器减一
                this->_connectionCount--;
                // 释放连接
                delete phead;
            } else {
                // 如果队头的连接没有超过最大空闲时间，那么其他连接肯定也没有超过
                break;
            }
        }

        // 唤醒生产者线程，可以创建新连接
        this->_cv.notify_one();
    }
}