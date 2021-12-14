#include <stdio.h>

/**
 * 1. 关系运算符
 * 2. 逻辑运算符
 * 3. if语句
 * 4. switch语句
 */
int main(){

    //    ----------------------------------关系运算符
//    char c='k';
//    int i=1,j=2,k=3;
//    float x=3e+5,y=0.85;
//    printf("%d,%d\n",'a'+5<c,-i-2*j>=k+1);
//    printf("%d,%d\n",1<j<5,x-5.25<=x+y);
//    printf("%d,%d\n",i+j+k==-2*j,k==j==i+5);
//    printf("---------------\n");

    //    ----------------------------------逻辑运算符
//    char c='k';
//    int i=1,j=2,k=3;
//    float x=3e+5,y=0.85;
//    printf("%d,%d\n",!x*!y,!!!x);
//    printf("%d,%d\n",x||i&&j-3,i<j&&x<y);
//    printf("%d,%d\n",i==5&&c&&(j=8),x+y||i+j+k);
//    printf("---------------\n");

    //    ----------------------------------if语句
    double a, b, c, t;
    printf("input three number:\n");
    setbuf(stdin, NULL);
    scanf("%lf %lf %lf", &a, &b, &c);
    if(a > b){
        t = b;
        b = a;
        a = t;
    }
    if(a > c){
        t = c;
        c = a;
        a = t;
    }
    if(b > c){
        t = b;
        b = c;
        c = t;
    }
    printf("%lf %lf %lf\n", a, b, c);
    printf("---------------\n");

    //    ----------------------------------switch语句
    int n;
    printf("input a number:\n");
    setbuf(stdin, NULL);
    scanf("%d", &n);
    switch(n){
        case 1:printf("Monday\n"); break;
        case 2:printf("Tuesday\n"); break;
        case 3:printf("Wednesday\n"); break;
        case 4:printf("Thursday\n"); break;
        case 5:printf("Friday\n"); break;
        case 6:printf("Saturday\n"); break;
        case 7:printf("Sunday\n"); break;
        default:printf("error\n");
    }
    printf("---------------\n");

}