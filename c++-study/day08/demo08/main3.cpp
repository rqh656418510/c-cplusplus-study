/*
 * 1. atomic������stirng����һ��ʹ��
*/

#include <iostream>

using namespace std;

int main() {
	// C++ ����������ֱ��������Ϊ "string" ���ǿɼ򵥸��Ƶ����ͣ�TriviallyCopyable��
	atomic<string> str{ "Hello" };
}