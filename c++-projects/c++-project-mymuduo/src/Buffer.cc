#include "Buffer.h"

#include <assert.h>
#include <errno.h>
#include <sys/uio.h>

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
        // 缓冲区扩容
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

// 向缓冲区追加数据
void Buffer::append(const char* data, size_t len) {
    ensureWritableBytes(len);
    std::copy(data, data + len, beginWrite());
    hasWritten(len);
}

// 通知缓冲区已写入数据
void Buffer::hasWritten(size_t len) {
    assert(len <= writableBytes());
    writerIndex_ += len;
}

// 返回缓冲区中可写数据的起始地址
char* Buffer::beginWrite() {
    return begin() + writerIndex_;
}

// 返回缓冲区中可写数据的起始地址
const char* Buffer::beginWrite() const {
    return begin() + writerIndex_;
}

// 从 fd 上读取数据
ssize_t Buffer::readFd(int fd, int* saveErrno) {
    // 在栈上分配内存空间（64KB）
    char extrabuf[65536] = {0};

    // 主缓冲区可写的字节数
    const size_t writable = writableBytes();

    // 采用 scatter-gather 读技术，同时将数据读入主缓冲区和 extrabuf
    struct iovec vec[2];
    vec[0].iov_base = begin() + writerIndex_;
    vec[0].iov_len = writable;
    vec[1].iov_base = extrabuf;
    vec[1].iov_len = sizeof extrabuf;

    // 当主缓冲区 writable 小于 extrabuf（64KB）时，说明主缓冲区的空间可能不够装下数据，
    // 需要使用两个 iovec：第一个写入 buffer_，第二个写入 extrabuf，从而尽可能读完内核中的数据。
    // 否则，如果主缓冲区足够大，只需一个 iovec。
    const int iovcnt = (writable < sizeof extrabuf) ? 2 : 1;

    // 读取数据
    const ssize_t n = ::readv(fd, vec, iovcnt);

    // 如果发生错误
    if (n < 0) {
        *saveErrno = errno;
    }
    // 如果只写入了主缓冲区，没有写入了 extrabuf
    else if (n <= writable) {
        writerIndex_ += n;
    }
    // 如果不仅写入了主缓冲区，还写入了 extrabuf
    else {
        writerIndex_ = buffer_.size();
        append(extrabuf, n - writable);
    }
    return n;
}

// 返回 vector 底层数组的首元素地址（即数组的起始地址）
char* Buffer::begin() {
    return &*buffer_.begin();
}

// 返回 vector 底层数组的首元素地址（即数组的起始地址）
const char* Buffer::begin() const {
    return &*buffer_.begin();
}