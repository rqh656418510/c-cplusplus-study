#include "MySqlConnectionPool.h"

#include <exception>

#include "AppConfigLoader.h"
#include "Logger.h"

// 构造函数
MySqlConnectionPool::MySqlConnectionPool() : connectionCount_(0), closed_(false) {
    // 全局配置信息
    const AppConfig &config = AppConfigLoader::getInstance().getConfig();

    // 初始化连接池参数
    this->initSize_ = config.mysql.connectionPoolInitSize;
    this->maxSize_ = config.mysql.connectionPoolMaxSize;
    this->maxIdleTime_ = config.mysql.connectionPoolMaxIdleTime;
    this->connectionTimeout_ = config.mysql.connectionPoolConnectionTimeout;

    // 创建初始化数量的MySQL连接
    for (int i = 0; i < this->initSize_; i++) {
        MySqlConnection *connection = new MySqlConnection();
        // 连接数据库
        bool connected = connection->connect(config.mysql.ip, config.mysql.port, config.mysql.user,
                                             config.mysql.password, config.mysql.database);
        // 判断是否连接成功
        if (connected) {
            // 刷新连接进入空闲状态后的起始存活时间点
            connection->refreshAliveTime();
            // 入队操作
            this->connectionQueue_.push(connection);
            // 计数器加一
            this->connectionCount_++;
        }
    }

    // 创建生产 MySQL 连接的线程
    produceThread_ = std::thread(std::bind(&MySqlConnectionPool::produceConnection, this));

    // 创建扫描空闲连接的线程
    scanIdleThread_ = std::thread(std::bind(&MySqlConnectionPool::scanIdleConnection, this));
}

// 析构函数
MySqlConnectionPool::~MySqlConnectionPool() {
    try {
        // 关闭连接池，释放所有连接
        this->close();
    } catch (...) {
        // 析构函数禁止抛异常
        LOG_ERROR("Failed to destroy connection pool");
    }
}

// 获取连接池单例对象
MySqlConnectionPool *MySqlConnectionPool::getInstance() {
    // 静态局部变量（线程安全）
    static MySqlConnectionPool instatnce;
    return &instatnce;
}

// 关闭连接池
void MySqlConnectionPool::close() {
    // 判断连接池是否已关闭
    if (this->closed_) {
        return;
    }

    // 设置关闭状态
    this->closed_ = true;

    // 通知所有线程连接池关闭
    cv_.notify_all();

    // 等待生产线程结束运行
    if (produceThread_.joinable()) {
        produceThread_.join();
    }

    // 等待空闲扫描线程结束运行
    if (scanIdleThread_.joinable()) {
        scanIdleThread_.join();
    }

    // 获取互斥锁
    std::unique_lock<std::mutex> lock(this->queueMutex_);

    while (!(this->connectionQueue_.empty())) {
        // 获取队头的连接
        MySqlConnection *phead = this->connectionQueue_.front();
        // 出队操作
        this->connectionQueue_.pop();
        // 计数器减一
        this->connectionCount_--;
        // 释放连接占用的内存空间
        delete phead;
    }
}

// 判断连接池是否已关闭
bool MySqlConnectionPool::isClosed() const {
    return this->closed_;
}

// 获取连接池中的连接数量
int MySqlConnectionPool::getSize() const {
    return this->connectionCount_;
}

// 从连接池中获取MySQL连接
MySqlConnectionPtr MySqlConnectionPool::getConnection() {
    // 判断连接池是否已关闭
    if (this->closed_) {
        LOG_ERROR("Connection pool has closed");
        return nullptr;
    }

    // 获取互斥锁
    std::unique_lock<std::mutex> lock(this->queueMutex_);

    // 使用While循环来避免线程虚假唤醒
    while (this->connectionQueue_.empty()) {
        // 如果连接队列为空，则等待指定的时间
        std::cv_status status = this->cv_.wait_for(lock, std::chrono::milliseconds(this->connectionTimeout_));
        if (std::cv_status::timeout == status) {
            // 如果等待超时，再次判断连接队列是否为空
            if (this->connectionQueue_.empty()) {
                LOG_ERROR("Failed to get mysql connection, queue is empty");
                return nullptr;
            }
        }
    }

    // 如果连接池已经关闭，则直接返回
    if (this->closed_) {
        return nullptr;
    }

    // 获取队头的连接，并返回智能指针，同时自定义智能指针释放资源的方式，将连接归还到队列中
    MySqlConnectionPtr ptr_conn(this->connectionQueue_.front(), [this](MySqlConnection *pconn) {
        // 获取互斥锁
        std::unique_lock<std::mutex> lock(this->queueMutex_);

        // 判断连接池是否已关闭
        if (!this->closed_) {
            // 刷新连接进入空闲状态后的起始存活时间点
            pconn->refreshAliveTime();
            // 入队操作（将连接归还到队列中）
            this->connectionQueue_.push(pconn);
            // 通知正在等待获取连接的线程
            this->cv_.notify_all();
        } else {
            // 连接池已关闭，释放连接
            delete pconn;
        }
    });

    // 出队操作
    this->connectionQueue_.pop();

    if (this->connectionQueue_.empty()) {
        // 如果连接队列为空，则通知生产线程生产连接
        this->cv_.notify_all();
    }

    return ptr_conn;
}

// 生产MySQL连接
void MySqlConnectionPool::produceConnection() {
    while (!this->closed_) {
        // 获取互斥锁
        std::unique_lock<std::mutex> lock(this->queueMutex_);

        // 使用While循环来避免线程虚假唤醒
        while (!this->closed_ && (!this->connectionQueue_.empty() || this->connectionCount_ >= this->maxSize_)) {
            // 如果队列中有空闲连接，或者连接数量达到上限，生产者线程进入等待状态
            this->cv_.wait(lock);
        }

        // 如果连接池已经关闭，则退出生产线程
        if (this->closed_) {
            break;
        }

        // 全局配置信息
        const AppConfig &config = AppConfigLoader::getInstance().getConfig();

        // 创建数据库连接
        MySqlConnection *connection = new MySqlConnection();

        // 连接数据库
        bool connected = connection->connect(config.mysql.ip, config.mysql.port, config.mysql.user,
                                             config.mysql.password, config.mysql.database);

        // 判断是否连接成功
        if (connected) {
            // 刷新连接进入空闲状态后的起始存活时间点
            connection->refreshAliveTime();
            // 入队操作
            this->connectionQueue_.push(connection);
            // 计数器加一
            this->connectionCount_++;
            // 通知消费者线程可以消费连接了
            this->cv_.notify_all();
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
void MySqlConnectionPool::scanIdleConnection() {
    while (!this->closed_) {
        // 获取互斥锁
        std::unique_lock<std::mutex> lock(this->queueMutex_);

        // 使用条件变量进行可中断的定时等待，在每次被唤醒（包括虚假唤醒）时都会检查关闭标志；若检测到连接池已关闭则立即返回，以保证扫描线程能够安全退出
        if (this->cv_.wait_for(lock, std::chrono::seconds(this->maxIdleTime_),
                               [this]() { return this->closed_.load(); })) {
            // 当被唤醒时，说明连接池已经关闭，退出扫描线程
            break;
        }

        // wait_for() 超时返回后，如果连接池已经关闭，则退出扫描线程
        if (this->closed_) {
            break;
        }

        // 判断空闲连接数量是否大于初始连接数量
        while (!this->connectionQueue_.empty() && this->connectionQueue_.size() > this->initSize_) {
            // 扫描队头的连接是否超过最大空闲时间
            MySqlConnection *phead = this->connectionQueue_.front();
            if (phead->getAliveTime() >= this->maxIdleTime_ * 1000) {
                // 出队操作
                this->connectionQueue_.pop();
                // 计数器减一
                this->connectionCount_--;
                // 释放连接
                delete phead;
            } else {
                // 如果队头的连接没有超过最大空闲时间，那么其他连接肯定也没有超过
                break;
            }
        }
    }
}