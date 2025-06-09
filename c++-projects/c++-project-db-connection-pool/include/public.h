#pragma once

#ifdef WIN32
    #define LOG(format, ...) printf(format, __VA_ARGS__);
#else
    #define LOG(format, ...) printf(format, ##__VA_ARGS__);
#endif
