#include <stdio.h>
#include <math.h>

/**
 * 1. Hello Wolrd 程序
 * 2. C语言标准输入/输出的使用语法
 */

int main(){

//    ----------------------------------Hello World程序
     printf("Hello World!\n");

//    ----------------------------------标准输入/输出
    double n, s;
    printf("input a int number:\n");
    setbuf(stdin, NULL);
    scanf("%lf", &n);
    s = sin(n);
    printf("sine of %lf is %lf\n", n, s);

//    ----------------------------------标准输入/输出
    int x, y, result;
    printf("input two int number:\n");
    setbuf(stdin, NULL);
    scanf("%d %d", &x, &y);
    result = max(x, y);
    printf("%d and %d, the max number is %d", x, y, result);
}

int max(int a, int b){
    if(a > b)
        return a;
    else
        return b;
}
