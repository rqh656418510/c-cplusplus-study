/**
 * 1. ǿ��ѵ��ʹ�������ࡢ��ķ�װ
 */

#include <iostream>
#include "Array.h"

using namespace std;

int main() {

	// �Զ����ù��캯����ʼ������
	Array array1(5);

	// ���鸳ֵ
	for (int i = 0; i < array1.length(); i++) {
		array1.setData(i, i);
	}

	// ��ӡ����
	for (int i = 0; i < array1.length(); i++) {
		cout << "array1[" << i << "] = " << array1.getData(i) << endl;
	}

	// �Զ����ÿ������캯����ʼ������
	Array array2 = array1;

	// ��ӡ����
	for (int i = 0; i < array2.length(); i++) {
		cout << "array2[" << i << "] = " << array2.getData(i) << endl;
	}

	return 0;
}