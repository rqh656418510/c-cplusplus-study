#pragma once

#include <iostream>

using namespace std;

template <typename T>

class Complex {

public:
	Complex(T a, T b);
	void print();
	Complex operator+(Complex& c2);
	friend ostream& operator<< <T>(ostream& out, Complex& c1);

private:
	T a;
	T b;

};