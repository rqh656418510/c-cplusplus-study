#include "RedisConnection.h"

#include <sys/time.h>

#include <cstdarg>
#include <exception>

#include "Logger.h"

// 初始化 Redis 连接
RedisConnection::RedisConnection()
    : ctx_(nullptr), port_(0), db_(0), timeout_(5000), allowReconnect_(true), hasParams_(false) {
}

// 关闭 Redis 连接
RedisConnection::~RedisConnection() {
    try {
        if (ctx_ != nullptr) {
            redisFree(ctx_);
            ctx_ = nullptr;
        }
    } catch (const std::exception& e) {
        LOG_ERROR("Failed to close redis connection, exception: %s", e.what());
    } catch (...) {
        LOG_ERROR("Failed to close redis connection, unknown exception");
    }
}

// 连接 Redis 服务器（password 为空表示无密码登录，timeout 为连接超时毫秒数，reconnect 为断线是否允许重连）
bool RedisConnection::connect(const std::string& ip, int port, const std::string& password, int db, int timeout,
                              bool reconnect) {
    if (port < 1 || port > 65535) {
        LOG_ERROR("Connect redis [%s:%d] failed, invalid port", ip.c_str(), port);
        return false;
    }
    if (timeout < 1) {
        LOG_ERROR("Connect redis [%s:%d] failed, invalid timeout: %d ms", ip.c_str(), port, timeout);
        return false;
    }

    // 保存连接参数，供断线重连使用
    ip_ = ip;
    db_ = db;
    port_ = port;
    password_ = password;
    timeout_ = timeout;
    allowReconnect_ = reconnect;
    hasParams_ = true;

    // 关闭旧连接
    if (ctx_ != nullptr) {
        redisFree(ctx_);
        ctx_ = nullptr;
    }

    // 建立连接
    struct timeval tv;
    tv.tv_sec = timeout / 1000;
    tv.tv_usec = (timeout % 1000) * 1000;
    ctx_ = redisConnectWithTimeout(ip.c_str(), port, tv);

    // 判断连接是否有效
    if (ctx_ == nullptr || ctx_->err) {
        LOG_ERROR("Connect redis [%s:%d] failed", ip.c_str(), port);
        if (ctx_ != nullptr) {
            LOG_ERROR("%s", ctx_->errstr);
            redisFree(ctx_);
            ctx_ = nullptr;
        }
        return false;
    }

    // 非空密码时执行 AUTH
    if (!password.empty()) {
        redisReply* reply = static_cast<redisReply*>(redisCommand(ctx_, "AUTH %b", password.data(), password.size()));
        if (!checkReply(reply, "AUTH")) {
            if (reply != nullptr) {
                freeReplyObject(reply);
            }
            redisFree(ctx_);
            ctx_ = nullptr;
            return false;
        }
        freeReplyObject(reply);
    }

    // 选择数据库（db 为 0 时无需 SELECT）
    if (db != 0) {
        redisReply* reply = static_cast<redisReply*>(redisCommand(ctx_, "SELECT %d", db));
        if (!checkReply(reply, "SELECT")) {
            if (reply != nullptr) {
                freeReplyObject(reply);
            }
            redisFree(ctx_);
            ctx_ = nullptr;
            return false;
        }
        freeReplyObject(reply);
    }

    LOG_DEBUG("Connect redis [%s:%d] success", ip.c_str(), port);
    return true;
}

// 发送 PING 命令
bool RedisConnection::ping() {
    redisReply* reply = execFormat(true, "PING");
    if (!checkReply(reply, "PING")) {
        if (reply != nullptr) {
            freeReplyObject(reply);
        }
        return false;
    }

    freeReplyObject(reply);
    return true;
}

// 获取 string 类型数据（key 不存在时返回 false）
bool RedisConnection::get(const std::string& key, std::string& value) {
    redisReply* reply = execFormat(true, "GET %b", key.data(), key.size());
    if (!checkReply(reply, "GET")) {
        if (reply != nullptr) {
            freeReplyObject(reply);
        }
        return false;
    }

    if (reply->type == REDIS_REPLY_NIL) {
        freeReplyObject(reply);
        return false;
    }
    if (reply->type != REDIS_REPLY_STRING) {
        LOG_ERROR("Redis GET failed, unexpected reply type: %d", reply->type);
        freeReplyObject(reply);
        return false;
    }
    if (reply->str == nullptr) {
        LOG_ERROR("Redis GET failed, null string reply");
        freeReplyObject(reply);
        return false;
    }

    value.assign(reply->str, reply->len);
    freeReplyObject(reply);
    return true;
}

// 设置 string 类型数据
bool RedisConnection::set(const std::string& key, const std::string& value) {
    redisReply* reply = execFormat(false, "SET %b %b", key.data(), key.size(), value.data(), value.size());
    if (!checkReply(reply, "SET")) {
        if (reply != nullptr) {
            freeReplyObject(reply);
        }
        return false;
    }

    freeReplyObject(reply);
    return true;
}

// 获取 list 类型全部元素（key 不存在时返回 false）
bool RedisConnection::getList(const std::string& key, std::vector<std::string>& values) {
    if (!lrange(key, 0, -1, values)) {
        return false;
    }
    // LRANGE 对不存在的 key 返回空数组
    return !values.empty();
}

// 获取 list 指定位置的元素（越界或 key 不存在时返回 false）
bool RedisConnection::lindex(const std::string& key, int index, std::string& value) {
    redisReply* reply = execFormat(true, "LINDEX %b %d", key.data(), key.size(), index);
    if (!checkReply(reply, "LINDEX")) {
        if (reply != nullptr) {
            freeReplyObject(reply);
        }
        return false;
    }

    if (reply->type == REDIS_REPLY_NIL) {
        freeReplyObject(reply);
        return false;
    }
    if (reply->type != REDIS_REPLY_STRING) {
        LOG_ERROR("Redis LINDEX failed, unexpected reply type: %d", reply->type);
        freeReplyObject(reply);
        return false;
    }
    if (reply->str == nullptr) {
        LOG_ERROR("Redis LINDEX failed, null string reply");
        freeReplyObject(reply);
        return false;
    }

    value.assign(reply->str, reply->len);
    freeReplyObject(reply);
    return true;
}

// 获取 list 指定范围内的元素（key 不存在或区间为空时 values 为空）
bool RedisConnection::lrange(const std::string& key, int start, int stop, std::vector<std::string>& values) {
    redisReply* reply = execFormat(true, "LRANGE %b %d %d", key.data(), key.size(), start, stop);
    if (!checkReply(reply, "LRANGE")) {
        if (reply != nullptr) {
            freeReplyObject(reply);
        }
        return false;
    }

    if (!fillStringArray(reply, values, "LRANGE")) {
        freeReplyObject(reply);
        return false;
    }

    freeReplyObject(reply);
    return true;
}

// 设置 list 类型数据（覆盖写入：先删除原 key，再按顺序 RPUSH）
bool RedisConnection::setList(const std::string& key, const std::vector<std::string>& values) {
    // 覆盖写入前先删除旧 key
    if (!del(key)) {
        return false;
    }

    // 空 list 在 Redis 中等价于 key 不存在，删除后即可
    if (values.empty()) {
        return true;
    }

    return rpush(key, values);
}

// 将一个值插入 list 头部
bool RedisConnection::lpush(const std::string& key, const std::string& value) {
    std::vector<std::string> values(1, value);
    return lpush(key, values);
}

// 将一个或多个值插入 list 头部
bool RedisConnection::lpush(const std::string& key, const std::vector<std::string>& values) {
    return execKeyValues("LPUSH", key, values);
}

// 将一个值插入 list 尾部
bool RedisConnection::rpush(const std::string& key, const std::string& value) {
    std::vector<std::string> values(1, value);
    return rpush(key, values);
}

// 将一个或多个值插入 list 尾部
bool RedisConnection::rpush(const std::string& key, const std::vector<std::string>& values) {
    return execKeyValues("RPUSH", key, values);
}

// 移除并返回 list 头部的元素（key 不存在或列表为空时返回 false）
bool RedisConnection::lpop(const std::string& key, std::string& value) {
    redisReply* reply = execFormat(false, "LPOP %b", key.data(), key.size());
    if (!checkReply(reply, "LPOP")) {
        if (reply != nullptr) {
            freeReplyObject(reply);
        }
        return false;
    }

    if (reply->type == REDIS_REPLY_NIL) {
        freeReplyObject(reply);
        return false;
    }
    if (reply->type != REDIS_REPLY_STRING) {
        LOG_ERROR("Redis LPOP failed, unexpected reply type: %d", reply->type);
        freeReplyObject(reply);
        return false;
    }
    if (reply->str == nullptr) {
        LOG_ERROR("Redis LPOP failed, null string reply");
        freeReplyObject(reply);
        return false;
    }

    value.assign(reply->str, reply->len);
    freeReplyObject(reply);
    return true;
}

// 移除并返回 list 尾部的元素（key 不存在或列表为空时返回 false）
bool RedisConnection::rpop(const std::string& key, std::string& value) {
    redisReply* reply = execFormat(false, "RPOP %b", key.data(), key.size());
    if (!checkReply(reply, "RPOP")) {
        if (reply != nullptr) {
            freeReplyObject(reply);
        }
        return false;
    }

    if (reply->type == REDIS_REPLY_NIL) {
        freeReplyObject(reply);
        return false;
    }
    if (reply->type != REDIS_REPLY_STRING) {
        LOG_ERROR("Redis RPOP failed, unexpected reply type: %d", reply->type);
        freeReplyObject(reply);
        return false;
    }
    if (reply->str == nullptr) {
        LOG_ERROR("Redis RPOP failed, null string reply");
        freeReplyObject(reply);
        return false;
    }

    value.assign(reply->str, reply->len);
    freeReplyObject(reply);
    return true;
}

// 获取 hash 的单个字段值（字段不存在时返回 false）
bool RedisConnection::hget(const std::string& key, const std::string& field, std::string& value) {
    redisReply* reply = execFormat(true, "HGET %b %b", key.data(), key.size(), field.data(), field.size());
    if (!checkReply(reply, "HGET")) {
        if (reply != nullptr) {
            freeReplyObject(reply);
        }
        return false;
    }

    if (reply->type == REDIS_REPLY_NIL) {
        freeReplyObject(reply);
        return false;
    }
    if (reply->type != REDIS_REPLY_STRING) {
        LOG_ERROR("Redis HGET failed, unexpected reply type: %d", reply->type);
        freeReplyObject(reply);
        return false;
    }
    if (reply->str == nullptr) {
        LOG_ERROR("Redis HGET failed, null string reply");
        freeReplyObject(reply);
        return false;
    }

    value.assign(reply->str, reply->len);
    freeReplyObject(reply);
    return true;
}

// 获取 hash 的全部字段名及其值（key 不存在时 fields 为空）
bool RedisConnection::hgetall(const std::string& key, std::map<std::string, std::string>& fields) {
    redisReply* reply = execFormat(true, "HGETALL %b", key.data(), key.size());
    if (!checkReply(reply, "HGETALL")) {
        if (reply != nullptr) {
            freeReplyObject(reply);
        }
        return false;
    }

    if (!fillHashMap(reply, fields, "HGETALL")) {
        freeReplyObject(reply);
        return false;
    }

    freeReplyObject(reply);
    return true;
}

// 获取 hash 的全部字段名（key 不存在时 fields 为空）
bool RedisConnection::hkeys(const std::string& key, std::vector<std::string>& fields) {
    redisReply* reply = execFormat(true, "HKEYS %b", key.data(), key.size());
    if (!checkReply(reply, "HKEYS")) {
        if (reply != nullptr) {
            freeReplyObject(reply);
        }
        return false;
    }

    if (!fillStringArray(reply, fields, "HKEYS")) {
        freeReplyObject(reply);
        return false;
    }

    freeReplyObject(reply);
    return true;
}

// 获取 hash 的全部字段值（key 不存在时 values 为空）
bool RedisConnection::hvals(const std::string& key, std::vector<std::string>& values) {
    redisReply* reply = execFormat(true, "HVALS %b", key.data(), key.size());
    if (!checkReply(reply, "HVALS")) {
        if (reply != nullptr) {
            freeReplyObject(reply);
        }
        return false;
    }

    if (!fillStringArray(reply, values, "HVALS")) {
        freeReplyObject(reply);
        return false;
    }

    freeReplyObject(reply);
    return true;
}

// 判断 hash 字段名是否存在
bool RedisConnection::hexists(const std::string& key, const std::string& field) {
    redisReply* reply = execFormat(true, "HEXISTS %b %b", key.data(), key.size(), field.data(), field.size());
    if (!checkReply(reply, "HEXISTS")) {
        if (reply != nullptr) {
            freeReplyObject(reply);
        }
        return false;
    }

    if (reply->type != REDIS_REPLY_INTEGER) {
        LOG_ERROR("Redis HEXISTS failed, unexpected reply type: %d", reply->type);
        freeReplyObject(reply);
        return false;
    }

    bool found = reply->integer > 0;
    freeReplyObject(reply);
    return found;
}

// 设置 hash 类型数据（覆盖写入：先删除原 key，再 HMSET）
bool RedisConnection::setHash(const std::string& key, const std::map<std::string, std::string>& fields) {
    // 覆盖写入前先删除旧 key
    if (!del(key)) {
        return false;
    }

    // 空 hash 在 Redis 中等价于 key 不存在，删除后即可
    if (fields.empty()) {
        return true;
    }

    return hmset(key, fields);
}

// 设置 hash 的单个字段
bool RedisConnection::hset(const std::string& key, const std::string& field, const std::string& value) {
    redisReply* reply = execFormat(false, "HSET %b %b %b", key.data(), key.size(), field.data(), field.size(),
                                   value.data(), value.size());
    if (!checkReply(reply, "HSET")) {
        if (reply != nullptr) {
            freeReplyObject(reply);
        }
        return false;
    }

    freeReplyObject(reply);
    return true;
}

// 同时设置 hash 的多个字段（不删除原 key）
bool RedisConnection::hmset(const std::string& key, const std::map<std::string, std::string>& fields) {
    if (fields.empty()) {
        LOG_ERROR("Redis HMSET failed, fields empty");
        return false;
    }

    std::vector<std::string> args;
    args.push_back("HMSET");
    args.push_back(key);
    for (std::map<std::string, std::string>::const_iterator it = fields.begin(); it != fields.end(); ++it) {
        args.push_back(it->first);
        args.push_back(it->second);
    }

    redisReply* reply = execArgv(args, false);
    if (!checkReply(reply, "HMSET")) {
        if (reply != nullptr) {
            freeReplyObject(reply);
        }
        return false;
    }

    freeReplyObject(reply);
    return true;
}

// 仅在字段不存在时设置 hash 字段（字段已存在时返回 false）
bool RedisConnection::hsetnx(const std::string& key, const std::string& field, const std::string& value) {
    redisReply* reply = execFormat(false, "HSETNX %b %b %b", key.data(), key.size(), field.data(), field.size(),
                                   value.data(), value.size());
    if (!checkReply(reply, "HSETNX")) {
        if (reply != nullptr) {
            freeReplyObject(reply);
        }
        return false;
    }

    if (reply->type != REDIS_REPLY_INTEGER) {
        LOG_ERROR("Redis HSETNX failed, unexpected reply type: %d", reply->type);
        freeReplyObject(reply);
        return false;
    }

    bool created = reply->integer > 0;
    freeReplyObject(reply);
    return created;
}

// 删除 hash 的一个字段
bool RedisConnection::hdel(const std::string& key, const std::string& field) {
    std::vector<std::string> fields(1, field);
    return hdel(key, fields);
}

// 删除 hash 的一个或多个字段
bool RedisConnection::hdel(const std::string& key, const std::vector<std::string>& fields) {
    return execKeyValues("HDEL", key, fields);
}

// 获取 set 的成员数量
bool RedisConnection::scard(const std::string& key, long long& count) {
    redisReply* reply = execFormat(true, "SCARD %b", key.data(), key.size());
    if (!checkReply(reply, "SCARD")) {
        if (reply != nullptr) {
            freeReplyObject(reply);
        }
        return false;
    }

    if (reply->type != REDIS_REPLY_INTEGER) {
        LOG_ERROR("Redis SCARD failed, unexpected reply type: %d", reply->type);
        freeReplyObject(reply);
        return false;
    }

    count = reply->integer;
    freeReplyObject(reply);
    return true;
}

// 获取 set 的全部成员（key 不存在时 members 为空）
bool RedisConnection::smembers(const std::string& key, std::vector<std::string>& members) {
    redisReply* reply = execFormat(true, "SMEMBERS %b", key.data(), key.size());
    if (!checkReply(reply, "SMEMBERS")) {
        if (reply != nullptr) {
            freeReplyObject(reply);
        }
        return false;
    }

    if (!fillStringArray(reply, members, "SMEMBERS")) {
        freeReplyObject(reply);
        return false;
    }

    freeReplyObject(reply);
    return true;
}

// 判断 member 是否是 set 的成员
bool RedisConnection::sismember(const std::string& key, const std::string& member) {
    redisReply* reply = execFormat(true, "SISMEMBER %b %b", key.data(), key.size(), member.data(), member.size());
    if (!checkReply(reply, "SISMEMBER")) {
        if (reply != nullptr) {
            freeReplyObject(reply);
        }
        return false;
    }

    if (reply->type != REDIS_REPLY_INTEGER) {
        LOG_ERROR("Redis SISMEMBER failed, unexpected reply type: %d", reply->type);
        freeReplyObject(reply);
        return false;
    }

    bool found = reply->integer > 0;
    freeReplyObject(reply);
    return found;
}

// 向 set 添加一个成员
bool RedisConnection::sadd(const std::string& key, const std::string& member) {
    std::vector<std::string> members(1, member);
    return sadd(key, members);
}

// 向 set 添加一个或多个成员
bool RedisConnection::sadd(const std::string& key, const std::vector<std::string>& members) {
    return execKeyValues("SADD", key, members);
}

// 从 set 移除一个成员
bool RedisConnection::srem(const std::string& key, const std::string& member) {
    std::vector<std::string> members(1, member);
    return srem(key, members);
}

// 从 set 移除一个或多个成员
bool RedisConnection::srem(const std::string& key, const std::vector<std::string>& members) {
    return execKeyValues("SREM", key, members);
}

// 判断 key 是否存在（适用于 string / list / hash / set 等类型）
bool RedisConnection::exists(const std::string& key) {
    redisReply* reply = execFormat(true, "EXISTS %b", key.data(), key.size());
    if (!checkReply(reply, "EXISTS")) {
        if (reply != nullptr) {
            freeReplyObject(reply);
        }
        return false;
    }

    if (reply->type != REDIS_REPLY_INTEGER) {
        LOG_ERROR("Redis EXISTS failed, unexpected reply type: %d", reply->type);
        freeReplyObject(reply);
        return false;
    }

    bool found = reply->integer > 0;
    freeReplyObject(reply);
    return found;
}

// 删除 key（适用于 string / list / hash / set 等类型）
bool RedisConnection::del(const std::string& key) {
    redisReply* reply = execFormat(false, "DEL %b", key.data(), key.size());
    if (!checkReply(reply, "DEL")) {
        if (reply != nullptr) {
            freeReplyObject(reply);
        }
        return false;
    }

    freeReplyObject(reply);
    return true;
}

// 判断连接是否有效
bool RedisConnection::isValid() const {
    return ctx_ != nullptr && ctx_->err == 0;
}

// 使用已保存的连接参数重新建立连接（allowReconnect_ 为 false 时不重连）
bool RedisConnection::reconnect() {
    if (!hasParams_) {
        return false;
    }
    if (!allowReconnect_) {
        LOG_WARN("Redis connection lost, reconnect disabled [%s:%d]", ip_.c_str(), port_);
        return false;
    }
    LOG_WARN("Redis connection lost, try reconnect [%s:%d]", ip_.c_str(), port_);
    return connect(ip_, port_, password_, db_, timeout_, allowReconnect_);
}

// 检查命令回复是否成功（调用方负责 freeReplyObject）
bool RedisConnection::checkReply(redisReply* reply, const char* cmd) const {
    if (reply == nullptr) {
        LOG_ERROR("Redis command [%s] failed, connection error: %s", cmd, ctx_ != nullptr ? ctx_->errstr : "null");
        return false;
    }
    if (reply->type == REDIS_REPLY_ERROR) {
        LOG_ERROR("Redis command [%s] failed: %s", cmd, reply->str != nullptr ? reply->str : "unknown");
        return false;
    }
    return true;
}

// 执行 Redis 命令，同一次调用最多重连一次，以下两种情况互斥：
// (1) 发送命令前连接已失效：先重连，再发送当前命令（此时无论是否 retry 都会发送一次命令）
// (2) 发送命令时连接看似有效、因断线发送失败：会重连。一旦重连成功，当 retry 为 true（读操作）时重发当前命令一次，为
// false（写操作）时不重发当前命令以免重复执行
redisReply* RedisConnection::execFormat(bool retry, const char* format, ...) {
    const bool alreadyInvalid = !isValid();
    if (alreadyInvalid && !reconnect()) {
        return nullptr;
    }

    va_list ap;
    va_start(ap, format);
    redisReply* reply = static_cast<redisReply*>(redisvCommand(ctx_, format, ap));
    va_end(ap);

    // 仅情况 (2)：发送前连接有效且 I/O 失败时重连；retry 为 true 时重发当前命令
    if (reply == nullptr && !alreadyInvalid && reconnect() && retry) {
        va_start(ap, format);
        reply = static_cast<redisReply*>(redisvCommand(ctx_, format, ap));
        va_end(ap);
    }
    return reply;
}

// 以 argv 方式执行 Redis 命令（重连规则、retry 含义同 execFormat）
redisReply* RedisConnection::execArgv(const std::vector<std::string>& args, bool retry) {
    if (args.empty()) {
        return nullptr;
    }

    const bool alreadyInvalid = !isValid();
    if (alreadyInvalid && !reconnect()) {
        return nullptr;
    }

    std::vector<const char*> argv;
    std::vector<size_t> argvlen;
    argv.reserve(args.size());
    argvlen.reserve(args.size());
    for (size_t i = 0; i < args.size(); ++i) {
        argv.push_back(args[i].data());
        argvlen.push_back(args[i].size());
    }

    redisReply* reply =
        static_cast<redisReply*>(redisCommandArgv(ctx_, static_cast<int>(args.size()), argv.data(), argvlen.data()));

    // 仅情况 (2)：发送前连接有效且 I/O 失败时重连；retry 为 true 时重发当前命令
    if (reply == nullptr && !alreadyInvalid && reconnect() && retry) {
        reply = static_cast<redisReply*>(
            redisCommandArgv(ctx_, static_cast<int>(args.size()), argv.data(), argvlen.data()));
    }
    return reply;
}

// 执行 “命令 + key + 多个值” 形式的 Redis 写命令（LPUSH / RPUSH / SADD / SREM / HDEL，断线不重发命令）
bool RedisConnection::execKeyValues(const char* cmd, const std::string& key, const std::vector<std::string>& values) {
    if (values.empty()) {
        LOG_ERROR("Redis %s failed, values empty", cmd);
        return false;
    }

    std::vector<std::string> args;
    args.push_back(cmd);
    args.push_back(key);
    args.insert(args.end(), values.begin(), values.end());

    redisReply* reply = execArgv(args, false);
    if (!checkReply(reply, cmd)) {
        if (reply != nullptr) {
            freeReplyObject(reply);
        }
        return false;
    }

    freeReplyObject(reply);
    return true;
}

// 将数组类型回复填充为字符串列表
bool RedisConnection::fillStringArray(redisReply* reply, std::vector<std::string>& values, const char* cmd) const {
    if (reply->type != REDIS_REPLY_ARRAY) {
        LOG_ERROR("Redis %s failed, unexpected reply type: %d", cmd, reply->type);
        return false;
    }

    values.clear();
    values.reserve(static_cast<size_t>(reply->elements));
    for (size_t i = 0; i < reply->elements; ++i) {
        redisReply* item = reply->element[i];
        if (item != nullptr && item->type == REDIS_REPLY_STRING && item->str != nullptr) {
            values.push_back(std::string(item->str, item->len));
        }
    }
    return true;
}

// 将 HGETALL 数组回复填充为 hash map
bool RedisConnection::fillHashMap(redisReply* reply, std::map<std::string, std::string>& fields,
                                  const char* cmd) const {
    if (reply->type != REDIS_REPLY_ARRAY) {
        LOG_ERROR("Redis %s failed, unexpected reply type: %d", cmd, reply->type);
        return false;
    }
    if (reply->elements % 2 != 0) {
        LOG_ERROR("Redis %s failed, odd number of elements: %d", cmd, static_cast<int>(reply->elements));
        return false;
    }

    fields.clear();
    for (size_t i = 0; i + 1 < reply->elements; i += 2) {
        redisReply* field = reply->element[i];
        redisReply* value = reply->element[i + 1];
        if (field != nullptr && value != nullptr && field->type == REDIS_REPLY_STRING &&
            value->type == REDIS_REPLY_STRING && field->str != nullptr && value->str != nullptr) {
            fields[std::string(field->str, field->len)] = std::string(value->str, value->len);
        }
    }
    return true;
}
