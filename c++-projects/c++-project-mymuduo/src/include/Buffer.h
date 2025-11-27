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

    // 获取缓冲区中可读的字节数
    size_t readableBytes() const;

    // 获取缓冲区中可写的字节数
    size_t writableBytes() const;

    // 获取缓冲区中可预留的字节数
    size_t prependableBtes() const;

    // 返回缓冲区中可读数据的起始地址
    const char* peek() const;

    // 移动读指针
    void retrieve(size_t len);

    // 重置读指针与写指针
    void retrieveAll();

    // 将缓冲区中所有可读数据以字符串形式返回
    std::string retrieveAllAsString();

    // 将缓冲区中指定长度的可读数据以字符串形式返回
    std::string retrieveAsString(size_t len);

    // 确保缓冲区有足够的可写空间
    void ensureWritableBytes(size_t len);

    // 扩容缓冲区以容纳更多数据
    void makeSpace(size_t len);

    // 向缓冲区追加数据
    void append(const char* data, size_t len);

    // 通知缓冲区已写入数据
    void hasWritten(size_t len);

    // 返回缓冲区中可写数据的起始地址
    char* beginWrite();

    // 返回缓冲区中可写数据的起始地址
    const char* beginWrite() const;

    // 从 fd 上读取数据，并写到缓冲区中（返回值：n > 0：读取成功；n == 0：连接关闭；n < 0：读取出错）
    ssize_t readFd(int fd, int* saveErrno);

    // 从缓冲区中读取数据，并写到 fd 上（返回值：n > 0：写入成功；n == 0：没有数据可写入；n < 0：写入出错）
    ssize_t writeFd(int fd, int* saveErrno);

private:
    // 返回 vector 底层数组的首元素地址（即数组的起始地址）
    char* begin();

    // 返回 vector 底层数组的首元素地址（即数组的起始地址）
    const char* begin() const;

    std::vector<char> buffer_;  // 底层缓冲区
    size_t readerIndex_;        // 读指针位置
    size_t writerIndex_;        // 写指针位置
};