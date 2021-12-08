/**
 * 1. �Զ��������� `Array`����ʹ�����Ա�����ֱ�� `Array` ��� `[]`��`=`��`==`��`!=` �������������
 */

#include <iostream>
#include "Array.h"

using namespace std;

int main() {

	// �Զ����ù��캯��
	Array array1(5);

	for (int i = 0; i < array1.length(); i++) {
		array1[i] = i;
	}

	for (int i = 0; i < array1.length(); i++) {
		cout << "array1[" << i << "] = " << array1[i] << endl;
	}

	// �Զ����ÿ������캯�������������
	Array array2 = array1;

	for (int i = 0; i < array2.length(); i++) {
		cout << "array2[" << i << "] = " << array2[i] << endl;
	}

	// �Զ����ÿ������캯�������������
	Array array3 = array1;

	// �����Զ����ÿ������캯��������ǳ������
	// Ĭ������£������ﲻ�� "=" ������������أ����ճ�����쳣��ֹ���У�����ͬһ���ڴ�ռ䱻�ͷ����ε��£�
	array3 = array2;
	for (int i = 0; i < array3.length(); i++) {
		cout << "array3[" << i << "] = " << array3[i] << endl;
	}

	// �ж����������Ƿ���ͬ
	bool result1 = array1 == array2;
	string strResult1 = result1 ? "=" : "!=";
	cout << "array1 " << strResult1 << " array2 " << endl;

	// �ж����������Ƿ���ͬ
	bool result2 = array1 != array2;
	string strResult2 = result2 ? "!=" : "=";
	cout << "array1 " << strResult2 << " array2 " << endl;

	return 0;
}