#include <stdio.h>

void test1(){
    int i=1;
    i = i++;
    printf("i=%d", i);
}

int main(){
    test1();
    return 0;
}