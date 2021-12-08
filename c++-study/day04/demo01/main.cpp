/**
 * 1. ȫ�ֺ������Ա������ʹ��
 */

#include <iostream>
using namespace std;

class Test
{
public:
	int a;
	int b;

public:
	Test(int a = 0, int b = 0)
	{
		this->a = a;
		this->b = b;
	}

	~Test()
	{

	}

public:
	void printT()
	{
		cout << "a:" << a << " b: " << b << endl;
	}

	Test testAdd(Test& t2)
	{
		Test tmp(this->a + t2.a, this->b + t2.b);
		return tmp;
	}

	//t1.testAdd2(t2);
	//����һ�����ã��൱�ڷ�������
	//����t1���Ԫ�أ�this����&t1
	Test& testAdd2(Test& t2)
	{
		this->a = this->a + t2.a;
		this->b = this->b + t2.b;
		return *this; //�� *(&t1) �ֻص��� t1Ԫ��
	}
};

// ȫ�ֺ���
Test testAdd(Test& t1, Test& t2)
{
	Test tmp;
	tmp.a = t1.a + t2.a;
	tmp.b = t1.b + t2.b;
	return tmp;
}

// ȫ�ֺ���
void printT(Test* pT)
{
	cout << "a:" << pT->a << " b: " << pT->b << endl;
}

int main()
{
	Test t1(1, 2);
	Test t2(3, 4);

	// ����ȫ�ֺ���
	Test t3;
	t3 = testAdd(t1, t2);
	printT(&t3);

	// ���ó�Ա����
	Test t4 = t1.testAdd(t2); // ����������ֱ��ת����t4
	t4.printT();

	Test t5;
	t5 = t1.testAdd(t2); // �����������Ƹ�t5
	t5.printT();

	t1.testAdd2(t2); // �����ڲ�ʹ����thisָ��
	t1.printT();

	return 0;
}