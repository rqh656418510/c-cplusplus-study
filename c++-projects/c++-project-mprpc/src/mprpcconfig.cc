#include "mprpcconfig.h"

#include <cstdio>
#include <cstdlib>

// 加载配置文件
void MprpcConfig::LoadConfigFile(const char* config_file) {
    // 判断是否已经加载过配置文件
    if (!m_configMap.empty()) {
        return;
    }

    // 打开配置文件
    FILE* pf = fopen(config_file, "r");
    if (nullptr == pf) {
        std::cout << config_file << " is not exist!" << std::endl;
        exit(1);
    }

    // 解析配置文件
    char buf[1024];
    while (fgets(buf, sizeof(buf), pf)) {
        std::string src_buf(buf);

        // 去掉字符串前后的空白字符
        Trim(src_buf);

        // 判断注释内容
        if (src_buf.empty() || src_buf[0] == '#') {
            continue;
        }

        // 解析配置项
        int idx = src_buf.find_first_of('=');
        if (idx == -1) {
            // 配置项不合法
            continue;
        }

        // 获取配置项的 Key
        std::string key = src_buf.substr(0, idx);
        Trim(key);

        // 获取配置项的 Value
        std::string value = src_buf.substr(idx + 1);
        Trim(value);

        // 检查配置项的合法性
        if (key.empty() || value.empty()) {
            continue;
        }

        // 存储配置项
        m_configMap.insert({key, value});

        // 打印日志信息
        LOG_DEBUG("%s=%s", key.c_str(), value.c_str());
    }

    // 关闭文件
    fclose(pf);
}

// 获取配置项信息
std::string MprpcConfig::Load(const std::string& key) {
    auto it = m_configMap.find(key);
    return it != m_configMap.end() ? it->second : "";
}

// 去掉字符串前后的空白字符
void MprpcConfig::Trim(std::string& str) {
    // 定义空白字符
    const std::string whitespace = " \n\r\t";

    // 去除字符串前面多余的空白字符
    size_t start = str.find_first_not_of(whitespace);
    if (start != std::string::npos) {
        str = str.substr(start);
    } else {
        // 字符串全是空白字符
        str.clear();
        return;
    }

    // 去除字符串后面多余的空白字符
    size_t end = str.find_last_not_of(whitespace);
    if (end != std::string::npos) {
        str = str.substr(0, end + 1);
    }
}