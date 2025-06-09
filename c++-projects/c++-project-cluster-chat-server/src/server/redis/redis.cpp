#include "redis.hpp"

#include "config.hpp"

// 构造函数
Redis::Redis() : _publish_context(nullptr), _subcribe_context(nullptr) {
}

// 析构函数
Redis::~Redis() {
    if (_publish_context != nullptr) {
        redisFree(_publish_context);
    }

    if (_subcribe_context != nullptr) {
        redisFree(_subcribe_context);
    }
}

// 连接redis服务器
bool Redis::connect() {
    // 负责publish发布消息的上下文对象（即redis客户端）
    _publish_context = redisConnect(REDIS_IP.c_str(), REDIS_PORT);
    if (nullptr == _publish_context || _publish_context->err) {
        cerr << "connect redis failed!" << endl;
        if (_publish_context) {
            cerr << "connect redis error: " << _publish_context->errstr << endl;
            redisFree(_publish_context);
        }
        return false;
    }

    // 负责subscribe订阅消息的上下文对象（即redis客户端）
    _subcribe_context = redisConnect(REDIS_IP.c_str(), REDIS_PORT);
    if (nullptr == _subcribe_context || _subcribe_context->err) {
        cerr << "connect redis failed!" << endl;
        if (_subcribe_context) {
            cerr << "connect redis error: " << _subcribe_context->errstr << endl;
            redisFree(_subcribe_context);
        }
        return false;
    }

    // 在单独的线程中，监听通道上的事件，有消息就给业务层进行上报
    thread t([&]() { observer_channel_message(); });
    t.detach();

    cout << "connect redis success!" << endl;

    return true;
}

// 向redis指定的通道subscribe消息
bool Redis::subscribe(int channel) {
    // SUBSCRIBE命令本身会造成线程阻塞等待通道里面发生消息，这里只做订阅通道，不接收通道消息
    // 通道消息的接收专门在observer_channel_message()函数中的独立线程中进行
    // 这里只负责发送订阅命令，不阻塞接收Redis服务器的响应消息，否则会和notifyMsg线程抢占响应资源
    if (REDIS_ERR == redisAppendCommand(this->_subcribe_context, "SUBSCRIBE %d", channel)) {
        cerr << "subscribe command execute failed!" << endl;
        return false;
    }

    // redisBufferWrite()函数可以循环发送缓冲区中的数据，直到缓冲区数据发送完毕（done被置为1）
    int done = 0;
    while (!done) {
        if (REDIS_ERR == redisBufferWrite(this->_subcribe_context, &done)) {
            cerr << "subscribe command execute failed!" << endl;
            return false;
        }
    }

    return true;
}

// 向redis指定的通道unsubscribe消息
bool Redis::unsubscribe(int channel) {
    if (REDIS_ERR == redisAppendCommand(this->_subcribe_context, "UNSUBSCRIBE %d", channel)) {
        cerr << "unsubscribe command execute failed!" << endl;
        return false;
    }

    // redisBufferWrite()函数可以循环发送缓冲区中的数据，直到缓冲区数据发送完毕（done被置为1）
    int done = 0;
    while (!done) {
        if (REDIS_ERR == redisBufferWrite(this->_subcribe_context, &done)) {
            cerr << "unsubscribe command execute failed!" << endl;
            return false;
        }
    }

    return true;
}

// 在独立线程中异步接收订阅通道中的消息
void Redis::observer_channel_message() {
    redisReply *reply = nullptr;
    while (REDIS_OK == redisGetReply(this->_subcribe_context, (void **)&reply)) {
        // 订阅收到的消息是一个带三个元素的数组
        if (reply != nullptr && reply->element[2] != nullptr && reply->element[2]->str != nullptr) {
            // 给业务层上报通道上发生的消息
            _notify_message_handler(atoi(reply->element[1]->str), reply->element[2]->str);
        }

        // 释放资源
        freeReplyObject(reply);
    }

    cerr << ">>>>>>>>>>>>> observer_channel_message quit <<<<<<<<<<<<<" << endl;
}

// 向redis指定的通道publish消息
bool Redis::publish(int channel, string message) {
    // 发布消息
    redisReply *reply = (redisReply *)redisCommand(_publish_context, "PUBLISH %d %s", channel, message.c_str());
    if (nullptr == reply) {
        cerr << "publish command execute failed!" << endl;
        return false;
    }

    // 释放资源
    freeReplyObject(reply);
    return true;
}

// 初始化向业务层上报通道消息的回调对象
void Redis::init_notify_handler(function<void(int, string)> fn) {
    this->_notify_message_handler = fn;
}
