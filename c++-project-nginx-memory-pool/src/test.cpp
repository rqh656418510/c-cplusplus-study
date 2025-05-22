#include<iostream>
#include<memory>
#include <string.h>
#include "ngx_mem_pool.h"

using namespace std;

// 自定义数据类型
struct Data {
    char *ptr;
    FILE *pfile;
};

// 自定义资源清理操作
void cleanFunc1(void *arg) {
    char *p = (char *) arg;
    cout << "free ptr memory!" << endl;
    free(p);
}

// 自定义资源清理操作
void cleanFunc2(void *arg) {
    FILE *p = (FILE *) arg;
    cout << "close file!" << endl;
    fclose(p);
}

int main() {
    // 创建内存池
    unique_ptr<ngx_mem_pool> pool(new ngx_mem_pool(256));

    // 从小块内存池分配内存
    void *p1 = pool->ngx_palloc(128);
    if (p1 == nullptr) {
        cout << "ngx_palloc 128 bytes fail..." << endl;
        return -1;
    }

    // 从大块内存池分配内存
    Data *p2 = (Data *) pool->ngx_palloc(512);
    if (p2 == nullptr) {
        cout << "ngx_palloc 512 bytes fail..." << endl;
        return -1;
    }

    p2->ptr = (char *) malloc(12);
    if (p2->ptr == nullptr) {
        cout << "malloc 12 bytes fail..." << endl;
        return -1;
    }

    strcpy(p2->ptr, "hello world");
    p2->pfile = fopen("data.txt", "w");

    // 添加资源清理操作
    ngx_pool_cleanup_s *c1 = pool->ngx_pool_cleanup_add(sizeof(char *));
    c1->handler = cleanFunc1;
    c1->data = p2->ptr;

    // 添加资源清理操作
    ngx_pool_cleanup_s *c2 = pool->ngx_pool_cleanup_add(sizeof(FILE *));
    c2->handler = cleanFunc2;
    c2->data = p2->pfile;

    // 内存池由智能指针管理，程序运行结束后会自动销毁内存池

    return 0;
}