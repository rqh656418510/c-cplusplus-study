/*
 * 1. ���ڴ���
 * a) ��ʽ����ǰ����
 * b) ������������֮�������
*/

#include <iostream>
#include "datetime.h"

using namespace std;

int main() {

	// ���ڸ�ʽ��
	cout << formatCurrentTime() << endl;
	cout << formatCurrentTime("%Y%m%d") << endl;
	cout << formatCurrentTime("%Y-%m-%d") << endl;

	// �ж������ַ����Ƿ�Ϸ������ֱ�ȡ�������е�������
	int year, month, day;
	string str = "20211202";
	// string str = "20211231";
	// string str = "20190623";
	// string str = "20180103";

	bool result = stringToDate(str, year, month, day);
	cout << "result = " << result << endl;
	cout << "date = " << str << endl;
	printf("year = %d, month = %d, day = %d\n", year, month, day);

	// ������������֮�������
	int days = daysBetween2Date("20101111", "20111111");
	cout << "��� " << days << "��" << endl;

	int days2 = daysBetween2Date("20200202", "20200131");
	cout << "��� " << days2 << "��" << endl;

	int days3 = daysBetween2Date("20230712", "20050619");
	cout << "��� " << days3 << "��" << endl;

	// double times = contractRemainingTime("20211203");
	double times = contractRemainingTime("20211202");
	cout << "contractRemainingTime = " << times << endl;

	return 0;
}