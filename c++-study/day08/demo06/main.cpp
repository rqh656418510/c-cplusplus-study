/*
 * 1. unique_ptr 对象（智能指针）的使用
*/

#include <iostream>

using namespace std;

class Task {

public:
	Task(int id) {
		this->id = id;
		cout << "构造函数被调用" << endl;
	}

	~Task() {
		cout << "析构函数被调用" << endl;
	}

	int getId() {
		return this->id;
	}

private:
	int id;

};


// 使用原始指针创建 unique_ptr 对象
void create() {
	unique_ptr<Task> taskPtr(new Task(22));
	cout << "id = " << taskPtr->getId() << endl;
}


// 转移 unique_ptr 对象的所有权
void move() {
	// 通过原始指针创建taskPtr1
	unique_ptr<Task> taskPtr1(new Task(55));

	// 把taskPtr1中关联指针的所有权转移给taskPtr2
	unique_ptr<Task> taskPtr2 = move(taskPtr1);

	// taskPtr1关联指针的所有权现在转移到了taskPtr2中，现在taskPtr1关联的指针为空
	if (taskPtr1 == nullptr) {
		cout << "taskPtr1 is empty" << endl;
	}

	// taskPtr1关联指针的所有权现在转移到了taskPtr2中，现在taskPtr2关联的指针不为空
	if (taskPtr2 != nullptr) {
		cout << "taskPtr2 is not empty" << endl;
	}

	cout << taskPtr2->getId() << endl;
}


// 释放 unique_ptr 对象关联的原始指针
void release() {
	unique_ptr<Task> taskPtr1(new Task(55));

	if (taskPtr1 != nullptr) {
		cout << "taskPtr1 is not empty" << endl;
	}

	// 释放关联指针的所有权
	Task* ptr = taskPtr1.release();

	if (taskPtr1 == nullptr) {
		cout << "taskPtr1 is empty" << endl;
	}

	cout << "id = " << ptr->getId() << endl;
}

// 检查 unique_ptr 对象是否为空
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