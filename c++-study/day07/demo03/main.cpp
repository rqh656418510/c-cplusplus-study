/*
 * 1. ����ָ�������ָ��Ĳ��������ǲ�һ����
 * a) ָ��Ҳֻһ���������ͣ��� C++ ������ָ��ִ�� `++`��`--` �������Ȼ�ǺϷ���
 * b) "��̬���ø����ָ��ָ������Ķ���" �� "����ָ�벽�����Լӣ�++��" ��������ȫ��ͬ�ĸ���
 * c) ������̳и����û������κ��Լ��ĳ�Ա�����ͳ�Ա��������ô��ʱ����ָ�������ָ��Ĳ�������һ����
 * d) ָ�������ǰ���ָ����ָ�����ͽ��еģ�����ָ�������ָ��Ĳ��������ǲ�һ���ģ���Ҫ�ø���ָ���Լӣ�`++`�����Լ���`--`���ķ�ʽ����������Ķ�������
 */

#include <iostream>
using namespace std;

class Parent
{
public:
	Parent(int a = 0)
	{
		this->a = a;
	}

	virtual void print()
	{
		cout << "I'm parent" << endl;
	}

private:
	int a;
};

class Child : public Parent
{
public:

	Child(int b, int c) :Parent(0)
	{
		this->b = b;
		this->c = c;
	}

	virtual void print()
	{
		cout << "I'm child" << endl;
	}
private:
	int b;
	int c;
};

int main()
{
	Parent* parent = NULL;
	Child* child = NULL;

	Child  array[] = { Child(1, 2), Child(3,4), Child(5, 6) };
	parent = array;
	child = array;

	// ָ���Լ���������п��ܻ�������︸��ָ�������ָ��Ĳ����ǲ�һ���ģ���Ҫ�ø���ָ���Լӣ�`++`�����Լ���`--`���ķ�ʽ����������Ķ�������
	parent++;
	child++;

	parent++;
	child++;

	return 0;
}