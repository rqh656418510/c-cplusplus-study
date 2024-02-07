#pragma once

#include <iostream>
#include <time.h>
#include <chrono>
#include <sstream>
#include <cstring>
#include <vector>
#include "strUtil.h"

using namespace std;

// 日期工具类
class DateUtil {

public:

    // 格式化当前时间
    // 默认格式是: 2020-06-07 23:46:53
    static string formatCurrentTime() {
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
    static string formatCurrentTime(string format) {
        time_t rawtime;
        struct tm* info;
        char buffer[80];

        time(&rawtime);
        info = localtime(&rawtime);
        strftime(buffer, 80, format.c_str(), info);
        string str(buffer);
        return str;
    }

    // 根据给定的日期，计算它是星期几
    // date: 日期字符串，格式是: 2021-12-01
    // 返回值：1, 2, 3, 4, 5, 6, 0, 其中 0 表示星期日
    static int dayOfWeek(const string &date) {
        char c;
        int y, m, d;
        stringstream(date) >> y >> c >> m >> c >> d;
        tm t = {0, 0, 0, d, m - 1, y - 1900};
        mktime(&t);
        return t.tm_wday;
    }

    // 根据给定的日期，判断是否为周末
    // date: 日期字符串，格式是: 2021-12-01
    static bool isWeekendDays(const string &date) {
        int wday = dayOfWeek(date);
        if (wday == 6 || wday == 0) {
            return true;
        }
        return false;
    }

    // 判断一个年份是否为闰年
    static bool isLeap(int year) {
        return (year % 4 == 0 || year % 400 == 0) && (year % 100 != 0);
    }

    // 计算特定年份的天数
    static int daysOfYear(int year) {
        return isLeap(year) ? 366 : 365;
    }

    // 根据给定的日期，计算它在该年的第几天
    static int dayOfYear(int year, int month, int day) {
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
    static bool stringToDate(string date, int& year, int& month, int& day) {
        year = atoi(date.substr(0, 4).c_str());
        month = atoi(date.substr(4, 2).c_str());
        day = atoi(date.substr(6, 2).c_str());
        int DAY[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        if (isLeap(year)) {
            DAY[1] = 29;
        }
        return year >= 0 && month <= 12 && month > 0 && day <= DAY[month - 1] && day > 0;
    }

    // 获取时间戳（秒数）
    // dateTime: 日期时间字符串，格式：2021-01-08 21:27:00
    static long getTimestamp(const string &dateTime) {
        tm tm = {};
        strptime(dateTime.c_str(), "%Y-%m-%d %H:%M:%S", &tm);
        chrono::system_clock::time_point tp = chrono::system_clock::from_time_t(mktime(&tm));
        long milliseconds = chrono::duration_cast<chrono::milliseconds>(tp.time_since_epoch()).count();
        return milliseconds / 1000;
    }

    // 计算两个日期之间的天数
    // date1: 日期字符串，格式是: 20211201
    // date2: 日期字符串，格式是: 20211201
    // 当返回值为 -1 时，说明日期的格式不正确
    static int daysBetween2Date(string date1, string date2) {
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
            d1 = dayOfYear(year1, month1, day1);
            d2 = dayOfYear(year2, month2, day2);
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
                d1 = 366 - dayOfYear(year1, month1, day1);
            }
            else {
                d1 = 365 - dayOfYear(year1, month1, day1);
            }
            // 计算第二日期在当年中的第几天
            d2 = dayOfYear(year2, month2, day2);
            // 计算两个年份相隔的天数
            d3 = 0;
            for (int year = year1 + 1; year < year2; year++) {
                if (isLeap(year)) {
                    d3 += 366;
                } else {
                    d3 += 365;
                }
            }
            return d1 + d2 + d3;
        }
    }

    // 计算期权合约的剩余时间（单位年）
    // expireDate: 到期日期，格式是: 20211201
    // 当返回值为 -1 时，说明期权合约已到期
    // 当返回值为 0 时，说明今天是期权合约有效的最后一天
    static double contractRemainingTime(string expireDate) {
        string currentDate = formatCurrentTime("%Y%m%d");
        if (strcmp(currentDate.c_str(), expireDate.c_str()) > 0) {
            return -1;
        }
        int days = daysBetween2Date(currentDate, expireDate);
        return days / 365.0;
    }

    // 判断给定的当天时间是否允许进行交易
    // currentTime: 当天时间，格式：09:00:00
    // timeAreaStr：允许交易的时间范围，格式：09:00:00-10:15:00,13:30:00-15:00:00,21:00:00-02:30:00，24h表示允许24小时进行交易
    // weekendDays：周末是否允许交易
    static bool checkTradingTime(const string &currentTime, const string &timeAreaStr, bool weekendDays) {
        // 当前日期
        string currentDate = formatCurrentTime("%Y-%m-%d");

        // 判断当天是否为周末
        if (!weekendDays && isWeekendDays(currentDate)) {
            return false;
        }

        // 判断是否允许24小时交易
        if (!strcmp(timeAreaStr.c_str(), "24h") || !strcmp(timeAreaStr.c_str(), "24H")) {
            return true;
        }

        // 解析时间范围字符串，判断当天时间是否在指定的时间范围内
        vector<string> timeAreaVector = StringUtil::split(timeAreaStr, ',');
        for (auto timeArea = timeAreaVector.begin(); timeArea != timeAreaVector.end(); timeArea++) {
            vector<string> timeVector = StringUtil::split(*timeArea, '-');

            // 开始时间
            string startTime = timeVector.at(0);
            string startDateTime = currentDate + " " + startTime;
            long startTimestamp = getTimestamp(startDateTime);

            // 结束时间
            string stopTime = timeVector.at(1);
            string stopDateTime = currentDate + " " + stopTime;
            long stopTimestamp = getTimestamp(stopDateTime);
            // 如果开始时间大于结束时间（例如 13:00:00-02:16:00），则结束时间加上一天
            if (strcmp(startTime.c_str(), stopTime.c_str()) > 0) {
                stopTimestamp += 86400;
            }

            // 当天时间
            string currentDateTime = currentDate + " " + currentTime;
            long currentTimestamp = getTimestamp(currentDateTime);
            // 如果开始时间大于当天时间（例如 13:00:00-02:16:00），则当天时间加上一天
            if (strcmp(startTime.c_str(), currentTime.c_str()) > 0) {
                currentTimestamp += 86400;
            }

            // cout << "startTime = " << startTime.c_str() << ", stopTime = " << stopTime.c_str() << ", currentTime = " << currentTime.c_str() << endl;

            // 判断时间范围
            if (currentTimestamp >= startTimestamp && currentTimestamp <= stopTimestamp) {
                return true;
            }
        }
        return false;
    }

};