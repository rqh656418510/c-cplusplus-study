#include <stdio.h>
#include <math.h>
#include <curses.h>

// gcc work-2.c -lm  -l curses -o work-2.exe && ./work-2.exe

/**
问题:输出以下图形
*
**
***
****
*****
******
*/
void work1(){
    int line, times, max=6;
    for(line=0; line<max; line++){
        for(times=0; times<line+1; times++){
            printf("%c", '*');
        }
        printf("%c", '\n');
    }
}

/**
 * 题目：有1、2、3、4个数字，能组成多少个互不相同且无重复数字的三位数？都是多少？
 * 1.程序分析：可填在百位、十位、个位的数字都是1、2、3、4。组成所有的排列后再去掉不满足条件的排列
 */
void work2(){
    int i, j, k, total=0;
    for(i=1; i<5; i++){
        for(j=1; j<5; j++){
            for(k=1; k<5; k++){
                if(i!=j && i!=k && j!=k){
                    total++;
                    printf("%d,%d,%d\n", i, j, k);
                }
            }
        }
    }
    printf("total: %d\n", total);
}

/**
 * 题目：显示输入的字符, 如果按的是Esc键, 则退出循环； 如果按的是Enter键, 则不做任何处理，继续输入下一个字符
 */
void work3(){
    char c;
    initscr();
    while(1){
        c = getch();
        if(c == 27) {
            break;
        }
        if(c == 10){
            continue;
        }
        printf("%c", c);
    }
    endwin();
}

/**
 * 题目：用π/4≈1-1/3+1/5-1/7+。。。。公式求π的近似值，直到某一项的绝对值小于1e-6为止
 */
void work4(){
    double i, t, s, pi;
    i=1, t=1, s=1, pi=0;
    while(fabs(t) > 1e-6){
        pi = pi + t;
        i = i + 2;
        s = -s;
        t = s / i;
    }
    printf("pi=%10.6f\n", pi * 4);
}

/**
 * 题目：求Fibonacci数列前40个数。这个数列有如下特点：第1，2两个数为1，1, 从第3个数开始，该数是其前面两个数之和
 */
void work5(){
    int j;
    long f = 1, s = 1, k = 0;
    printf("%ld %ld ", f, s);
    for(j=0; j<38; j++){
        k = f + s;
        f = s;
        s = k;
        printf("%ld ", k);
    }
}

/**
 * 题目：允许输入一个数m，并判断m是否为素数
 */
void work6(){
    int m, i, k;
    printf("input a number:\n");
    setbuf(stdin, NULL);
    scanf("%d", &m);
    k = sqrt(m);
    for(i=2; i<=k; i++) {
        if (m % i == 0) {
            break;
        }
    }
    if(i > k)
    {
        printf("%d is a prime number\n", m);
    }else {
        printf("%d is not a prime number\n", m);
    }
}

/**
 * 题目：求100～200间的全部素数并打印出来
 */
void work7(){
    int j;
    for(j=100; j<=200; j++){
        int i, k = sqrt(j);
        for(i=2; i<=k; i++) {
            if (j % i == 0) {
                break;
            }
        }
        if(i > k)
        {
            printf("%d ", j);
        }
    }
    printf("\n");
}

int main(){
//    work1();
//    work2();
//    work3();
//    work4();
//    work5();
//    work6();
    work7();
    return 0;
}