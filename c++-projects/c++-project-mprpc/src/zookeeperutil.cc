#include "zookeeperutil.h"

#include <cstdlib>

#include "logger.h"
#include "mprpcapplication.h"

////////////////////////////////////////////////// ZK 扩展代码 //////////////////////////////////////////////////

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

    // 这里必须判断 ZK 的异步请求调用是否正常，否则可能因为异步请求未发出，导致回调永不执行，最终造成线程死锁
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
int zoo_create_sync(zhandle_t *zh, const char *path, const char *value, int valuelen, const struct ACL_vector *acl,
                    int mode, char *path_buf_out, int path_buf_out_len) {
    // 上下文信息
    SyncCreateContext ctx;

    // 初始化信号量
    sem_init(&ctx.sem, 0, 0);

    // 发起 ZK 异步请求的调用
    int ret = zoo_acreate(zh, path, value, valuelen, acl, mode, znode_create_completion, &ctx);

    // 这里必须判断 ZK 的异步请求调用是否正常，否则可能因为异步请求未发出，导致回调永不执行，最终造成线程死锁
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

// 全局的 Watcher 监听器，接收 ZkServer 给 ZkClient 发送的通知
void global_watcher(zhandle_t *zh, int type, int state, const char *path, void *watcherCtx) {
    // 判断接收到的事件类型是不是会话事件类型
    if (type == ZOO_SESSION_EVENT) {
        // 判断是不是 ZK 客户端连接成功
        if (state == ZOO_CONNECTED_STATE) {
            // 从 ZK 客户端的上下文中获取预设置的信号量
            sem_t *init_sem = (sem_t *)zoo_get_context(zh);
            // 唤醒正在等待 ZK 客户端初始化完成的线程
            sem_post(init_sem);
        }
    }
}

////////////////////////////////////////////////// 类实现代码 //////////////////////////////////////////////////

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
void ZkClient::Start() {
    // 获取 ZK 客户端的连接信息
    std::string host = MprpcApplication::GetInstance().GetConfig().Load(ZK_SERVER_IP_KEY);
    std::string port = MprpcApplication::GetInstance().GetConfig().Load(ZK_SERVER_PORT_KEY);
    std::string conn_str = host + ":" + port;

    /**
     * 初始化 ZK 的客户端句柄（特别注意：这里是异步初始化）
     * ZooKeeper C API 的多线程版本提供了三个线程，包括：
     * (1) API 调用线程（当前调用 ZK API 的线程）
     * (2) 网络 I/O 线程，基于 pthread_create() + poll 实现
     * (3) Watcher 回调线程，基于 pthread_create() 实现
     */
    m_zhandle = zookeeper_init(conn_str.c_str(), global_watcher, 30000, nullptr, nullptr, 0);
    if (nullptr == m_zhandle) {
        LOG_ERROR("zookeeper client init failed!");
        exit(EXIT_FAILURE);
    }

    // 创建并初始化信号量
    sem_t init_sem;
    sem_init(&init_sem, 0, 0);

    // 将信号量存放到 ZK 客户端的上下文中
    zoo_set_context(m_zhandle, &init_sem);

    // 阻塞等待 ZK 客户端初始化完成
    sem_wait(&init_sem);

    // 销毁信号量
    sem_destroy(&init_sem);

    LOG_INFO("zookeeper client init success!");
}

// 在 ZK 服务器上根据指定的 Path 创建 ZNode 节点
void ZkClient::Create(const char *path, const char *data, int datalen, int mode) {
    // 同步判断 ZNode 节点是否存在
    int flag = zoo_exists_sync(m_zhandle, path, 0);

    // ZNode 节点已存在
    if (ZOK == flag) {
        LOG_ERROR("znode %s create failed, because existed!", path);
    }
    // ZNode 节点不存在
    else if (ZNONODE == flag) {
        // 实际创建的节点路径
        const int path_buf_len = 512;
        char path_buf[path_buf_len] = {0};

        // 同步创建 ZNode 节点
        flag = zoo_create_sync(m_zhandle, path, data, strlen(data), &ZOO_OPEN_ACL_UNSAFE, mode, path_buf, path_buf_len);
        if (ZOK == flag) {
            // 节点创建成功
            LOG_INFO("znode %s create success", path_buf);
        } else {
            // 节点创建失败
            LOG_ERROR("znode %s create failed!", path);
        }
    }
    // 发生错误，比如会话过期、身份认证失败等
    else {
        LOG_ERROR("znode %s create failed!", path);
    }
}

// 在 ZK 服务器上，根据指定的 Path 获取 ZNode 节点的值
std::string ZkClient::GetData(const char *path) {
    return "";
}