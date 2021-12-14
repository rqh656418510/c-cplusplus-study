/*
 * 1. unique_ptr ��������ָ�룩��ʹ��
*/

#include <iostream>

using namespace std;

class Task {

public:
	Task(int id) {
		this->id = id;
		cout << "���캯��������" << endl;
	}

	~Task() {
		cout << "��������������" << endl;
	}

	int getId() {
		return this->id;
	}

private:
	int id;

};


// ʹ��ԭʼָ�봴�� unique_ptr ����
void create() {
	unique_ptr<Task> taskPtr(new Task(22));
	cout << "id = " << taskPtr->getId() << endl;
}


// ת�� unique_ptr ���������Ȩ
void move() {
	// ͨ��ԭʼָ�봴��taskPtr1
	unique_ptr<Task> taskPtr1(new Task(55));

	// ��taskPtr1�й���ָ�������Ȩת�Ƹ�taskPtr2
	unique_ptr<Task> taskPtr2 = move(taskPtr1);

	// taskPtr1����ָ�������Ȩ����ת�Ƶ���taskPtr2�У�����taskPtr1������ָ��Ϊ��
	if (taskPtr1 == nullptr) {
		cout << "taskPtr1 is empty" << endl;
	}

	// taskPtr1����ָ�������Ȩ����ת�Ƶ���taskPtr2�У�����taskPtr2������ָ�벻Ϊ��
	if (taskPtr2 != nullptr) {
		cout << "taskPtr2 is not empty" << endl;
	}

	cout << taskPtr2->getId() << endl;
}


// �ͷ� unique_ptr ���������ԭʼָ��
void release() {
	unique_ptr<Task> taskPtr1(new Task(55));

	if (taskPtr1 != nullptr) {
		cout << "taskPtr1 is not empty" << endl;
	}

	// �ͷŹ���ָ�������Ȩ
	Task* ptr = taskPtr1.release();

	if (taskPtr1 == nullptr) {
		cout << "taskPtr1 is empty" << endl;
	}

	cout << "id = " << ptr->getId() << endl;
}

// ��� unique_ptr �����Ƿ�Ϊ��
void empty() {
	unique_ptr<Task> taskPtr1;

	if (!taskPtr1) {
		cout << "taskPtr2 is empty" << endl;
	}

	if (taskPtr1 == nullptr) {
		cout << "taskPtr1 is empty" << endl;
	}

	unique_ptr<Task> taskPtr2(new Task(33));

	if (taskPtr2) {
		cout << "taskPtr2 is not empty" << endl;
	}


}

int main() {
	// create();
	// move();
	// empty();
	release();
	return 0;
}