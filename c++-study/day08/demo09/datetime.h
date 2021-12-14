#pragma once

#include <iostream>

using namespace std;

// ��ʽ����ǰʱ��
// Ĭ�ϸ�ʽ��: 2020-06-07 23:46:53
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

// ��ʽ����ǰʱ��
// format: ��ʽ�ַ��������� %Y-%m-%d %H:%M:%S
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

// �ж�һ������Ƿ�Ϊ����
bool isLeap(int year) {
	return (year % 4 == 0 || year % 400 == 0) && (year % 100 != 0);
}

// �����ض���ݵ�����
int daysOfYear(int year) {
	return isLeap(year) ? 366 : 365;
}

// ���ݸ��������ڣ��������ڸ���ĵڼ���
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

// �ж������ַ����Ƿ�Ϸ������ֱ�ȡ�������е�������
// date: �����ַ�������ʽ��: 20211201
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

// ������������֮�������
// date1: �����ַ�������ʽ��: 20211201
// date2: �����ַ�������ʽ��: 20211201
// ������ֵΪ -1 ʱ��˵�����ڵĸ�ʽ����ȷ
int daysBetween2Date(string date1, string date2) {
	int year1, month1, day1;
	int year2, month2, day2;
	if (!stringToDate(date1, year1, month1, day1) || !stringToDate(date2, year2, month2, day2)) {
		cout << "��������ڸ�ʽ����ȷ";
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
		// ȷ��year1��ݱ�year2��
		if (year1 > year2) {
			swap(year1, year2);
			swap(month1, month2);
			swap(day1, day2);
		}
		// �����һ�������ڸ��껹ʣ������
		int d1, d2, d3;
		if (isLeap(year1)) {
			d1 = 366 - dayInYear(year1, month1, day1);
		}
		else {
			d1 = 365 - dayInYear(year1, month1, day1);
		}
		// ����ڶ������ڵ����еĵڼ���
		d2 = dayInYear(year2, month2, day2);
		// ��������������������
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

// ������Ȩ��Լ��ʣ��ʱ�䣨��λ�꣩
// expireDate: �������ڣ���ʽ��: 20211201
// ������ֵΪ -1 ʱ��˵����Ȩ��Լ�ѵ���
// ������ֵΪ 0 ʱ��˵����������Ȩ��Լ��Ч�����һ��
double contractRemainingTime(string expireDate) {
	string currentDate = formatCurrentTime("%Y%m%d");
	if (strcmp(currentDate.c_str(), expireDate.c_str()) > 0) {
		return -1;
	}
	int days = daysBetween2Date(currentDate, expireDate);
	return days / 365.0;
}