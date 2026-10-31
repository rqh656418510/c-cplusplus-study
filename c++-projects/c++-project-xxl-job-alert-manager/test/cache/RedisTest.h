#pragma once

#include <map>
#include <set>
#include <sys/time.h>
#include <vector>

#include "AppConfigLoader.h"
#include "Logger.h"
#include "RedisConnection.h"

// Redis 测试
class RedisTest {
public:
    // 连接 Redis 服务器（支持空密码 / 配置密码）
    void connectRedis() {
        const AppConfig& config = AppConfigLoader::getInstance().getConfig();
        RedisConnection conn;
        bool connected = conn.connect(config.redis.ip, config.redis.port, config.redis.password, config.redis.db,
                                      config.redis.connectionTimeout, config.redis.reconnect);
        if (!connected) {
            LOG_ERROR("Redis connect failed, ip: %s, port: %d", config.redis.ip.c_str(), config.redis.port);
            return;
        }
        if (!conn.ping()) {
            LOG_ERROR("Redis ping failed");
            return;
        }
        LOG_INFO("Redis connect and ping success, ip: %s, port: %d, db: %d", config.redis.ip.c_str(),
                 config.redis.port, config.redis.db);
    }

    // string 类型操作
    void stringOperations() {
        const AppConfig& config = AppConfigLoader::getInstance().getConfig();
        RedisConnection conn;
        if (!conn.connect(config.redis.ip, config.redis.port, config.redis.password, config.redis.db,
                          config.redis.connectionTimeout, config.redis.reconnect)) {
            LOG_ERROR("Redis connect failed");
            return;
        }

        const std::string key = "alert-manager:test:string";
        const std::string value = "hello-redis";

        conn.del(key);

        if (conn.exists(key)) {
            LOG_ERROR("Redis string exists should be false before SET");
            return;
        }

        if (!conn.set(key, value)) {
            LOG_ERROR("Redis string SET failed");
            return;
        }
        LOG_INFO("Redis string SET success, key: %s, value: %s", key.c_str(), value.c_str());

        if (!conn.exists(key)) {
            LOG_ERROR("Redis string EXISTS failed after SET");
            return;
        }

        std::string got;
        if (!conn.get(key, got) || got != value) {
            LOG_ERROR("Redis string GET failed, expected: %s, actual: %s", value.c_str(), got.c_str());
            return;
        }
        LOG_INFO("Redis string GET success, key: %s, value: %s", key.c_str(), got.c_str());

        if (!conn.del(key)) {
            LOG_ERROR("Redis string DEL failed");
            return;
        }
        if (conn.exists(key)) {
            LOG_ERROR("Redis string EXISTS should be false after DEL");
            return;
        }
        LOG_INFO("Redis string DEL success, key: %s", key.c_str());
    }

    // list 类型操作
    void listOperations() {
        const AppConfig& config = AppConfigLoader::getInstance().getConfig();
        RedisConnection conn;
        if (!conn.connect(config.redis.ip, config.redis.port, config.redis.password, config.redis.db,
                          config.redis.connectionTimeout, config.redis.reconnect)) {
            LOG_ERROR("Redis connect failed");
            return;
        }

        const std::string key = "alert-manager:test:list";
        std::vector<std::string> values;
        values.push_back("item-1");
        values.push_back("item-2");
        values.push_back("item-3");

        conn.del(key);

        if (conn.exists(key)) {
            LOG_ERROR("Redis list exists should be false before SET");
            return;
        }

        if (!conn.setList(key, values)) {
            LOG_ERROR("Redis list SET failed");
            return;
        }
        LOG_INFO("Redis list SET success, key: %s, size: %d", key.c_str(), static_cast<int>(values.size()));

        if (!conn.exists(key)) {
            LOG_ERROR("Redis list EXISTS failed after SET");
            return;
        }

        std::vector<std::string> got;
        if (!conn.getList(key, got) || got.size() != values.size()) {
            LOG_ERROR("Redis list GET failed, expected size: %d, actual size: %d", static_cast<int>(values.size()),
                      static_cast<int>(got.size()));
            return;
        }
        for (size_t i = 0; i < values.size(); ++i) {
            if (got[i] != values[i]) {
                LOG_ERROR("Redis list GET failed, index: %d, expected: %s, actual: %s", static_cast<int>(i),
                          values[i].c_str(), got[i].c_str());
                return;
            }
        }
        LOG_INFO("Redis list GET success, key: %s, size: %d", key.c_str(), static_cast<int>(got.size()));

        std::string indexed;
        if (!conn.lindex(key, 1, indexed) || indexed != "item-2") {
            LOG_ERROR("Redis LINDEX failed, expected: item-2, actual: %s", indexed.c_str());
            return;
        }
        LOG_INFO("Redis LINDEX success, key: %s, index: 1, value: %s", key.c_str(), indexed.c_str());

        std::vector<std::string> ranged;
        if (!conn.lrange(key, 0, 1, ranged) || ranged.size() != 2 || ranged[0] != "item-1" || ranged[1] != "item-2") {
            LOG_ERROR("Redis LRANGE failed");
            return;
        }
        LOG_INFO("Redis LRANGE success, key: %s, size: %d", key.c_str(), static_cast<int>(ranged.size()));

        if (!conn.lpush(key, "item-0")) {
            LOG_ERROR("Redis LPUSH failed");
            return;
        }
        if (!conn.rpush(key, "item-4")) {
            LOG_ERROR("Redis RPUSH failed");
            return;
        }
        std::vector<std::string> pushed;
        if (!conn.lrange(key, 0, -1, pushed) || pushed.size() != 5 || pushed[0] != "item-0" ||
            pushed[4] != "item-4") {
            LOG_ERROR("Redis LPUSH/RPUSH verify failed");
            return;
        }
        LOG_INFO("Redis LPUSH/RPUSH success, key: %s, size: %d", key.c_str(), static_cast<int>(pushed.size()));

        std::string popped;
        if (!conn.lpop(key, popped) || popped != "item-0") {
            LOG_ERROR("Redis LPOP failed, expected: item-0, actual: %s", popped.c_str());
            return;
        }
        if (!conn.rpop(key, popped) || popped != "item-4") {
            LOG_ERROR("Redis RPOP failed, expected: item-4, actual: %s", popped.c_str());
            return;
        }
        std::vector<std::string> after_pop;
        if (!conn.lrange(key, 0, -1, after_pop) || after_pop.size() != 3 || after_pop[0] != "item-1" ||
            after_pop[2] != "item-3") {
            LOG_ERROR("Redis LPOP/RPOP verify failed");
            return;
        }
        LOG_INFO("Redis LPOP/RPOP success, key: %s, size: %d", key.c_str(), static_cast<int>(after_pop.size()));

        if (!conn.del(key)) {
            LOG_ERROR("Redis list DEL failed");
            return;
        }
        if (conn.exists(key)) {
            LOG_ERROR("Redis list EXISTS should be false after DEL");
            return;
        }
        LOG_INFO("Redis list DEL success, key: %s", key.c_str());
    }

    // hash 类型操作
    void hashOperations() {
        const AppConfig& config = AppConfigLoader::getInstance().getConfig();
        RedisConnection conn;
        if (!conn.connect(config.redis.ip, config.redis.port, config.redis.password, config.redis.db,
                          config.redis.connectionTimeout, config.redis.reconnect)) {
            LOG_ERROR("Redis connect failed");
            return;
        }

        const std::string key = "alert-manager:test:hash";
        std::map<std::string, std::string> fields;
        fields["name"] = "alert-manager";
        fields["version"] = "0.0.1";
        fields["env"] = "test";

        conn.del(key);

        if (conn.exists(key)) {
            LOG_ERROR("Redis hash exists should be false before SET");
            return;
        }

        if (!conn.setHash(key, fields)) {
            LOG_ERROR("Redis hash SET failed");
            return;
        }
        LOG_INFO("Redis hash SET success, key: %s, size: %d", key.c_str(), static_cast<int>(fields.size()));

        if (!conn.exists(key)) {
            LOG_ERROR("Redis hash EXISTS failed after SET");
            return;
        }

        std::map<std::string, std::string> got;
        if (!conn.hgetall(key, got) || got.size() != fields.size()) {
            LOG_ERROR("Redis HGETALL failed, expected size: %d, actual size: %d", static_cast<int>(fields.size()),
                      static_cast<int>(got.size()));
            return;
        }
        for (std::map<std::string, std::string>::const_iterator it = fields.begin(); it != fields.end(); ++it) {
            std::map<std::string, std::string>::const_iterator got_it = got.find(it->first);
            if (got_it == got.end() || got_it->second != it->second) {
                LOG_ERROR("Redis HGETALL failed, field: %s, expected: %s, actual: %s", it->first.c_str(),
                          it->second.c_str(), got_it == got.end() ? "" : got_it->second.c_str());
                return;
            }
        }
        LOG_INFO("Redis HGETALL success, key: %s, size: %d", key.c_str(), static_cast<int>(got.size()));

        std::string field_value;
        if (!conn.hget(key, "name", field_value) || field_value != "alert-manager") {
            LOG_ERROR("Redis HGET failed, expected: alert-manager, actual: %s", field_value.c_str());
            return;
        }
        LOG_INFO("Redis HGET success, key: %s, field: name, value: %s", key.c_str(), field_value.c_str());

        if (!conn.hset(key, "status", "running")) {
            LOG_ERROR("Redis HSET failed");
            return;
        }
        if (!conn.hget(key, "status", field_value) || field_value != "running") {
            LOG_ERROR("Redis HSET verify failed");
            return;
        }
        LOG_INFO("Redis HSET success, key: %s, field: status, value: running", key.c_str());

        std::map<std::string, std::string> extra;
        extra["region"] = "cn";
        extra["owner"] = "ops";
        if (!conn.hmset(key, extra)) {
            LOG_ERROR("Redis HMSET failed");
            return;
        }
        LOG_INFO("Redis HMSET success, key: %s, extra size: %d", key.c_str(), static_cast<int>(extra.size()));

        std::map<std::string, std::string> all_fields;
        if (!conn.hgetall(key, all_fields) || all_fields.size() != 6 || all_fields["region"] != "cn") {
            LOG_ERROR("Redis HGETALL failed, size: %d", static_cast<int>(all_fields.size()));
            return;
        }
        LOG_INFO("Redis HGETALL success, key: %s, size: %d", key.c_str(), static_cast<int>(all_fields.size()));

        if (!conn.hexists(key, "name") || conn.hexists(key, "missing")) {
            LOG_ERROR("Redis HEXISTS failed");
            return;
        }
        LOG_INFO("Redis HEXISTS success, key: %s, field: name", key.c_str());

        std::vector<std::string> keys;
        if (!conn.hkeys(key, keys) || keys.size() != 6) {
            LOG_ERROR("Redis HKEYS failed, size: %d", static_cast<int>(keys.size()));
            return;
        }
        LOG_INFO("Redis HKEYS success, key: %s, size: %d", key.c_str(), static_cast<int>(keys.size()));

        std::vector<std::string> vals;
        if (!conn.hvals(key, vals) || vals.size() != 6) {
            LOG_ERROR("Redis HVALS failed, size: %d", static_cast<int>(vals.size()));
            return;
        }
        LOG_INFO("Redis HVALS success, key: %s, size: %d", key.c_str(), static_cast<int>(vals.size()));

        if (conn.hsetnx(key, "name", "other")) {
            LOG_ERROR("Redis HSETNX should fail when field exists");
            return;
        }
        if (!conn.hsetnx(key, "token", "abc")) {
            LOG_ERROR("Redis HSETNX failed for new field");
            return;
        }
        LOG_INFO("Redis HSETNX success, key: %s, field: token", key.c_str());

        std::vector<std::string> del_fields;
        del_fields.push_back("region");
        del_fields.push_back("owner");
        if (!conn.hdel(key, del_fields) || conn.hexists(key, "region")) {
            LOG_ERROR("Redis HDEL failed");
            return;
        }
        LOG_INFO("Redis HDEL success, key: %s", key.c_str());

        if (!conn.del(key)) {
            LOG_ERROR("Redis hash DEL failed");
            return;
        }
        if (conn.exists(key)) {
            LOG_ERROR("Redis hash EXISTS should be false after DEL");
            return;
        }
        LOG_INFO("Redis hash DEL success, key: %s", key.c_str());
    }

    // set 类型操作
    void setOperations() {
        const AppConfig& config = AppConfigLoader::getInstance().getConfig();
        RedisConnection conn;
        if (!conn.connect(config.redis.ip, config.redis.port, config.redis.password, config.redis.db,
                          config.redis.connectionTimeout, config.redis.reconnect)) {
            LOG_ERROR("Redis connect failed");
            return;
        }

        const std::string key = "alert-manager:test:set";
        std::vector<std::string> members;
        members.push_back("alpha");
        members.push_back("beta");
        members.push_back("gamma");

        conn.del(key);

        if (!conn.sadd(key, members)) {
            LOG_ERROR("Redis SADD failed");
            return;
        }
        LOG_INFO("Redis SADD success, key: %s, size: %d", key.c_str(), static_cast<int>(members.size()));

        long long count = 0;
        if (!conn.scard(key, count) || count != 3) {
            LOG_ERROR("Redis SCARD failed, expected: 3, actual: %lld", count);
            return;
        }
        LOG_INFO("Redis SCARD success, key: %s, count: %lld", key.c_str(), count);

        if (!conn.sismember(key, "beta") || conn.sismember(key, "delta")) {
            LOG_ERROR("Redis SISMEMBER failed");
            return;
        }
        LOG_INFO("Redis SISMEMBER success, key: %s, member: beta", key.c_str());

        std::vector<std::string> got;
        if (!conn.smembers(key, got) || got.size() != 3) {
            LOG_ERROR("Redis SMEMBERS failed, size: %d", static_cast<int>(got.size()));
            return;
        }
        std::set<std::string> got_set(got.begin(), got.end());
        if (got_set.count("alpha") == 0 || got_set.count("beta") == 0 || got_set.count("gamma") == 0) {
            LOG_ERROR("Redis SMEMBERS failed, missing member");
            return;
        }
        LOG_INFO("Redis SMEMBERS success, key: %s, size: %d", key.c_str(), static_cast<int>(got.size()));

        std::vector<std::string> removed;
        removed.push_back("alpha");
        removed.push_back("gamma");
        if (!conn.srem(key, removed)) {
            LOG_ERROR("Redis SREM failed");
            return;
        }
        if (!conn.scard(key, count) || count != 1 || conn.sismember(key, "alpha") || !conn.sismember(key, "beta")) {
            LOG_ERROR("Redis SREM verify failed, count: %lld", count);
            return;
        }
        LOG_INFO("Redis SREM success, key: %s, count: %lld", key.c_str(), count);

        if (!conn.del(key)) {
            LOG_ERROR("Redis set DEL failed");
            return;
        }
        LOG_INFO("Redis set DEL success, key: %s", key.c_str());
    }

    // 使用时发现连接断开则自动重连
    void reconnectOnUse() {
        const AppConfig& config = AppConfigLoader::getInstance().getConfig();
        RedisConnection conn;
        if (!conn.connect(config.redis.ip, config.redis.port, config.redis.password, config.redis.db,
                          config.redis.connectionTimeout, config.redis.reconnect)) {
            LOG_ERROR("Redis reconnect-on-use connect failed");
            return;
        }

        const std::string key = "alert-manager:test:reconnect";
        const std::string value = "reconnect-ok";
        if (!conn.set(key, value)) {
            LOG_ERROR("Redis reconnect-on-use SET failed");
            return;
        }

        // 另建一条连接踢掉其它客户端，模拟 RedisConnection 的连接被断开
        struct timeval tv;
        tv.tv_sec = config.redis.connectionTimeout / 1000;
        tv.tv_usec = (config.redis.connectionTimeout % 1000) * 1000;
        redisContext* admin = redisConnectWithTimeout(config.redis.ip.c_str(), config.redis.port, tv);
        if (admin == nullptr || admin->err) {
            LOG_ERROR("Redis reconnect-on-use helper connect failed");
            if (admin != nullptr) {
                redisFree(admin);
            }
            conn.del(key);
            return;
        }
        if (!config.redis.password.empty()) {
            redisReply* auth = static_cast<redisReply*>(
                redisCommand(admin, "AUTH %b", config.redis.password.data(), config.redis.password.size()));
            if (auth != nullptr) {
                freeReplyObject(auth);
            }
        }
        // 踢掉其它客户端（不包括当前 admin 连接），模拟 RedisConnection 的连接被断开
        redisReply* killReply =
            static_cast<redisReply*>(redisCommand(admin, "CLIENT KILL TYPE normal SKIPME yes"));
        if (killReply == nullptr || killReply->type == REDIS_REPLY_ERROR) {
            LOG_ERROR("Redis reconnect-on-use CLIENT KILL failed: %s",
                      killReply != nullptr && killReply->str != nullptr ? killReply->str : "null");
            if (killReply != nullptr) {
                freeReplyObject(killReply);
            }
            redisFree(admin);
            conn.del(key);
            return;
        }
        freeReplyObject(killReply);
        redisFree(admin);

        std::string got;
        if (!conn.get(key, got) || got != value) {
            LOG_ERROR("Redis reconnect-on-use GET failed, expected: %s, actual: %s", value.c_str(), got.c_str());
            conn.del(key);
            return;
        }
        if (!conn.del(key)) {
            LOG_ERROR("Redis reconnect-on-use DEL failed");
            return;
        }
        LOG_INFO("Redis reconnect-on-use success, key: %s, value: %s", key.c_str(), got.c_str());
    }
};
