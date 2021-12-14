#include <stdio.h>

/**
 * 1. #define 符号常量的使用
 * 2. 整型变量（short, int, long, unsigned）的使用
 * 3. 整型数据的溢出
 * 4. 浮点型变量（float, double, long double）的使用
 */

#define PRICE 30;

void count(){
    long x, y;
    int a, b, c, d;
    x = 5;
    y = 6;
    a = 7;
    b = 8;
    c = x + a;
    d = y + b;
    printf("%d = %d + %d, %d = %d + %d\n", c, x, a, d, y, b);

    int n = 3;
    float m = 6.3;
    float nm = n + m;
    printf("%d + %f = %f\n", n, m, nm);
}

int main(){

//    ----------------------------------符号常量的使用
    int num, total;
    num = 3;
    total = num * PRICE;
    printf("total=%d\n", total);
    printf("---------------\n");


//    ----------------------------------整型变量所占的字节数
    short a = 3;
    printf("short size is %d byte\n", sizeof(a));
    int b = 4;
    printf("int size is %d byte\n", sizeof(b));
    long c = 5;
    printf("long size is %d byte\n", sizeof(c));
    unsigned d = 10;
    printf("unsigned size is %d byte\n", sizeof(d));
    printf("---------------\n");


//    ----------------------------------整型数据的溢出
    short int x, y;
    x = 32767;
    y = x + 1;
    printf("%d, %d\n", x, y);
    printf("---------------\n");


//    ----------------------------------浮点型变量所占的字节数
    float e = 3.14;
    printf("float size is %d byte\n", sizeof(e));
    double f = 3.14;
    printf("double size is %d byte\n", sizeof(f));
    long double g = 3.14;
    printf("long double size is %d byte\n", sizeof(g));
    printf("---------------\n");


//    ----------------------------------不同的类型可以参与运算并赋值，其中的类型转换由编译器自动完成
    count();
}

