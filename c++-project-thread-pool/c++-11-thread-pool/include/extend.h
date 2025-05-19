#ifndef EXTEND_H
#define EXTEND_H

#include <memory>
#include <utility>
#include <type_traits>


///////////////////////////////////// make_unique() /////////////////////////////////////


namespace extend {
    // 创建非数组类型对象
    template<typename T, typename... Args>
    typename std::enable_if<!std::is_array<T>::value, std::unique_ptr<T>>::type
    make_unique(Args &&... args) {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }

    // 创建未知大小的数组（例如 make_unique<T[]>(n)）
    template<typename T>
    typename std::enable_if<std::is_array<T>::value && std::extent<T>::value == 0, std::unique_ptr<T>>::type
    make_unique(std::size_t size) {
        using ElementType = typename std::remove_extent<T>::type;
        return std::unique_ptr<T>(new ElementType[size]());
    }

    // 禁止使用定长数组（例如 make_unique<int[10]> 是不合法的）
    template<typename T, typename... Args>
    typename std::enable_if<(std::extent<T>::value != 0), void>::type
    make_unique(Args &&...) = delete;
}


///////////////////////////////////// Any 类型 /////////////////////////////////////


// Any 类型（可以接收任意数据类型）
class Any {

public:
    // 构造函数
    Any() = default;

    // 析构函数
    ~Any() = default;

    // 禁止带左值的拷贝构造函数
    Any(const Any &) = delete;

    // 禁止带左值的赋值运算符
    Any &operator=(const Any &) = delete;

    // 带右值的拷贝构造函数（移动拷贝构造）
    Any(Any &&other) noexcept : base_(std::move(other.base_)) {

    }

    // 带右值的赋值运算符（移动赋值运算符）
    Any &operator=(Any &&other) noexcept {
        if (this != &other) {
            base_ = std::move(other.base_);
        }
        return *this;
    }

    // 通用构造函数（让 Any 类型可以接收任意数据类型）
    template<typename T>
    Any(T&& data) : base_(extend::make_unique<Derive<typename std::decay<T>::type>>(std::forward<T>(data))) {

    }

    // 类型转换（将 Any 类型存储的数据类型提取出来）
    template<typename T>
    T cast() {
        if (base_ == nullptr) {
            throw std::runtime_error("Any is empty");
        }

        // 将基类指针转换为派生类指针（类型向下转换）
        Derive <T> *p = dynamic_cast<Derive <T> *>(base_.get());
        if (p == nullptr) {
            throw std::runtime_error("type is unmatch!");
        }

        // 返回真实的数据类型
        return p->getData();
    }

private:
    // 基类类型
    class Base {

    public:
        // 虚析构函数
        virtual ~Base() = default;
    };

    // 派生类类型
    template<typename T>
    class Derive : public Base {

    public:
        // 通用构造函数
        template<typename U>
        Derive(U &&data) : data_(std::forward<U>(data)) {

        }

        // 析构函数
        ~Derive() {

        }

        T getData() const {
            return data_;
        }

    private:
        T data_;
    };

private:
    std::unique_ptr<Base> base_;    // 基类指针

};


///////////////////////////////////// Semaphore 信号量 /////////////////////////////////////


// 信号量类（用于线程通信）
class Semaphore {

public:
    // 构造函数
    Semaphore(int limit = 0) : limit_(limit) {

    }

    // 析构函数
    ~Semaphore() = default;

    // 获取一个信号量资源
    void wait() {
        // 获取互斥锁
        std::unique_lock<std::mutex> lock(mtx_);

        // 等待信号量资源
        cond_.wait(lock, [this]() { return limit_ > 0; });

        // 更改资源计数
        limit_--;
    }

    // 增加一个信号量资源
    void post() {
        // 获取互斥锁
        std::unique_lock<std::mutex> lock(mtx_);

        // 更改资源计数
        limit_++;

        // 通知其他线程获取信号量资源
        cond_.notify_all();
    }

private:
    int limit_;                     // 资源计数
    std::mutex mtx_;                // 互斥锁
    std::condition_variable cond_;  // 条件变量
};

#endif // EXTEND_H
