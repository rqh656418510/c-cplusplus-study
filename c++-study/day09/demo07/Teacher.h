#pragma once

#include <iostream>

using namespace std;

class Teacher {

public:
	Teacher();
	Teacher(int age, const char* name);
	Teacher(const Teacher& obj);
	~Teacher();

public:
	Teacher& operator=(const Teacher& obj);
	friend ostream& operator<<(ostream& out, Teacher& obj);

public:
	int getAge();
	char* getName();
	void setAge(int age);
	void setName(const char* name);

private:
	int m_age;
	char* m_name;
};