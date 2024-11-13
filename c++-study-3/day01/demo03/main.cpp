/**
 * 掌握进程虚拟地址空间区域划分
 */

#include <iostream>

using namespace std;

int gdata1 = 10;
int gdata2 = 0;
int gdata3;

static int gdata4 = 11;
static int gdata5 = 0;
static int gdata6;

int main() {
    int a = 12;
    int b = 0;
    int c;

    static int e = 13;
    static int f = 0;
    static int g;

    return 0;
}