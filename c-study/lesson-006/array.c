#include <stdio.h>

/**
 * 1. 一维数组定义
 * 2. 一维数组初始化赋值
 * 3. 一维数组动态赋值
 */

void getMax(){
    int i, max=0, a[5];
    printf("please input five int number:\n");
    setbuf(stdin, NULL);
    for(i=0; i<=4; i++){
        scanf("%d", &a[i]);
    }
    for(i=0; i<=4; i++){
        if(a[i] > max){
            max = a[i];
        }
    }
    printf("max=%d\n", max);
}

int main(){

    // ----------------------------------一维数组定义
    int i, a[5];
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;
    a[3] = 4;
    a[4] = 5;
    for(i=0; i<5; i++){
        printf("%d ", a[i]);
    }
    printf("\n");
    printf("---------------\n");

    // ----------------------------------一维数组初始化赋值
    int j;
    int b[5] = {1, 2, 3, 4, 5};
    for(j=0; j<=4; j++){
        printf("%d ", b[j]);
    }
    printf("\n");
    printf("---------------\n");

    // ----------------------------------一维数组动态赋值
    getMax();
    printf("---------------\n");
    return 0;
}
