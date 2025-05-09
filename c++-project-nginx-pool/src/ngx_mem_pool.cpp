#include<iostream>
#include <stdexcept>
#include "ngx_mem_pool.h"

// ���캯��
ngx_mem_pool::ngx_mem_pool(int size) {
    // �����ڴ��
	this->ngx_create_pool(size);
    if (_pool == nullptr) {
        throw "create memory pool fail...";
    }
}

// ��������
ngx_mem_pool::~ngx_mem_pool() {
    // �����ڴ��
	if (_pool != nullptr) {
        this->ngx_destroy_pool();
    }
}

// ����ָ����С���ڴ��
void* ngx_mem_pool::ngx_create_pool(size_t size) {
    if (size < sizeof(ngx_pool_s)) {
        std::cout << "create memory pool fail, pool size too small" << std::endl;
		return nullptr;
    }

	// �����ڴ�ռ�
    _pool = (ngx_pool_s*) malloc(size);
    if (_pool == nullptr) {
        return nullptr;
	}

    // С���ڴ�ص�ͷ����Ϣ
    _pool->d.last = (u_char*)_pool + sizeof(ngx_pool_s);
    _pool->d.end = (u_char*)_pool + size;
    _pool->d.next = nullptr;
    _pool->d.failed = 0;

    // С���ڴ��������ռ�
    size = size - sizeof(ngx_pool_s);
    _pool->max = (size < NGX_MAX_ALLOC_FROM_POOL) ? size : NGX_MAX_ALLOC_FROM_POOL;

    _pool->current = _pool;
    _pool->large = nullptr;
    _pool->cleanup = nullptr;

    return _pool;
}

// ���ڴ��������ָ����С���ڴ棬�������ڴ��ֽڶ���
void* ngx_mem_pool::ngx_palloc(size_t size) {
    if (size <= this->_pool->max) {
        return ngx_palloc_small(size, 1);
    }
	return ngx_palloc_large(size);
}

// ���ڴ��������ָ����С���ڴ棬�������ڴ��ֽڶ���
void* ngx_mem_pool::ngx_pnalloc(size_t size) {
    if (size <= this->_pool->max) {
		return ngx_palloc_small(size, 0);
    }
	return ngx_palloc_large(size);
}

// ���� ngx_palloc ʵ���ڴ���䣬�����ڴ��ʼ��Ϊ 0
void* ngx_mem_pool::ngx_pcalloc(size_t size) {
    void* p;

    p = ngx_palloc(size);
    if (p) {
        ngx_memzero(p, size);
    }

    return p;
}

// ����С���ڴ�
void* ngx_mem_pool::ngx_palloc_small(size_t size, ngx_uint_t align) {
    u_char* m;
    ngx_pool_s* p;

    p = this->_pool->current;

    // ����С���ڴ�����������п��ÿռ��С���ڴ�
    do {
        m = p->d.last;

        if (align) {
            m = ngx_align_ptr(m, NGX_ALIGNMENT);
        }

        if ((size_t)(p->d.end - m) >= size) {
            p->d.last = m + size;

            return m;
        }

        p = p->d.next;

    } while (p);

    // ���Ҳ����п��ÿռ��С���ڴ棬��ֱ�ӷ����µ�С���ڴ�
    return ngx_palloc_block(size);
}

// �������ڴ�
void* ngx_mem_pool::ngx_palloc_large(size_t size) {
    void* p;
    ngx_uint_t n;
    ngx_pool_large_s* large;

    // �����µĴ���ڴ�
    p = malloc(size);
    if (p == nullptr) {
        return nullptr;
    }

    n = 0;

    // ��������ڴ���������µĴ���ڴ���ӵ�������
    for (large = this->_pool->large; large; large = large->next) {
        if (large->alloc == nullptr) {
            large->alloc = p;
            return p;
        }

        if (n++ > 3) {
            break;
        }
    }

    large = (ngx_pool_large_s*) ngx_palloc_small(sizeof(ngx_pool_large_s), 1);
    if (large == nullptr) {
        free(p);
        return nullptr;
    }

    large->alloc = p;
    large->next = this->_pool->large;
    this->_pool->large = large;

    return p;
}

// �����µ�С���ڴ�
void* ngx_mem_pool::ngx_palloc_block(size_t size) {
    u_char* m;
    size_t psize;
	ngx_pool_s* p, * _new;

    // �µ�С���ڴ�Ĵ�С
	psize = (size_t)(this->_pool->d.end - (u_char*)this->_pool);

    // �����µ�С���ڴ�
	m = (u_char*)malloc(psize);
    if (m == nullptr) {
        return nullptr;
    }

    _new = (ngx_pool_s*)m;

    // �µ�С���ڴ��ͷ����Ϣ
    _new->d.end = m + psize;
    _new->d.next = nullptr;
    _new->d.failed = 0;

    m += sizeof(ngx_pool_data_t);
    m = ngx_align_ptr(m, NGX_ALIGNMENT);
    _new->d.last = m + size;

    for (p = this->_pool->current; p->d.next; p = p->d.next) {
        if (p->d.failed++ > 4) {
            this->_pool->current = p->d.next;
        }
    }

    p->d.next = _new;

    return m;
}

// �ͷŴ���ڴ�
void ngx_mem_pool::ngx_pfree(void* p) {
    ngx_pool_large_s * l;
    for (l = this->_pool->large; l; l = l->next) {
        if (p == l->alloc) {
            free(l->alloc);
            l->alloc = nullptr;
            return;
        }
    }
}

// �����ڴ��
void ngx_mem_pool::ngx_reset_pool() {
    ngx_pool_s* p;
    ngx_pool_large_s* l;

    // �ͷŴ���ڴ�������е������ڴ�
    for (l = this->_pool->large; l; l = l->next) {
        if (l->alloc) {
            free(l->alloc);
        }
    }

    // ����С���ڴ�������еĵ�һ���ڴ棬ʵ�ֺ���С���ڴ�ĸ���
    p = this->_pool;
    p->d.last = (u_char*)p + sizeof(ngx_pool_s);
    p->d.failed = 0;


    // ����С���ڴ�������еĵڶ��鵽���һ���ڴ棬ʵ�ֺ���С���ڴ�ĸ���
    for (p = p->d.next; p; p = p->d.next) {
        p->d.last = (u_char*)p + sizeof(ngx_pool_data_t);
        p->d.failed = 0;
	}

    this->_pool->current = this->_pool;
	this->_pool->large = nullptr;
}

// �����ڴ��
void ngx_mem_pool::ngx_destroy_pool() {
    ngx_pool_s* p, * n;
    ngx_pool_large_s* l;
    ngx_pool_cleanup_s* c;

    // ������������������ص������� 
    for (c = this->_pool->cleanup; c; c = c->next) {
        if (c->handler) {
            c->handler(c->data);
		}
    }
    
    // �ͷŴ���ڴ�������е������ڴ�
    for (l = this->_pool->large; l; l = l->next) {
        if (l->alloc) {
            free(l->alloc);
        }
    }

    // �ͷ�С���ڴ�������е������ڴ�
    for (p = this->_pool, n = this->_pool->d.next; /* void */; p = n, n = n->d.next) {
        free(p);
        if (n == nullptr) {
            break;
        }
    }
}

// �����Դ����������ص������� 
ngx_pool_cleanup_s* ngx_mem_pool::ngx_pool_cleanup_add(size_t size) {
    ngx_pool_cleanup_s* c;

	c = (ngx_pool_cleanup_s*)ngx_palloc(sizeof(ngx_pool_cleanup_s));
    if (c == nullptr) {
        return nullptr;
    }

    if (size) {
		c->data = ngx_palloc(size);
        if (c->data == nullptr) {
            return nullptr;
        }

    }
    else {
        c->data = nullptr;
    }

    c->handler = nullptr;

    // ��ӵ���Դ������������У�ͷ�巨��
    c->next = this->_pool->cleanup;
    this->_pool->cleanup = c;

    return c;
}
