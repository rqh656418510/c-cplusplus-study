/**
 * 1. �̳��е����ͼ���ԭ��
 * 2. ���ͼ��ݹ�����ָ����Ҫ���������κεط���������ʹ�ù��������ࣨPublic �̳У��Ķ��������
 * 3. ͨ�����м̳У�������õ��˻����г����캯������������֮������г�Ա������������������ʵ�ʾ;߱��˻�������й��ܣ����ǻ����ܽ�������⣬���������඼���Խ��
 * 4. ֵ��һ����ǣ������֮�����������Ϳ�����Ϊ����Ķ���ʹ�ã�����ֻ��ʹ�ôӻ���̳еõ��ĳ�Ա�����ͼ��ݹ����Ƕ�̬�Ե���Ҫ����֮һ
 */

#include <iostream>

using namespace std;

// ����
class Parent {

public:
	void printParent() {
		cout << "I'm parent" << endl;
	}

private:
	int a;
};

// ���ࣨ���м̳У�
class Child : public Parent {

public:
	void printChild() {
		cout << "I'm child" << endl;
	}

private:
	int c;
};

void howToPrint(Parent* p) {
	p->printParent();
}

void howToPrint(Parent& p) {
	p.printParent();
}

int main() {
	Parent p1;
	p1.printParent();

	Child c1;
	c1.printChild();
	c1.printParent();

	// 1-1 ����ָ�����ֱ��ָ���������
	cout << "1-1" << endl;
	Parent* p2 = NULL;
	p2 = &c1;
	p2->printParent();

	// 1-2 ����ָ�����ֱ��ָ���������ָ������������
	cout << "1-2" << endl;
	howToPrint(&p1);
	howToPrint(&c1);

	// 2-1 �������ÿ���ֱ�������������
	cout << "2-1" << endl;
	Parent& p3 = c1;
	p3.printParent();

	// 2-2 �������ÿ���ֱ���������������������������
	cout << "2-2" << endl;
	howToPrint(p1);
	howToPrint(c1);

	// 3-1 ����������ֱ�ӳ�ʼ��������󣬻��Զ����ø���Ŀ������캯��
	cout << "3-1" << endl;
	Parent p4 = c1;
	p4.printParent();

	// 4-1 ����������ֱ�Ӹ�ֵ���������
	cout << "4-1" << endl;
	Parent p5;
	p5 = c1;
	p5.printParent();

	return 0;
}