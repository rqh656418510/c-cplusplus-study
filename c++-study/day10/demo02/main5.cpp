/*
 * 1. �쳣�������
 * a) �쳣�ӿڵ�����
*/

#include <iostream>

using namespace std;

class A {};
class B {};
class C {};
class D {};
class F {};

// �ܹ���ֻ���׳����� A��B��C��D ���������͵��쳣
void funcA() throw (A, B, C, D) {
	throw A();
}

// �����׳��κ����͵��쳣
void funcB() throw() {

}

// �����׳��κ����͵��쳣
void funcC() {
	throw B();
}

int main() {
	try {
		funcA();
	}
	catch (...) {
		cout << "�����쳣 ..." << endl;
	}
	return 0;
}