#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "copyable.h"

/// A buffer class modeled after org.jboss.netty.buffer.ChannelBuffer
///
/// @code
/// +-------------------+------------------+------------------+
/// | prependable bytes |  readable bytes  |  writable bytes  |
/// |                   |     (CONTENT)    |                  |
/// +-------------------+------------------+------------------+
/// |                   |                  |                  |
/// 0      <=      readerIndex   <=   writerIndex    <=     size
/// @endcode

class Buffer : public copyable {
public:
    static const size_t kCheapPrepend = 8;    // 预留空间大小
    static const size_t kInitialSize = 1024;  // 初始缓冲区大小

    // 构造函数
    explicit Buffer(size_t initialSize = kInitialSize);

    // 析构函数
    ~Buffer();

    // 获取缓冲区可读的字节数
    size_t readableBytes() const;

    // 获取缓冲区可写的字节数
    size_t writableBytes() const;

    // 获取缓冲区可预留的字节数
    size_t prependableBtes() const;

    // 返回缓冲区中可读数据的起始地址
    const char* peek() const;

    // 移动读指针
    void retrieve(size_t len);

    // 重置读指针与写指针
    void retrieveAll();

    // 将所有可读数据以字符串形式返回
    std::string retrieveAllAsString();

    // 将指定长度的可读数据以字符串形式返回
    std::string retrieveAsString(size_t len);

    // 确保缓冲区有足够的可写空间
    void ensureWritableBytes(size_t len);

    // 扩容缓冲区以容纳更多数据
    void makeSpace(size_t len);

private:
    // 返回 vector 底层数组的首元素地址（即数组的起始地址）
    char* begin();

    // 返回 vector 底层数组的首元素地址（即数组的起始地址）
    const char* begin() const;

    std::vector<char> buffer_;  // 底层缓冲区
    size_t readerIndex_;        // 读指针位置
    size_t writerIndex_;        // 写指针位置
};