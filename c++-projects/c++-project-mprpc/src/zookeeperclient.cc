#include "zookeeperclient.h"

/////////////////////////////////////////// ZK 客户端同步操作扩展代码 ///////////////////////////////////////////

// 同步检查 ZNode 节点是否存在的上下文结构
struct SyncExistsContext {
    sem_t sem;              // 信号量
    int rc = ZSYSTEMERROR;  // 检查结果
};

// 异步检查 ZNode 是否存在的回调
void znode_exists_completion(int rc, const struct Stat *stat, const void *data) {
    SyncExistsContext *ctx = (SyncExistsContext *)data;
    // 存储检查结果
    ctx->rc = rc;
    // 唤醒正在等待检查结果的线程
    sem_post(&ctx->sem);
}

// 同步检查 ZNode 节点是否存在
int zoo_exists_sync(zhandle_t *zh, const char *path, int watch) {
    // 上下文信息
    SyncExistsContext ctx;

    // 初始化信号量
    sem_init(&ctx.sem, 0, 0);

    // 发起 ZK 异步请求的调用
    int ret = zoo_aexists(zh, path, watch, znode_exists_completion, &ctx);

    // 这里必须判断 ZK 的异步请求调用是否正常，否则可能因为异步请求未正常发出，导致回调永不执行，最终造成线程死锁
    if (ret != ZOK) {
        // 销毁信号量
        sem_destroy(&ctx.sem);
        // ZK 的异步请求发出失败
        return ret;
    }

    // 阻塞等待检查结果
    sem_wait(&ctx.sem);

    // 销毁信号量
    sem_destroy(&ctx.sem);

    // 返回检查结果
    return ctx.rc;
}

// 同步创建 ZNode 节点的上下文结构
struct SyncCreateContext {
    sem_t sem;                 // 信号量
    int rc = ZSYSTEMERROR;     // 创建结果
    char path_buf[512] = {0};  // 用于返回实际创建的节点路径
};

// 异步创建 ZNode 节点的回调
void znode_create_completion(int rc, const char *path, const void *data) {
    // 上下文信息
    SyncCreateContext *ctx = (SyncCreateContext *)data;

    // 存储创建结果
    ctx->rc = rc;

    // 存储实际创建的节点路径
    if (ZOK == rc && path) {
        strncpy(ctx->path_buf, path, sizeof(ctx->path_buf) - 1);
    }

    // 唤醒正在等待创建结果的线程
    sem_post(&ctx->sem);
}

// 同步创建 ZNode 节点
int zoo_create_sync(zhandle_t *zh, const char *path, const char *data, int datalen, const struct ACL_vector *acl,
                    int mode, char *path_buf_out, int path_buf_out_len) {
    // 上下文信息
    SyncCreateContext ctx;

    // 初始化信号量
    sem_init(&ctx.sem, 0, 0);

    // 发起 ZK 异步请求的调用
    int ret = zoo_acreate(zh, path, data, datalen, acl, mode, znode_create_completion, &ctx);

    // 这里必须判断 ZK 的异步请求调用是否正常，否则可能因为异步请求未正常发出，导致回调永不执行，最终造成线程死锁
    if (ret != ZOK) {
        // 销毁信号量
        sem_destroy(&ctx.sem);
        // ZK 的异步请求发出失败
        return ret;
    }

    // 阻塞等待检查结果
    sem_wait(&ctx.sem);

    // 销毁信号量
    sem_destroy(&ctx.sem);

    // 返回实际创建的节点路径
    if (path_buf_out && path_buf_out_len > 0) {
        strncpy(path_buf_out, ctx.path_buf, path_buf_out_len - 1);
        path_buf_out[path_buf_out_len - 1] = '\0';
    }

    // 返回检查结果
    return ctx.rc;
}

// 同步获取 ZNode 节点数据和状态的上下文结构
struct SyncGetContext {
    sem_t sem;                    // 信号量
    int rc = ZSYSTEMERROR;        // 操作结果
    char *buf = nullptr;          // 数据缓冲区
    int buf_len = 0;              // 数据缓冲区的大小
    struct Stat *stat = nullptr;  // ZNode 节点的状态
};

// 异步获取 ZNode 节点数据和状态的回调
void znode_get_completion(int rc, const char *value, int value_len, const struct Stat *stat, const void *data) {
    // 上下文信息
    SyncGetContext *ctx = (SyncGetContext *)data;

    // 存储操作结果
    ctx->rc = rc;

    // 存储 ZNode 节点的状态
    if (rc == ZOK && stat && ctx->stat) {
        *ctx->stat = *stat;
    }

    // 存储 ZNode 节点的数据
    if (ZOK == rc && value && value_len > 0 && ctx->buf && ctx->buf_len > 0) {
        int copy_len = (value_len < ctx->buf_len - 1) ? value_len : ctx->buf_len - 1;
        memcpy(ctx->buf, value, copy_len);
        ctx->buf[copy_len] = '\0';
    }

    // 唤醒正在等待获取结果的线程
    sem_post(&ctx->sem);
}

// 同步获取 ZNode 节点的数据和状态
int zoo_get_sync(zhandle_t *zh, const char *path, int watch, char *buf_out, int buf_out_len, struct Stat *stat_out) {
    // 上下文信息
    SyncGetContext ctx;
    ctx.stat = stat_out;
    ctx.buf = buf_out;
    ctx.buf_len = buf_out_len;

    // 初始化信号量
    sem_init(&ctx.sem, 0, 0);

    // 发起 ZK 异步请求的调用
    int ret = zoo_aget(zh, path, watch, znode_get_completion, &ctx);

    // 这里必须判断 ZK 的异步请求调用是否正常，否则可能因为异步请求未正常发出，导致回调永不执行，最终造成线程死锁
    if (ret != ZOK) {
        // 销毁信号量
        sem_destroy(&ctx.sem);
        // ZK 的异步请求发出失败
        return ret;
    }

    // 阻塞等待获取结果
    sem_wait(&ctx.sem);

    // 销毁信号量
    sem_destroy(&ctx.sem);

    // 返回操作结果
    return ctx.rc;
}

// 同步获取 ZNode 子节点列表的上下文结构
struct SyncGetChildrenContext {
    sem_t sem;                          // 信号量
    int rc = ZSYSTEMERROR;              // 操作结果
    std::vector<std::string> children;  // 子节点列表
};

// 异步获取 ZNode 子节点列表的回调
void zoo_get_children_completion(int rc, const struct String_vector *strings, const void *data) {
    // 上下文信息
    SyncGetChildrenContext *ctx = (SyncGetChildrenContext *)data;

    // 存储操作结果
    ctx->rc = rc;

    // 存储子节点列表
    if (ZOK == rc && strings) {
        for (int i = 0; i < strings->count; i++) {
            ctx->children.emplace_back(strings->data[i]);
        }
    }

    // 唤醒正在等待获取结果的线程
    sem_post(&ctx->sem);
}

// 同步获取 ZNode 子节点列表
std::vector<std::string> zoo_get_children_sync(zhandle_t *zh, const char *path, int watch) {
    // 子节点列表
    std::vector<std::string> result;

    // 上下文信息
    SyncGetChildrenContext ctx;

    // 初始化信号量
    sem_init(&ctx.sem, 0, 0);

    // 发起 ZK 异步请求的调用
    int ret = zoo_aget_children(zh, path, watch, zoo_get_children_completion, &ctx);

    // 这里必须判断 ZK 的异步请求调用是否正常，否则可能因为异步请求未正常发出，导致回调永不执行，最终造成线程死锁
    if (ret != ZOK) {
        // 销毁信号量
        sem_destroy(&ctx.sem);
        // ZK 的异步请求发出失败
        return result;
    }

    // 阻塞等待获取结果
    sem_wait(&ctx.sem);

    // 销毁信号量
    sem_destroy(&ctx.sem);

    // 获取子节点列表成功
    if (ZOK == ctx.rc) {
        // 直接转移 children 所有权给 result
        result = std::move(ctx.children);
    }
    // 获取子节点列表失败
    else {
        // 打印日志信息
        LOG_ERROR("failed to get children of node %s", path);
    }

    // 返回子节点列表
    return result;
}

// 全局的 Watcher 监听器，接收 ZkServer 给 ZkClient 发送的通知
void global_watcher(zhandle_t *zh, int type, int state, const char *path, void *watcherCtx) {
    // 判断接收到的事件类型是不是会话事件类型
    if (type == ZOO_SESSION_EVENT) {
        // ZK 客户端连接成功
        if (state == ZOO_CONNECTED_STATE) {
            // 从 ZK 客户端的上下文中获取预设置的信号量
            sem_t *init_sem = (sem_t *)zoo_get_context(zh);
            // 唤醒正在等待 ZK 客户端初始化完成的线程
            sem_post(init_sem);
        }
        // ZK 客户端身份认证失败
        else if (state == ZOO_AUTH_FAILED_STATE) {
            // 打印日志信息
            LOG_ERROR("zookeeper auth failed");
        }
        // ZK 客户端会话过期
        else if (state == ZOO_EXPIRED_SESSION_STATE) {
            // 打印日志信息
            LOG_ERROR("zookeeper session expired");
        }
    }
}

/////////////////////////////////////////// ZK 客户端实现代码 ///////////////////////////////////////////

// 构造函数
ZkClient::ZkClient() : m_zhandle(nullptr) {
}

// 析构函数
ZkClient::~ZkClient() {
    if (m_zhandle != nullptr) {
        // 关闭 ZK 的客户端句柄（释放资源）
        zookeeper_close(m_zhandle);
    }
}

// 启动 ZK 客户端
bool ZkClient::Start(const std::string &host, const int port) {
    // 拼接 ZK 服务端的连接信息
    const std::string conn_str = host + ":" + std::to_string(port);

    /**
     * 初始化 ZK 的客户端句柄，连接 ZK 服务端（特别注意：这里是异步初始化）
     * ZooKeeper C API 的多线程版本有三个线程，包括：
     * (1) API 调用线程（当前调用 ZK API 的线程）
     * (2) 网络 I/O 线程，基于 pthread_create() + poll 实现
     * (3) Watcher 回调线程，基于 pthread_create() 实现
     */
    m_zhandle = zookeeper_init(conn_str.c_str(), global_watcher, 30000, nullptr, nullptr, 0);
    if (nullptr == m_zhandle) {
        // 打印日志信息
        LOG_ERROR("zookeeper client init failed");
        return false;
    }

    // 创建并初始化信号量
    sem_t init_sem;
    sem_init(&init_sem, 0, 0);

    // 将信号量存放到 ZK 客户端的上下文中
    zoo_set_context(m_zhandle, &init_sem);

    // 设置等待 ZK 客户端连接的超时时间（10 秒）
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    ts.tv_sec += 10;

    // 阻塞等待 ZK 客户端初始化完成
    if (sem_timedwait(&init_sem, &ts) != 0) {
        // 销毁信号量
        sem_destroy(&init_sem);
        // 打印日志信息
        LOG_ERROR("zookeeper client connect timeout");
        return false;
    }

    // 销毁信号量
    sem_destroy(&init_sem);

    // 打印日志信息
    LOG_INFO("zookeeper client init success");

    return true;
}

// 在 ZK 服务器上根据指定的 Path 创建 ZNode 节点
std::string ZkClient::Create(const char *path, const char *data, int datalen, int mode) {
    // 检查节点路径是否合法
    if (!checkPath(path)) {
        // 返回空字符串
        return "";
    }

    // 同步判断 ZNode 节点是否存在
    int flag = zoo_exists_sync(m_zhandle, path, 0);

    // ZNode 节点已存在
    if (ZOK == flag) {
        // 打印日志信息
        LOG_WARN("znode %s create failed, because it existed", path);
        // 返回空字符串
        return "";
    }
    // ZNode 节点不存在
    else if (ZNONODE == flag) {
        // 实际创建的节点路径
        const int path_buf_len = 512;
        char path_buf[path_buf_len] = {0};

        // 同步创建 ZNode 节点
        flag = zoo_create_sync(m_zhandle, path, data, datalen, &ZOO_OPEN_ACL_UNSAFE, mode, path_buf, path_buf_len);
        // 节点创建成功
        if (ZOK == flag) {
            // 打印日志信息
            LOG_INFO("znode %s create success", path_buf);
            // 返回实际创建的节点路径
            return path_buf;
        }
        // 节点创建失败
        else {
            // 打印日志信息
            LOG_ERROR("znode %s create failed", path);
            // 返回空字符串
            return "";
        }
    }
    // 发生错误，比如会话过期、身份认证失败等
    else {
        // 打印日志信息
        LOG_ERROR("znode %s create failed", path);
        // 返回空字符串
        return "";
    }
}

// 在 ZK 服务器上，根据指定的 Path 递归创建 ZNode 节点
std::string ZkClient::CreateRecursive(const char *path, const char *data, int datalen, int mode) {
    // 检查节点路径是否合法
    if (!checkPath(path)) {
        // 返回空字符串
        return "";
    }

    std::string current_path;
    std::string result_path;
    size_t current_pos = 1;       // 跳过第一个 '/'
    std::string full_path(path);  // 拷贝节点路径，避免修改原始字符串

    while (current_pos <= full_path.size()) {
        size_t next_pos = full_path.find('/', current_pos);
        if (next_pos == std::string::npos) {
            // 最后一级路径（完整路径）
            current_path = full_path;
        } else {
            current_path = full_path.substr(0, next_pos);
        }

        bool is_last_path = (next_pos == std::string::npos);   // 是否为最后一级路径
        const char *path_data = is_last_path ? data : "";      // 父路径不写入数据
        int path_data_len = is_last_path ? datalen : 0;        // 父路径的数据长度为零
        int path_mode = is_last_path ? mode : ZOO_PERSISTENT;  // 父路径为持久节点

        // 创建节点
        std::string created_path = Create(current_path.c_str(), path_data, path_data_len, path_mode);

        // 如果节点创建失败
        if (created_path.empty()) {
            // 判断节点是否存在
            int flag = zoo_exists_sync(m_zhandle, current_path.c_str(), 0);
            // 如果节点存在，使用（兼容）已存在的节点
            if (ZOK == flag) {
                created_path = current_path;
            }
            // 如果节点不存在或者发生错误，则直接返回空字符串
            else {
                // 打印日志信息
                LOG_ERROR("znode %s create failed", path);
                // 返回空字符串
                return "";
            }
        }

        // 如果是最后一级路径，则跳出 While 循环
        if (is_last_path) {
            result_path = created_path;
            break;
        }

        current_pos = next_pos + 1;
    }

    return result_path;
}

// 在 ZK 服务器上，根据指定的 Path 获取子节点列表
std::vector<std::string> ZkClient::GetChildren(const char *path) {
    // 检查节点路径是否合法
    if (!checkPath(path)) {
        // 返回空列表
        return {};
    }

    // 同步获取子节点列表
    return zoo_get_children_sync(m_zhandle, path, 0);
}

// 在 ZK 服务器上，根据指定的 Path 获取 ZNode 节点的数据
std::string ZkClient::GetData(const char *path) {
    // 检查节点路径是否合法
    if (!checkPath(path)) {
        // 返回空字符串
        return "";
    }

    // 节点数据
    const int data_buf_len = 2048;
    char data_buf[data_buf_len] = {0};

    // 同步获取 ZNode 节点的数据
    int flag = zoo_get_sync(m_zhandle, path, 0, data_buf, data_buf_len, nullptr);
    // 获取节点数据成功
    if (ZOK == flag) {
        // 返回节点数据
        return data_buf;
    }
    // 获取节点数据失败
    else {
        // 打印日志信息
        LOG_ERROR("get znode data failed, path: %s", path);
        // 返回空字符串
        return "";
    }
}

// 在 ZK 服务器上，根据指定的 Path 获取 ZNode 节点的状态
Stat ZkClient::GetStat(const char *path) {
    // 检查节点路径是否合法
    if (!checkPath(path)) {
        // 返回空数据
        return {};
    }

    // 节点状态
    struct Stat stat;

    // 同步获取 ZNode 节点的状态
    int flag = zoo_get_sync(m_zhandle, path, 0, nullptr, 0, &stat);
    // 获取节点状态成功
    if (ZOK == flag) {
        // 返回节点状态
        return stat;
    }
    // 获取节点状态失败
    else {
        // 打印日志信息
        LOG_ERROR("get znode stat failed, path: %s", path);
        // 返回空数据
        return {};
    }
}

// 在 ZK 服务器上，根据指定的 Path 判断 ZNode 节点是否存在
ZNodeStatus ZkClient::Exist(const char *path) {
    // 检查节点路径是否合法
    if (!checkPath(path)) {
        return UNKNOWN;
    }

    // 同步判断 ZNode 节点是否存在
    int flag = zoo_exists_sync(m_zhandle, path, 0);

    // ZNode 节点已存在
    if (ZOK == flag) {
        return EXIST;
    }
    // ZNode 节点不存在
    else if (ZNONODE == flag) {
        return NOTEXIST;
    }
    // 发生错误，比如会话过期、身份认证失败等
    else {
        return UNKNOWN;
    }
}

// 检查节点路径是否合法
bool ZkClient::checkPath(const char *path) {
    if (path == nullptr || path[0] != '/') {
        // 打印日志信息
        LOG_ERROR("invalid node path: %s", path);
        return false;
    }
    return true;
}