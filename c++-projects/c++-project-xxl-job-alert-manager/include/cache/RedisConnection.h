#pragma once

#include <hiredis/hiredis.h>

#include <map>
#include <string>
#include <vector>

#include "NonCopyable.h"

// Redis 操作类（基于 HiRedis，非线程安全）
class RedisConnection : NonCopyable {
public:
    // 初始化 Redis 连接
    RedisConnection();

    // 关闭 Redis 连接
    ~RedisConnection();

    // 连接 Redis 服务器（password 为空表示无密码登录，timeout 为连接超时毫秒数，reconnect 为断线是否允许重连）
    bool connect(const std::string& ip, int port, const std::string& password, int db = 0, int timeout = 5000,
                 bool reconnect = true);

    // 发送 PING 命令
    bool ping();

    //////////////////////////////// string 类型操作 ////////////////////////////////

    // 获取 string 类型数据（key 不存在时返回 false）
    bool get(const std::string& key, std::string& value);

    // 设置 string 类型数据
    bool set(const std::string& key, const std::string& value);

    //////////////////////////////// list 类型操作 ////////////////////////////////

    // 获取 list 类型全部元素（key 不存在时返回 false）
    bool getList(const std::string& key, std::vector<std::string>& values);

    // 获取 list 指定位置的元素（越界或 key 不存在时返回 false）
    bool lindex(const std::string& key, int index, std::string& value);

    // 获取 list 指定范围内的元素（key 不存在或区间为空时 values 为空）
    bool lrange(const std::string& key, int start, int stop, std::vector<std::string>& values);

    // 设置 list 类型数据（覆盖写入：先删除原 key，再按顺序 RPUSH）
    bool setList(const std::string& key, const std::vector<std::string>& values);

    // 将一个值插入 list 头部
    bool lpush(const std::string& key, const std::string& value);

    // 将一个或多个值插入 list 头部
    bool lpush(const std::string& key, const std::vector<std::string>& values);

    // 将一个值插入 list 尾部
    bool rpush(const std::string& key, const std::string& value);

    // 将一个或多个值插入 list 尾部
    bool rpush(const std::string& key, const std::vector<std::string>& values);

    // 移除并返回 list 头部的元素（key 不存在或列表为空时返回 false）
    bool lpop(const std::string& key, std::string& value);

    // 移除并返回 list 尾部的元素（key 不存在或列表为空时返回 false）
    bool rpop(const std::string& key, std::string& value);

    //////////////////////////////// hash 类型操作 ////////////////////////////////

    // 获取 hash 的单个字段值（字段不存在时返回 false）
    bool hget(const std::string& key, const std::string& field, std::string& value);

    // 获取 hash 的全部字段名及其值（key 不存在时 fields 为空）
    bool hgetall(const std::string& key, std::map<std::string, std::string>& fields);

    // 获取 hash 的全部字段名（key 不存在时 fields 为空）
    bool hkeys(const std::string& key, std::vector<std::string>& fields);

    // 获取 hash 的全部字段值（key 不存在时 values 为空）
    bool hvals(const std::string& key, std::vector<std::string>& values);

    // 判断 hash 字段名是否存在
    bool hexists(const std::string& key, const std::string& field);

    // 设置 hash 类型数据（覆盖写入：先删除原 key，再 HMSET）
    bool setHash(const std::string& key, const std::map<std::string, std::string>& fields);

    // 设置 hash 的单个字段
    bool hset(const std::string& key, const std::string& field, const std::string& value);

    // 同时设置 hash 的多个字段（不删除原 key）
    bool hmset(const std::string& key, const std::map<std::string, std::string>& fields);

    // 仅在字段不存在时设置 hash 字段（字段已存在时返回 false）
    bool hsetnx(const std::string& key, const std::string& field, const std::string& value);

    // 删除 hash 的一个字段
    bool hdel(const std::string& key, const std::string& field);

    // 删除 hash 的一个或多个字段
    bool hdel(const std::string& key, const std::vector<std::string>& fields);

    //////////////////////////////// set 类型操作 ////////////////////////////////

    // 获取 set 的成员数量
    bool scard(const std::string& key, long long& count);

    // 获取 set 的全部成员（key 不存在时 members 为空）
    bool smembers(const std::string& key, std::vector<std::string>& members);

    // 判断 member 是否是 set 的成员
    bool sismember(const std::string& key, const std::string& member);

    // 向 set 添加一个成员
    bool sadd(const std::string& key, const std::string& member);

    // 向 set 添加一个或多个成员
    bool sadd(const std::string& key, const std::vector<std::string>& members);

    // 从 set 移除一个成员
    bool srem(const std::string& key, const std::string& member);

    // 从 set 移除一个或多个成员
    bool srem(const std::string& key, const std::vector<std::string>& members);

    // 判断 key 是否存在（适用于 string / list / hash / set 等类型）
    bool exists(const std::string& key);

    // 删除 key（适用于 string / list / hash / set 等类型）
    bool del(const std::string& key);

private:
    redisContext* ctx_;     // 表示和 Redis Server 的一条连接（非线程安全）
    std::string ip_;        // Redis 服务器地址
    int port_;              // Redis 服务器端口
    std::string password_;  // Redis 登录密码（空表示无密码）
    int db_;                // Redis 数据库编号
    int timeout_;           // 连接超时时间（毫秒）
    bool allowReconnect_;   // 断线是否允许重连
    bool hasParams_;        // 是否已保存过连接参数（校验通过后即保存，供断线重连）

    // 判断连接是否有效
    bool isValid() const;

    // 使用已保存的连接参数重新建立连接（allowReconnect_ 为 false 时不重连）
    bool reconnect();

    // 检查命令回复是否成功（调用方负责 freeReplyObject）
    bool checkReply(redisReply* reply, const char* cmd) const;

    // 执行 Redis 命令，同一次调用最多重连一次，以下两种情况互斥：
    // (1) 发送命令前连接已失效：先重连，再发送当前命令（此时无论是否 retry 都会发送一次命令）
    // (2) 发送命令时连接看似有效、因断线发送失败：会重连。一旦重连成功，当 retry 为
    // true（读操作）时重发当前命令一次，为 false（写操作）时不重发当前命令以免重复执行
    redisReply* execFormat(bool retry, const char* format, ...);

    // 以 argv 方式执行 Redis 命令（重连规则、retry 含义同 execFormat）
    redisReply* execArgv(const std::vector<std::string>& args, bool retry);

    // 执行 “命令 + key + 多个值” 形式的 Redis 写命令（LPUSH / RPUSH / SADD / SREM / HDEL，断线不重发命令）
    bool execKeyValues(const char* cmd, const std::string& key, const std::vector<std::string>& values);

    // 将数组类型回复填充为字符串列表
    bool fillStringArray(redisReply* reply, std::vector<std::string>& values, const char* cmd) const;

    // 将 HGETALL 数组回复填充为 hash map
    bool fillHashMap(redisReply* reply, std::map<std::string, std::string>& fields, const char* cmd) const;
};