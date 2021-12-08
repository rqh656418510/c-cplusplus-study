/*
 * 1. Map���ϵ�ʹ��
*/

#include <iostream>
#include <map>

using namespace std;

int main() {
	// ����Map���ϱ���
	map<int, int> m;

	// ��һ�����ݲ��뷽ʽ
	m.insert(pair<int, int>(1, 2));
	// �ڶ������ݲ��뷽ʽ���Ƽ���
	m.insert(make_pair(3, 4));
	// ���������ݲ��뷽ʽ
	m.insert(map<int, int>::value_type(5, 6));
	// ���������ݲ��뷽ʽ
	m[7] = 8;

	// ��һ�ַ�ʽ����Map����
	for (map<int, int>::iterator it = m.begin(); it != m.end(); it++) {
		cout << "key = " << it->first << " , " << it->second << endl;
	}

	cout << endl;

	// �ڶ��ַ�ʽ����Map����
	for (auto it = m.begin(); it != m.end(); it++) {
		cout << "key = " << it->first << " , value = " << it->second << endl;
	}

	cout << endl;

	// ��ȡָ����Key
	map<int, int>::iterator item = m.find(5);
	cout << "key = " << item->first << " , value = " << item->second << endl;

	cout << endl;

	// ��һ�ַ�ʽ�ж�Key�Ƿ����
	// ���Key���ڣ�find()�����᷵��Key��Ӧ�ĵ����������Key�����ڣ�find()�����᷵��β�������end()
	if (m.find(100) == m.end()) {
		cout << "key " << 100 << " not exist" << endl;
	}

	cout << endl;

	// �ڶ��ַ�ʽ�ж�Key�Ƿ����
	// count()��������ͳ��Keyֵ��Map�г��ֵĴ�����Map��Key�ǲ������ظ��ģ�������Key���ڻ᷵��1�������ڻ᷵��0
	if (m.count(5) == 1) {
		cout << "key " << 5 << " existed" << endl;
	}

	cout << endl;

	// ɾ��ָ����Key
	m.erase(7);
	for (auto it = m.begin(); it != m.end(); it++) {
		cout << "key = " << it->first << " , value = " << it->second << endl;
	}

}