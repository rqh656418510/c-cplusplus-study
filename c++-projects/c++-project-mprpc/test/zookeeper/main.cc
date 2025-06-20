#include <iostream>
#include <string>

#include "logger.h"
#include "zookeeperutil.h"

// 测试 ZooKeeper 的 API
int main(int argc, char** argv) {
    // 设置日志级别
    Logger::GetInstance().SetLogLevel(INFO);

    /////////////////////////////////// 初始化客户端 ///////////////////////////////////

    // 创建 ZK 客户端
    ZkClient zkCli;

    // 启动 ZK 客户端
    bool started = zkCli.Start("127.0.0.1", 2181);
    if (!started) {
        return -1;
    }

    //////////////////////////////////// 创建节点 ////////////////////////////////////

    std::string path1 = "/cat";
    // 判断节点是否存在
    if (zkCli.Exist(path1.c_str()) == NOTEXIST) {
        // 创建持久化节点
        std::string data1 = "hello cat";
        path1 = zkCli.Create(path1.c_str(), data1.c_str(), data1.length(), ZOO_PERSISTENT);
        LOG_INFO(path1.c_str());
    } else {
        LOG_WARN("node %s existed or error occurred", path1.c_str());
    }

    // 创建临时顺序节点
    std::string path2 = "/dog";
    std::string data2 = "hello dog";
    path2 = zkCli.Create(path2.c_str(), data2.c_str(), data2.length(), ZOO_EPHEMERAL_SEQUENTIAL);
    LOG_INFO(path2.c_str());

    // 递归创建临时节点
    std::string path3 = "/pig/pinkpig";
    std::string data3 = "hello pig";
    path3 = zkCli.CreateRecursive(path3.c_str(), data3.c_str(), data3.length(), ZOO_EPHEMERAL);
    LOG_INFO(path3.c_str());

    //////////////////////////////////// 获取节点数据 ////////////////////////////////////

    // 获取节点的数据（持久化节点）
    std::string resultData1 = zkCli.GetData(path1.c_str());
    LOG_INFO("the data of node %s ==> %s", path1.c_str(), resultData1.c_str());

    // 获取节点的数据（临时顺序节点）
    std::string resultData2 = zkCli.GetData(path2.c_str());
    LOG_INFO("the data of node %s ==> %s", path2.c_str(), resultData2.c_str());

    // 获取节点的数据（临时节点）
    std::string resultData3 = zkCli.GetData(path3.c_str());
    LOG_INFO("the data of node %s ==> %s", path3.c_str(), resultData3.c_str());

    //////////////////////////////////// 获取节点状态 ////////////////////////////////////

    // 获取节点的状态（持久化节点）
    Stat resultStat1 = zkCli.GetStat(path1.c_str());
    LOG_INFO("the stat of node %s ==> version: %u, ephemeralOwner: %u, numChildren: %u, dataLength: %u", path1.c_str(),
             resultStat1.version, resultStat1.ephemeralOwner, resultStat1.numChildren, resultStat1.dataLength);

    // 获取节点的状态（临时顺序节点）
    Stat resultStat2 = zkCli.GetStat(path2.c_str());
    LOG_INFO("the stat of node %s ==> version: %u, ephemeralOwner: %u, numChildren: %u, dataLength: %u", path2.c_str(),
             resultStat2.version, resultStat2.ephemeralOwner, resultStat2.numChildren, resultStat2.dataLength);

    // 获取节点的状态（临时节点）
    Stat resultStat3 = zkCli.GetStat(path3.c_str());
    LOG_INFO("the stat of node %s ==> version: %u, ephemeralOwner: %u, numChildren: %u, dataLength: %u", path3.c_str(),
             resultStat3.version, resultStat3.ephemeralOwner, resultStat3.numChildren, resultStat3.dataLength);

    //////////////////////////////////// 获取子节点列表 ////////////////////////////////////

    std::string path4 = "/pig";
    std::vector<std::string> resultList1 = zkCli.GetChildren(path4.c_str());
    for (std::string& child : resultList1) {
        LOG_INFO("%s is child node of %s", child.c_str(), path4.c_str());
    }

    return 0;
}
