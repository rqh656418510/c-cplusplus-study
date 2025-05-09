#include<iostream>
#include<memory>
#include "ngx_mem_pool.h"

using namespace std;

// �Զ�����������
struct Data {
    char* ptr;
    FILE* pfile;
};

// �Զ�����Դ�������
void cleanFunc1(void * arg) {
	char* p = (char*)arg;
	cout << "free ptr memory!" << endl;
    free(p);
}

// �Զ�����Դ�������
void cleanFunc2(void * arg) {
	FILE* p = (FILE*)arg;
    cout << "close file!" << endl;
	fclose(p);
}

int main() {
    // �����ڴ��
    unique_ptr<ngx_mem_pool> pool(new ngx_mem_pool(256));

	// ��С���ڴ�ط����ڴ�
    void* p1 = pool->ngx_palloc(128);
    if (p1 == nullptr){
        cout << "ngx_palloc 128 bytes fail..." << endl;
        return -1;
    }

    // �Ӵ���ڴ�ط����ڴ�
    Data* p2 = (Data*) pool->ngx_palloc(512);
	if (p2 == nullptr) {
		cout << "ngx_palloc 512 bytes fail..." << endl;
        return -1;
    }

	p2->ptr = (char*)malloc(12);
    if (p2->ptr == nullptr) {
        cout << "malloc 12 bytes fail..." << endl;
        return -1;
    }

    strcpy(p2->ptr, "hello world");
    p2->pfile = fopen("data.txt", "w");

    // �����Դ�������
    ngx_pool_cleanup_s* c1 = pool->ngx_pool_cleanup_add(sizeof(char*));
    c1->handler = cleanFunc1;
    c1->data = p2->ptr;

    // �����Դ�������
    ngx_pool_cleanup_s* c2 = pool->ngx_pool_cleanup_add(sizeof(FILE*));
    c2->handler = cleanFunc2;
    c2->data = p2->pfile;

    // �ڴ��������ָ������������н�������Զ������ڴ��

    return 0;
}
