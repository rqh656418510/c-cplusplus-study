/*
 * 1. ������ʶ����Ż����������ͣ�
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void m_print(const int num) {
    cout << num << " ";
}

int main() {
    // ��������
    vector<int> v;

    // ��������
    v.push_back(11);
    v.push_back(12);
    v.push_back(13);
    v.push_back(14);
    v.push_back(15);

    // ��һ�ַ�ʽ����������
    vector<int>::iterator itBegin = v.begin();
    vector<int>::iterator itEnd = v.end();
    while (itBegin != itEnd) {
        cout << *(itBegin++) << " ";
    }
    cout << endl;

    // �ڶ��ַ�ʽ����������
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;

    // �����ַ�ʽ����������
    for_each(v.begin(), v.end(), m_print);

    return 0;
}