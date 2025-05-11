#include<iostream>
#include<vector>
#include "custom_allocator.h"

using namespace std;

// �Զ�����������
class Person {

private:
    char* name;
    int age;

	// ����ַ���
    void deepCopy(const char* source) {
        if (source) {
			name = new char[strlen(source) + 1];
            strcpy(name, source);
        }
        else {
			name = nullptr;
        }
    }

public:
    // ���캯��
    Person(const char* name, int age) : age(age) {
        cout << "Person(name, age)" << endl;
        deepCopy(name);
    }

    // �������캯��
    Person(const Person& other) : age(other.age) {
		cout << "Person(const Person&)" << endl;
        deepCopy(other.name);
    }
    
    // ������ֵ�������������ԭ��
    Person& operator=(const Person& other) {
        cout << "Person& operator=(const Person&)" << endl;
		// ��ֹ�Ը�ֵ
        if (this != &other) {
            // ���ͷ�ԭ���ڴ�
            delete[] name;

            // ����������
            age = other.age;
            deepCopy(other.name);
		}
        return *this;
    }

    // ��������
    ~Person() {
        cout << "~Person()" << endl;
        delete[] name;
    }

    const char* getName() const { 
        return name; 
    }

    int getAge() const { 
        return age; 
    }

    void display() const {
		cout << "Name: " << (name ? name : "[Unnamed]") << ", Age: " << age << endl;
    }

};

// �ض�������
typedef __default_alloc_template<int> allocator_int;
typedef __default_alloc_template<Person> allocator_person;

// ���Ի�������
void test01() {
    // �����������
    srand(time(nullptr));

    vector<int, allocator_int> vec1;

    for (int i = 0; i < 10; ++i) {
        vec1.push_back(rand() % 10 + 1);
	}

	for (const int& item : vec1) {
		cout << item << " ";
    }

    cout << endl;
}

// �����Զ�������
void test02() {
    vector<Person, allocator_person> vec2;
    // ǿ��ָ����ʼ�������������ݴ�����
	vec2.reserve(5);

    vec2.push_back(Person("Jim", 18));
    vec2.push_back(Person("Peter", 23));

    for (auto it = vec2.begin(); it != vec2.end(); ++it) {
		it->display();
    }
}

int main() {
	test01();
    test02();
    return 0;
}
