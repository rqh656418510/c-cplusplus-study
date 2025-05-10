#include<iostream>
#include<vector>
#include "custom_allocator.h"

using namespace std;

void test01() {
    vector<int, custom_allocator<int>> vec1;
}

int main() {
    test01();
    return 0;
}
