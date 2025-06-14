#include "mprpcconfig.h"

#include <cstdio>
#include <cstdlib>

// 加载配置文件
void MprpcConfig::LoadConfigFile(const char* config_file) {
    // 打开配置文件
    FILE* pf = fopen(config_file, "r");
    if (nullptr == pf) {
        std::cout << config_file << " is not exist!" << std::endl;
        exit(EXIT_FAILURE);
    }

    // 解析配置文件
    while (!feof(pf)) {
        char buf[1024] = {0};
        fgets(buf, 1024, pf);
        std::string src_buf(buf);

        // 去掉字符串前后的空格字符
        Trim(src_buf);

        // 判断注释内容
        if (src_buf[0] == '#' || src_buf.empty()) {
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
        int endIdx = src_buf.find('\n', idx);
        std::string value = src_buf.substr(idx + 1, endIdx - idx - 1);
        Trim(value);

        // 存储配置项
        m_configMap.insert({key, value});

        // 打印日志信息
        std::cout << key << "=" << value << std::endl;
    }
}

// 获取配置项信息
std::string MprpcConfig::Load(const std::string& key) {
    auto it = m_configMap.find(key);
    return it != m_configMap.end() ? it->second : "";
}

// 去掉字符串前后的空格字符
void MprpcConfig::Trim(std::string& str) {
    // 去除字符串前面多余的空格字符
    int idx = str.find_first_not_of(' ');
    if (idx != -1) {
        str = str.substr(idx, str.size() - idx);
    }

    // 去除字符串后面多余的空格字符
    idx = str.find_last_not_of(' ');
    if (idx != -1) {
        str = str.substr(0, idx + 1);
    }
}