/*
 * 1. ��дһ��C++����, �������Ա( programmer )����
 * b)Ҫ���ܼ������������Ա( junior_programmer ) �м�����Ա ( mid_programmer )�߼�����Ա( adv_programmer)�Ĺ���
 * a)Ҫ�����ó�����ͳһ����,����������չ, ����:����, ���� �ܹ�ʦ (architect ) �Ĺ���
*/

#include <iostream>

using namespace std;

class programmer
{
public:
	virtual void getSal() = 0;
};

// ��������Ա
class junior_programmer : public programmer
{
public:
	junior_programmer(char* name, char* job, int sal)
	{
		this->name = name;
		this->job = job;
		this->sal = sal;
	}
	virtual void getSal()
	{
		cout << name << " " << job << " : " << sal << endl;
	}
private:
	char* name;
	char* job;
	int sal;
};

// �м�����Ա
class mid_programmer : public programmer
{
public:
	mid_programmer(char* name, char* job, int sal)
	{
		this->name = name;
		this->job = job;
		this->sal = sal;
	}
	virtual void getSal()
	{
		cout << name << " " << job << " : " << sal << endl;
	}
private:
	char* name;
	char* job;
	int sal;
};

// �߼�����Ա
class adv_programmer : public programmer
{
public:
	adv_programmer(char* name, char* job, int sal)
	{
		this->name = name;
		this->job = job;
		this->sal = sal;
	}
	virtual void getSal()
	{
		cout << name << " " << job << " : " << sal << endl;
	}
private:
	char* name;
	char* job;
	int sal;
};

// �ܹ�ʦ
class architect : public programmer
{
public:
	architect(char* name, char* job, int sal)
	{
		this->name = name;
		this->job = job;
		this->sal = sal;
	}
	virtual void getSal()
	{
		cout << name << " " << job << " : " << sal << endl;
	}
private:
	char* name;
	char* job;
	int sal;
};

//���㺯�����򵥵Ŀ��
void CalProgSal(programmer* base)
{
	base->getSal();
}

void main()
{
	junior_programmer jp("С��", "����", 4000);
	mid_programmer mp("С��", "�м�", 8600);
	adv_programmer ap("С��", "�߼�", 15000);
	architect ar("���Ǹ�ˮƽѧԱ", "�ܹ�ʦ", 24000);

	CalProgSal(&jp);
	CalProgSal(&mp);
	CalProgSal(&ap);
	CalProgSal(&ar);

	return;
}