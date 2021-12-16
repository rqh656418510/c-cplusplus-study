#include <stdio.h>
#include <math.h>

// gcc homework-1.c -lm -o homework-1.exe && ./homework-1.exe

/**
 * 题目：输入三个小写字母，输出其ASCII码和对应的大写字母
 */
void work1() {
    char c1, c2, c3;
    printf("input three small character:\n");
    setbuf(stdin, NULL);
    scanf("%c %c %c", &c1, &c2, &c3);
    printf("%d %d %d\n", c1, c2, c3);
    printf("%c %c %c\n", c1 - 32, c2 - 32, c3 - 32);
}

/**
 * 输入三角形的三边长，求三角形面积。
 */
void work2() {
    double a, b, c, s, area;
    printf("input three number:\n");
    setbuf(stdin, NULL);
    scanf("%lf %lf %lf", &a, &b, &c);
    s = (a + b + c) / 2.0;
    area = sqrt(s * (s - a) * (s - b) * (s - c));
    printf("a = %lf, b = %lf, c = %lf, area = %lf\n", a, b, c, area);
}

/**
  * 输入一个字符，判别它是否大写字母，如果是，将它转换成小写字母；如果不是，不转换。然后输出最后得到的字符
  */
void work3() {
    char a;
    printf("input a character:\n");
    setbuf(stdin, NULL);
    scanf("%c", &a);
    if (a >= 'A' && a <= 'Z') {
        printf("%c\n", a + 32);
    } else {
        printf("%c\n", a);
    }
}

/**
 * 使用if语句实现, 输入三个整数，输出最大数和最小数
 */
void work4() {
    double a, b, c, max, min;
    printf("input three number:\n");
    setbuf(stdin, NULL);
    scanf("%lf %lf %lf", &a, &b, &c);
    if (a > b) {
        max = a;
        min = b;
    } else {
        max = b;
        min = a;
    }
    if (c > max) {
        max = c;
    }
    if (c < min) {
        min = c;
    }
    printf("max=%lf, min=%lf\n", max, min);
}

/**
  * 计算器程序。用户输入运算数和四则运算符，输出计算结果。
  */

int work5() {
    double a, b, result;
    char c;
    printf("输入运算数和四则运算符:\n");
    scanf("%lf%c%lf", &a, &c, &b);
    switch (c) {
        case '+': {
            result = a + b;
            break;
        }
        case '-': {
            result = a - b;
            break;
        }
        case '*': {
            result = a * b;
            break;
        }
        case '/': {
            if (0 == b) {
                printf("input error!\n");
                return 1;
            } else {
                result = a / b;
            }
            break;
        }
        default: {
            printf("input error!\n");
            return 1;
        }
    }
    printf("%lf%c%lf=%lf\n", a, c, b, result);
}

/**
 * 统计从键盘输入一行字符的个数
 */
void work6() {
    int i = 0;
    printf("input the string:\n");
    while (getchar() != '\n') {
        i++;
    }
    printf("total: %d\n", i);
}

int main() {
//    work1();
//    work2();
//    work3();
//    work4();
//    work5();
    work6();
    return 0;
}