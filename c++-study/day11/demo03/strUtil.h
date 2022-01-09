#pragma once

#include <iostream>

using namespace std;

// 字符串工具类
class StringUtil {

public:

    // 去除字符串两边的空格
    static void trim(string &str) {
        if (str.empty()) {
            return;
        }
        str.erase(0, str.find_first_not_of(" "));
        str.erase(str.find_last_not_of(" ") + 1);
    }

    // 判断字符串是否为空
    // "" -> true
    // " " -> true
    // " a " -> false
    static bool empty(const string &str) {
        if (str.empty()) {
            return true;
        }
        string strTemp = str;
        trim(strTemp);
        return strTemp.length() == 0;
    }

    // 分割字符串
    // str: 要分割的字符串
    // delim: 分割字符
    static vector<string> split(const string &str, const char &delim = ' ') {
        vector<string> tokens;
        size_t lastPos = str.find_first_not_of(delim, 0);
        size_t pos = str.find(delim, lastPos);
        while (lastPos != string::npos) {
            tokens.emplace_back(str.substr(lastPos, pos - lastPos));
            lastPos = str.find_first_not_of(delim, pos);
            pos = str.find(delim, lastPos);
        }
        return tokens;
    }

};