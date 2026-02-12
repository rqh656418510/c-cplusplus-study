#include "CurlHelper.h"

// curl 写回调函数，将返回的数据写入 std::string
size_t CurlWriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}