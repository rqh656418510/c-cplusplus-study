/*
 * 1. 日期处理
 * a) 格式化当前日期
 * b) 计算两个日期之间的天数
*/

#include <iostream>
#include "datetime.h"

using namespace std;

int main() {

	// 日期格式化
	cout << formatCurrentTime() << endl;
	cout << formatCurrentTime("%Y%m%d") << endl;
	cout << formatCurrentTime("%Y-%m-%d") << endl;

	// 判断日期字符串是否合法，并分别取出日期中的年月日
	int year, month, day;
	string str = "20211202";
	// string str = "20211231";
	// string str = "20190623";
	// string str = "20180103";

	bool result = stringToDate(str, year, month, day);
	cout << "result = " << result << endl;
	cout << "date = " << str << endl;
	printf("year = %d, month = %d, day = %d\n", year, month, day);

	// 计算两个日期之间的天数
	int days = daysBetween2Date("20101111", "20111111");
	cout << "相差 " << days << "天" << endl;

	int days2 = daysBetween2Date("20200202", "20200131");
	cout << "相差 " << days2 << "天" << endl;

	int days3 = daysBetween2Date("20230712", "20050619");
	cout << "相差 " << days3 << "天" << endl;

	// double times = contractRemainingTime("20211203");
	double times = contractRemainingTime("20211202");
	cout << "contractRemainingTime = " << times << endl;

	return 0;
}