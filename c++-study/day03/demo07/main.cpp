/**
 * 1. C++面向对象模型初探
 */

#include <iostream>

using namespace std;

struct S1 {
    int i;
    int j;
    int k;
};

struct S2 {
    int i;
    int j;
    int k;
    static int m;
};

class C1 {
public:
    int i;
    int j;
    int k;
};

class C2 {
public:
    int i;
    int j;
    int k;
    static int m;

public:
    int getK() const {
        return k;
    }

    void setK(int val) {
        k = val;
    }
};

int main() {
    printf("s1:%d \n", sizeof(S1));
    printf("s2:%d \n", sizeof(S2));
    printf("c1:%d \n", sizeof(C1));
    printf("c2:%d \n", sizeof(C2));
    return 0;
}