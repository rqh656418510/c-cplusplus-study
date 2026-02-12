#include "MySqlConnectionPool.h"

#include <algorithm>
#include <exception>
#include <vector>

#include "AppConfigLoader.h"
#include "Logger.h"

// 构造函数
MySqlConnectionPool::MySqlConnectionPool() : connectionCount_(0), closed_(false) {
    // 获取全局配置信息
    const AppConfig &config = AppConfigLoader::getInstance().getConfig();

    // 初始化连接池参数
    this->initSize_ = config.mysql.connectionPoolInitSize;
    this->maxSize_ = config.mysql.connectionPoolMaxSize;
    this->maxIdleTime_ = config.mysql.connectionPoolMaxIdleTime;
    this->connectionTimeout_ = config.mysql.connectionPoolConnectionTimeout;
    this->heartbeatIntervalTime_ = config.mysql.connectionPoolHeartbeatIntervalTime;
    this->scanIntervalTime_ = std::min(this->maxIdleTime_, this->heartbeatIntervalTime_);

    // 创建初始化数量的MySQL连接
    for (int i = 0; i < this->initSize_; i++) {
        MySqlConnection *connection = new MySqlConnection();
        // 连接数据库
        bool connected = connection->connect(config.mysql.ip, config.mysql.port, config.mysql.user,
                                             config.mysql.password, config.mysql.database);
        // 判断是否连接成功
        if (connected) {
            // 刷新连接进入空闲状态后的起始存活时间点
            connection->refreshIdleStartTime();
            // 入队操作
            this->connectionQueue_.push_back(connection);
            // 计数器加一
            this->connectionCount_++;
        }
    }

    // 创建生产MySQL连接的线程
    produceThread_ = std::thread(std::bind(&MySqlConnectionPool::produceConnection, this));

    // 创建扫描空闲连接的线程
    scanIdleThread_ = std::thread(std::bind(&MySqlConnectionPool::scanIdleConnection, this));

    // 打印日志信息
    LOG_INFO("Connection pool inited");
}

// 析构函数
MySqlConnectionPool::~MySqlConnectionPool() {
    if (!this->closed_) {
        // 关闭连接池，释放所有连接
        this->close();
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
    try {
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

        // 释放所有连接
        while (!(this->connectionQueue_.empty())) {
            // 获取队头的连接
            MySqlConnection *phead = this->connectionQueue_.front();
            // 出队操作
            this->connectionQueue_.pop_front();
            // 计数器减一
            this->connectionCount_--;
            // 释放连接占用的内存空间
            delete phead;
        }

        // 打印日志信息
        LOG_INFO("Connection pool stoped");
    } catch (const std::exception &e) {
        LOG_ERROR("Connection pool stop failed, exception: %s", e.what());
    } catch (...) {
        LOG_ERROR("Connection pool stop failed, unknown exception");
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
std::shared_ptr<MySqlConnection> MySqlConnectionPool::getConnection() {
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
    std::shared_ptr<MySqlConnection> sp(this->connectionQueue_.front(), [this](MySqlConnection *pconn) {
        // 获取互斥锁
        std::unique_lock<std::mutex> lock(this->queueMutex_);

        // 判断连接池是否已关闭
        if (!this->closed_) {
            // 刷新连接进入空闲状态后的起始存活时间点
            pconn->refreshIdleStartTime();
            // 入队操作（将连接归还到队列中）
            this->connectionQueue_.push_back(pconn);
            // 通知正在等待获取连接的线程
            this->cv_.notify_all();
        } else {
            // 连接池已关闭，释放连接
            delete pconn;
        }
    });

    // 出队操作
    this->connectionQueue_.pop_front();

    if (this->connectionQueue_.empty()) {
        // 如果连接队列为空，则通知生产线程生产连接
        this->cv_.notify_all();
    }

    return sp;
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

        // 获取全局配置信息
        const AppConfig &config = AppConfigLoader::getInstance().getConfig();

        // 创建数据库连接
        MySqlConnection *connection = new MySqlConnection();

        // 连接数据库
        bool connected = connection->connect(config.mysql.ip, config.mysql.port, config.mysql.user,
                                             config.mysql.password, config.mysql.database);

        // 判断是否连接成功
        if (connected) {
            // 刷新连接进入空闲状态后的起始存活时间点
            connection->refreshIdleStartTime();
            // 入队操作
            this->connectionQueue_.push_back(connection);
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

// 扫描连接池中的空闲连接
void MySqlConnectionPool::scanIdleConnection() {
    while (!this->closed_) {
        //////////////////////////////// 回收连接池中的空闲连接 ////////////////////////////////

        {
            // 打印日志信息
            LOG_DEBUG("Connection pool scan idle connection and send heartbeat");

            // 获取互斥锁
            std::unique_lock<std::mutex> lock(this->queueMutex_);

            // 使用条件变量进行可中断的定时等待，在每次被唤醒（包括虚假唤醒）时都会检查关闭标志；若检测到连接池已关闭则立即返回，以保证扫描线程能够安全退出
            if (this->cv_.wait_for(lock, std::chrono::seconds(this->scanIntervalTime_),
                                   [this]() { return this->closed_.load(); })) {
                // 当被唤醒时，说明连接池已经关闭，退出扫描线程
                break;
            }

            // wait_for() 超时返回后，如果连接池已经关闭，则退出扫描线程
            if (this->closed_) {
                break;
            }

            for (auto it = this->connectionQueue_.begin(); it != this->connectionQueue_.end();) {
                // 判断空闲连接（即队列里的连接）数量是否大于初始连接数量
                if (this->connectionQueue_.size() > this->initSize_) {
                    // 如果连接超过最大空闲时间，则回收连接
                    if ((*it)->getIdleTotalTimes() >= this->maxIdleTime_ * 1000) {
                        // 临时拷贝一份连接
                        MySqlConnection *conn = *it;
                        // 移除连接（返回下一个有效迭代器）
                        it = this->connectionQueue_.erase(it);
                        // 计数器减一
                        this->connectionCount_--;
                        // 释放连接
                        delete conn;
                    } else {
                        it++;
                    }
                } else {
                    it++;
                }
            }
        }  // 立刻释放互斥锁

        //////////////////////////////// 为连接池中的空闲连接发送心跳 ////////////////////////////////

        // 用于存放需要发送心跳的连接的集合
        std::vector<MySqlConnection *> needHeartbeatList;

        {
            // 获取互斥锁
            std::unique_lock<std::mutex> lock(this->queueMutex_);

            // 遍历队列里的所有连接（空闲连接）
            for (auto conn : this->connectionQueue_) {
                // 判断是否满足发送心跳的时间间隔
                if (conn != nullptr && conn->getLastHeartbeatIntervalTime() >= heartbeatIntervalTime_) {
                    // 保存需要发送心跳的连接
                    needHeartbeatList.push_back(conn);
                }
            }
        }  // 立刻释放互斥锁

        // 用于存放发送心跳失败的连接的集合
        std::vector<MySqlConnection *> failedHeartbeatList;

        // 遍历所有需要发送心跳的连接
        for (auto conn : needHeartbeatList) {
            // 为连接发送心跳（网络耗时操作）
            if (conn->sendHeartbeat()) {
                // 心跳发送成功，刷新连接上次发送心跳的时间戳
                conn->refreshLastHeartbeatTime();
            } else {
                // 心跳发送失败，保存发送心跳失败的连接
                failedHeartbeatList.push_back(conn);
            }
        }

        {
            // 获取互斥锁
            std::unique_lock<std::mutex> lock(this->queueMutex_);

            // 遍历所有发送心跳失败的连接
            for (auto conn : failedHeartbeatList) {
                auto it = std::find(this->connectionQueue_.begin(), this->connectionQueue_.end(), conn);
                if (it != this->connectionQueue_.end()) {
                    // 从队列中移除连接（不进行连接重连，宁可丢连接，也不要复活坏连接）
                    this->connectionQueue_.erase(it);
                    // 计数器减一
                    this->connectionCount_--;
                    // 释放连接
                    delete conn;
                }
            }
        }  // 立刻释放互斥锁
    }
}