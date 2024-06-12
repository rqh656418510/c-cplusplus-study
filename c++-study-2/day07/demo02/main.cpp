/**
 * 使用函数模板实现通用的数组排序
 *
 * <p> 选择排序
 * <p> 1. 基本思想：反复从未排序部分中选择最小（或最大）的元素，将其放到已排序部分的末尾，该过程一直进行到所有元素均排序完成。
 * <p> 2. 时间复杂度：选择排序的时间复杂度为 O(n^2)，其中 n 是数组的元素个数。因为它有两个嵌套的循环，每个循环都运行 O(n) 次。
 * <p> 3. 空间复杂度：选择排序是原地排序算法（in-place sort），空间复杂度为 O(1)。
 * <p> 4. 稳定性：选择排序是不稳定的排序算法，因为在找到最小元素并进行交换时，可能会改变相同元素的相对顺序。
 */

#include <iostream>

using namespace std;

// 交换两个元素
template<class T1>
void mySwap(T1 &a, T1 &b) {
    T1 tmp = a;
    a = b;
    b = tmp;
}

// 数组排序
template<class T2, size_t N>
void mySort(T2 (&array)[N]) {
    // 实现选择排序，从小到大
    for (int i = 0; i < N - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < N; j++) {
            if (array[j] < array[minIndex]) {
                minIndex = j;
            }
        }
        // 交换
        if (minIndex != i) {
            mySwap(array[i], array[minIndex]);
        }
    }
}

// 打印数组
template<class T3, size_t M>
void printArray(T3 (&array)[M]) {
    for (const T3 item : array) {
        cout << item << " ";
    }
    cout << endl;
}

int main() {
    int array1[] = {5, 2, 4, 6, 3, 9, 1};
    mySort(array1);
    printArray(array1);

    char array2[] = {'c', 'a', 'z', 'h', 'n', 'p', 'k'};
    mySort(array2);
    printArray(array2);

    return 0;
}
