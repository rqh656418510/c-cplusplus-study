#pragma once

#include<cstdlib>

// ����ֵ d ����Ϊ�ٽ���ֵ a �ı���
#define ngx_align(d, a) (((d) + (a - 1)) & ~(a - 1))

// ����ֵ p ����Ϊ�ٽ���ֵ a �ı���
#define ngx_align_ptr(p, a) (u_char *) (((uintptr_t) (p) + ((uintptr_t) a - 1)) & ~((uintptr_t) a - 1))

// ��ָ�����ڴ�ȫ����ʼ��Ϊ0
#define ngx_memzero(buf, n) (void) memset(buf, 0, n)

// �����ض���
using u_char = unsigned char;
using ngx_uint_t = unsigned int;

// ����ǰ������
struct ngx_pool_s;

// ���������ص�������������
typedef void (*ngx_pool_cleanup_pt)(void* data);

// ���������ͷ����Ϣ
struct ngx_pool_cleanup_s {
    ngx_pool_cleanup_pt   handler;     // ����ָ�룬ָ���ڴ���������Ļص�����
    void                  *data;       // ���ݸ��ص������Ĳ���
    ngx_pool_cleanup_s    *next;       // ��һ���������������γɵ�������
};

// ����ڴ���ڴ�ص�ͷ����Ϣ
struct ngx_pool_large_s {
    ngx_pool_large_s    *next;      // ��һ������ڴ棬�����γɵ�������
    void                *alloc;     // ��¼����Ĵ���ڴ����ʼ��ַ
};

// С���ڴ���ڴ�ص�ͷ����Ϣ
struct ngx_pool_data_t {
    u_char         *last;       // �ɷ����ڴ�Ŀ�ʼλ�ã�����ǰ�ڴ�������λ��
    u_char         *end;        // �ɷ����ڴ��ĩβλ��
    ngx_pool_s     *next;       // ���ӵ���һ���ڴ�أ��ڴ�صĺܶ���ڴ����ͨ����ָ�����ӳ������
    ngx_uint_t     failed;      // ��¼��ǰ�ڴ�ط����ڴ�ʧ�ܵĴ�������ʧ�ܴ�������ָ��ֵʱ��current ָ����һ�ڴ�ص�Ԫ
};

// �ڴ�ص����ṹ��
struct ngx_pool_s {
    ngx_pool_data_t         d;              // С���ڴ�ص�ͷ����Ϣ
    size_t                  max;            // С���ڴ��������ռ�
    ngx_pool_s              *current;       // ָ���ڴ���еĿ����ڴ��
    ngx_pool_large_s        *large;         // ����ڴ�������ָ�룬����ڴ����ֱ�Ӳ��ñ�׼ϵͳ�ӿ� malloc()
    ngx_pool_cleanup_s      *cleanup;       // ������ handler �����ָ�룬����ָ���ڴ��ͷ�ʱ��Ҫ������Դ��һЩ��Ҫ����
};

// Ĭ��һ������ҳ��Ĵ�С��4KB��
const int NGX_PAGESIZE = 4096;
// С���ڴ�ɷ�������ռ�
const int NGX_MAX_ALLOC_FROM_POOL = NGX_PAGESIZE - 1;
// �ڴ�ص�Ĭ�ϳ�ʼ��С��16KB��
const int NGX_DEFAULT_POOL_SIZE = 16 * 1024;
// �ڴ�ط���ʱ�Ķ����ֽ�����16 �ֽڣ�
const int NGX_POOL_ALIGNMENT = 16;
// С���ڴ����С�ɽ��ܴ�С
const int NGX_MIN_POOL_SIZE = ngx_align((sizeof(ngx_pool_s) + 2 * sizeof(ngx_pool_large_s)), NGX_POOL_ALIGNMENT);
// С���ڴ����ʱ�Ķ����ֽ�����ͨ���� 4 �ֽڣ�32 λϵͳ������ 8 �ֽڣ�64 λϵͳ��
const int NGX_ALIGNMENT = sizeof(unsigned long);

class ngx_mem_pool {

public:
    // ���캯��
    ngx_mem_pool(int size);
    // ��������
    ~ngx_mem_pool();
    // ��ֹ����
    ngx_mem_pool(const ngx_mem_pool& pool) = delete;
    // ��ֹ��ֵ
	ngx_mem_pool& operator=(const ngx_mem_pool&) = delete;

public:
    // ���ڴ��������ָ����С���ڴ棬�������ڴ��ֽڶ���
    void* ngx_palloc(size_t size);
    // ���ڴ��������ָ����С���ڴ棬�������ڴ��ֽڶ���
    void* ngx_pnalloc(size_t size);
    // ���� ngx_palloc ʵ���ڴ���䣬�����ڴ��ʼ��Ϊ 0
    void* ngx_pcalloc(size_t size);
    // �ͷŴ���ڴ�
    void ngx_pfree(void* p);
    // �����ڴ��
    void ngx_reset_pool();
    // �����ڴ��
    void ngx_destroy_pool();
    // �����Դ����������ص������� 
    ngx_pool_cleanup_s* ngx_pool_cleanup_add(size_t size);

private:
    // ����ָ����С���ڴ��
    void* ngx_create_pool(size_t size);
    // ����С���ڴ�
    void* ngx_palloc_small(size_t size, ngx_uint_t align);
    // �������ڴ�
    void* ngx_palloc_large(size_t size);
    // �����µ�С���ڴ�
    void* ngx_palloc_block(size_t size);

private: 
    // ָ���ڴ�ص����ָ��
	ngx_pool_s* _pool;

};
