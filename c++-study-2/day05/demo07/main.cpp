/**
 * []运算符重载
 */
#include <iostream>

using namespace std;

class MyVector {

public:
    // [] 运算符重载
    int &operator[](int index) {
        if (index < 0 || index >= 5) {
            cerr << "Index out of bounds" << endl;
            exit(1);
        }
        return data[index];
    }

private:
    int data[5];

};

int main() {
    MyVector vector;

    // 设置向量中的值
    for (int i = 0; i < 5; i++) {
        vector[i] = i * 2;
    }

    // 设置向量中的值
    vector[1] = 100;

    // 访问向量中的值并输出
    for (int i = 0; i < 5; i++) {
        cout << "vector[" << i << "] = " << vector[i] << endl;
    }

    return 0;
}
