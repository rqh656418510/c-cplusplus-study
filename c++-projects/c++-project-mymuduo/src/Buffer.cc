#include "Buffer.h"

#include <assert.h>

// 构造函数
Buffer::Buffer(size_t initialSize)
    : buffer_(kCheapPrepend + initialSize), readerIndex_(kCheapPrepend), writerIndex_(kCheapPrepend) {
}

// 析构函数
Buffer::~Buffer() {
}

// 获取缓冲区可读的字节数
size_t Buffer::readableBytes() const {
    return writerIndex_ - readerIndex_;
}

// 获取缓冲区可写的字节数
size_t Buffer::writableBytes() const {
    return buffer_.size() - writerIndex_;
}

// 获取缓冲区可预留的字节数
size_t Buffer::prependableBtes() const {
    return readerIndex_;
}

// 返回缓冲区中可读数据的起始地址
const char* Buffer::peek() const {
    return begin() + readerIndex_;
}

// 移动读指针
void Buffer::retrieve(size_t len) {
    assert(len <= readableBytes());
    if (len < readableBytes()) {
        readerIndex_ += len;
    } else {
        retrieveAll();
    }
}

// 重置读指针与写指针
void Buffer::retrieveAll() {
    readerIndex_ = kCheapPrepend;
    writerIndex_ = kCheapPrepend;
}

// 将所有可读数据以字符串形式返回
std::string Buffer::retrieveAllAsString() {
    return retrieveAsString(readableBytes());
}

// 将指定长度的可读数据以字符串形式返回
std::string Buffer::retrieveAsString(size_t len) {
    assert(len <= readableBytes());
    // 构造字符串
    std::string result(peek(), len);
    // 移动读指针
    retrieve(len);
    return result;
}

// 确保缓冲区有足够的可写空间
void Buffer::ensureWritableBytes(size_t len) {
    if (writableBytes() < len) {
        makeSpace(len);
    }
    assert(writableBytes() >= len);
}

// 扩容缓冲区以容纳更多数据
void Buffer::makeSpace(size_t len) {
    // 判断是否需要通过移动数据来腾出空间
    if (writableBytes() + prependableBtes() < len + kCheapPrepend) {
        // 没有空闲的空间，直接扩容
        buffer_.resize(writerIndex_ + len);
    } else {
        // 有空闲的空间，通过移动数据来腾出空间
        assert(kCheapPrepend < readerIndex_);
        size_t readable = readableBytes();
        std::copy(begin() + readerIndex_, begin() + writerIndex_, begin() + kCheapPrepend);
        readerIndex_ = kCheapPrepend;
        writerIndex_ = readerIndex_ + readable;
        assert(readable == readableBytes());
    }
}

// 返回 vector 底层数组的首元素地址（即数组的起始地址）
char* Buffer::begin() {
    return &*buffer_.begin();
}

// 返回 vector 底层数组的首元素地址（即数组的起始地址）
const char* Buffer::begin() const {
    return &*buffer_.begin();
}