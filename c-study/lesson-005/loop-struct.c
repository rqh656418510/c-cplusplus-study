#include <stdio.h>

/**
 *  1. 使用goto语句和if语句构成循环
 *  2. 使用while语句构成循环
 *  3. do-while循环语句
 *  4. for语句
 *  5. continue语句
 */
int main(){

    //    ----------------------------------使用goto语句和if语句构成循环
    int i=1, sum=0;
    loop: if(i<=100){
        sum += i;
        i++;
        goto loop;
    }
    printf("%d\n", sum);
    printf("---------------\n");

    //    ----------------------------------使用while语句构成循环
    int i1=1, sum1=0;
    while(i1<=100){
        sum1 += i1;
        i1++;
    }
    printf("%d\n", sum1);
    printf("---------------\n");

    //    ----------------------------------do-while循环语句
    int i2=1, sum2=0;
    do {
        sum2 += i2;
        i2++;
    } while (i2 <= 100);
    printf("%d\n", sum2);
    printf("---------------\n");

    //    ----------------------------------for语句
    int i3, sum3=0;
    for(i3=0; i3<=100; i3++){
        sum3 += i3;
    }
    printf("%d\n", sum3);
    printf("---------------\n");

    //    ----------------------------------continue语句
    int n;
    for(n=100; n<=200; n++){
        if(n%3 == 0){
            continue;
        }
        printf("%d\n", n);
    }
    printf("---------------\n");

}