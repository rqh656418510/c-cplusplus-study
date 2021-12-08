/*
 * 1. atomic不能与stirng类型一起使用
*/

#include <iostream>

using namespace std;

int main() {
	// C++ 编译器会出现编译错误，因为 "string" 不是可简单复制的类型（TriviallyCopyable）
	atomic<string> str{ "Hello" };
}