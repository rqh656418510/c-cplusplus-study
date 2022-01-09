#include "datetime.h"
#include <iostream>

using namespace std;

int main() {
    // 分割字符串
    vector<string> strResult = DateUtil::split("Hello,World,!", '-');
    for (auto it = strResult.begin(); it != strResult.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;

    // 根据给定的日期，计算它是星期几
    cout << DateUtil::dayOfWeek("2022-01-07") << " ";
    cout << DateUtil::dayOfWeek("2022-01-08") << " ";
    cout << DateUtil::dayOfWeek("2022-01-09") << " ";
    cout << DateUtil::dayOfWeek("2022-01-10") << endl;

    // 根据给定的日期，判断是否为周末
    int wdays = DateUtil::dayOfWeek("2022-01-09");
    bool result = DateUtil::isWeekendDays("2022-01-09");
    cout << "wdays = " << wdays << ", isWeekend = " << (result ? "true" : "false") << endl;

    // 获取时间戳
    long timestamp = DateUtil::getTimestamp("2021-01-18 00:45:25");
    cout << "timestamp = " << timestamp << endl;

    // 判断给定的时间是否允许交易
    string currentTime;
    string timeArea;

    // timeArea = "24h";
    // timeArea = "24H";

    // timeArea = "09:00:00-10:15:00";
    // currentTime = "09:00:00";
    // currentTime = "09:05:00";
    // currentTime = "08:05:00";
    // currentTime = "10:13:00";
    // currentTime = "10:15:00";
    // currentTime = "10:16:00";

    timeArea = "21:00:00-02:30:00";
    // currentTime = "21:00:00";
    // currentTime = "22:00:00";
    currentTime = "01:00:00";
    // currentTime = "02:30:00";
    // currentTime = "02:30:01";
    // currentTime = "08:30:01";

    // timeArea = "00:00:00-00:00:00";
    // currentTime = "00:00:00";
    // currentTime = "00:00:01";

    // timeArea = "00:00:00-00:00:02";
    // currentTime = "00:00:00";
    // currentTime = "00:00:01";
    // currentTime = "00:00:03";

    // timeArea = "00:00:01-00:00:00";
    // currentTime = "00:00:02";

    // timeArea = "00:00:05-00:00:00";
    // currentTime = "00:00:02";

    bool result2 = DateUtil::checkTradingTime(currentTime, timeArea, true);
    cout << "result2 = " << (result2 ? "true" : "false") << endl;
    return 0;
}