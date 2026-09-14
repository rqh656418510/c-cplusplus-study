/**
 * new细节探秘，重载类operator new delete
 *
 * (a) new 分配内存的细节
 */

#include <cstring>
#include <iostream>

void fun() {
    char* ptr = new char[10];
    memset(ptr, '\0', 10);
    delete[] ptr;

    int* ptr2 = new int(10);
    delete ptr2;
}

int main() {
    fun();
    return 0;
}