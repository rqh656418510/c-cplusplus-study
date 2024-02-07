#pragma once

#include <iostream>

using namespace std;

// 格式化当前时间
// 默认格式是: 2020-06-07 23:46:53
string formatCurrentTime() {
	time_t rawtime;
	struct tm* info;
	char buffer[80];

	time(&rawtime);
	info = localtime(&rawtime);
	strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", info);
	string str(buffer);
	return str;
}

// 格式化当前时间
// format: 格式字符串，例如 %Y-%m-%d %H:%M:%S
string formatCurrentTime(string format) {
	time_t rawtime;
	struct tm* info;
	char buffer[80];

	time(&rawtime);
	info = localtime(&rawtime);
	strftime(buffer, 80, format.c_str(), info);
	string str(buffer);
	return str;
}

// 判断一个年份是否为闰年
bool isLeap(int year) {
	return (year % 4 == 0 || year % 400 == 0) && (year % 100 != 0);
}

// 计算特定年份的天数
int daysOfYear(int year) {
	return isLeap(year) ? 366 : 365;
}

// 根据给定的日期，计算它在该年的第几天
int dayInYear(int year, int month, int day) {
	int DAY[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (isLeap(year)) {
		DAY[1] = 29;
	}
	for (int i = 0; i < month - 1; ++i) {
		day += DAY[i];
	}
	return day;
}

// 判断日期字符串是否合法，并分别取出日期中的年月日
// date: 日期字符串，格式是: 20211201
bool stringToDate(string date, int& year, int& month, int& day) {
	year = atoi(date.substr(0, 4).c_str());
	month = atoi(date.substr(4, 2).c_str());
	day = atoi(date.substr(6, 2).c_str());
	int DAY[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (isLeap(year)) {
		DAY[1] = 29;
	}
	return year >= 0 && month <= 12 && month > 0 && day <= DAY[month - 1] && day > 0;
}

// 计算两个日期之间的天数
// date1: 日期字符串，格式是: 20211201
// date2: 日期字符串，格式是: 20211201
// 当返回值为 -1 时，说明日期的格式不正确
int daysBetween2Date(string date1, string date2) {
	int year1, month1, day1;
	int year2, month2, day2;
	if (!stringToDate(date1, year1, month1, day1) || !stringToDate(date2, year2, month2, day2)) {
		cout << "输入的日期格式不正确";
		return -1;
	}
	if (year1 == year2 && month1 == month2) {
		return day1 > day2 ? day1 - day2 : day2 - day1;
	}
	else if (year1 == year2) {
		int d1, d2;
		d1 = dayInYear(year1, month1, day1);
		d2 = dayInYear(year2, month2, day2);
		return d1 > d2 ? d1 - d2 : d2 - d1;
	}
	else {
		// 确保year1年份比year2早
		if (year1 > year2) {
			swap(year1, year2);
			swap(month1, month2);
			swap(day1, day2);
		}
		// 计算第一个日期在该年还剩多少天
		int d1, d2, d3;
		if (isLeap(year1)) {
			d1 = 366 - dayInYear(year1, month1, day1);
		}
		else {
			d1 = 365 - dayInYear(year1, month1, day1);
		}
		// 计算第二日期在当年中的第几天
		d2 = dayInYear(year2, month2, day2);
		// 计算两个年份相隔的天数
		d3 = 0;
		for (int year = year1 + 1; year < year2; year++) {
			if (isLeap(year))
				d3 += 366;
			else
				d3 += 365;
		}
		return d1 + d2 + d3;
	}
}

// 计算期权合约的剩余时间（单位年）
// expireDate: 到期日期，格式是: 20211201
// 当返回值为 -1 时，说明期权合约已到期
// 当返回值为 0 时，说明今天是期权合约有效的最后一天
double contractRemainingTime(string expireDate) {
	string currentDate = formatCurrentTime("%Y%m%d");
	if (strcmp(currentDate.c_str(), expireDate.c_str()) > 0) {
		return -1;
	}
	int days = daysBetween2Date(currentDate, expireDate);
	return days / 365.0;
}