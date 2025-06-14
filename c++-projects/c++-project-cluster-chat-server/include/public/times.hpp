#ifndef TIMES_H
#define TIMES_H

#include <boost/date_time/c_local_time_adjustor.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <chrono>
#include <iostream>
#include <sstream>
#include <string>

// 获取当前时间戳（单位：毫秒）
inline long getTimestampMs() {
    using namespace std::chrono;

    // 获取当前系统的时间点
    chrono::system_clock::time_point now = chrono::system_clock::now();
    // 转换为时间戳
    return chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch()).count();
}

// 将时间戳（单位：毫秒）格式化为系统本地时间的字符串
// timestampMs: Unix 时间戳（自 1970-01-01 00:00:00 UTC 起的毫秒数）
// formatStr: 格式化字符串，例如 "%Y-%m-%d %H:%M:%S"
inline std::string formatTimestampLocal(long timestampMs, const std::string& formatStr) {
    using namespace boost::posix_time;
    using namespace boost::gregorian;
    using boost::date_time::c_local_adjustor;

    // 构造 UTC 时间：从 epoch 加上毫秒数
    ptime epoch(date(1970, 1, 1));
    time_duration duration = milliseconds(timestampMs);
    ptime utc_time = epoch + duration;

    // 转换为系统本地时间
    typedef c_local_adjustor<ptime> local_adj;
    ptime local_time = local_adj::utc_to_local(utc_time);

    // 格式化输出
    std::ostringstream oss;
    time_facet* facet = new time_facet(formatStr.c_str());
    oss.imbue(std::locale(std::locale::classic(), facet));
    oss << local_time;

    return oss.str();
}

#endif  // TIMES_H