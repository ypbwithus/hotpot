#ifndef ___LOGHELPER_H___
#define ___LOGHELPER_H___

#include <cstdio>
#include <iostream>
#include <glog/logging.h>
#include "glog/log_severity.h"
// #include <dirHelper.h>
#include <regex>
// #include "timeHelper.h"
#include <stdarg.h>
#include <thread>
#include <fstream>
#include <cstdlib>
#include <filesystem>

namespace fs = std::filesystem;

using namespace std;
using namespace google;

class logHelper
{
public:
    static bool debug;

public:
    static logHelper *GetInstance(char *argv[]);

    ~logHelper()
    {
        LOG(WARNING) << "In Destructor of logHelper";
        google::ShutdownGoogleLogging();
    }

    /// LOG_TRACE(level, fmt, ...)用法调用
    static string printfLog(const int level, const char *format, ...);

private:
    logHelper();

    /// Not defined, to prevent copying
    logHelper(const logHelper &);
    logHelper &operator=(const logHelper &other);

private:
    /// 循环文件线程
    thread *delThread;
    static void delThreadFun(void *_Pthis);

    /// 循环文件线程函数
    static void RotatingLogFiles(unsigned int filesNum, double filesSize);
};

#define LOG_TRACE(level, fmt, ...)                                     \
    do                                                                 \
    {                                                                  \
        LOG(level) << logHelper::printfLog(level, fmt, ##__VA_ARGS__); \
    } while (0)

#define SIMPLE_TRACE(fmt, ...)                     \
    do                                             \
    {                                              \
        printf("%s|%03d :: ", __func__, __LINE__); \
        printf(fmt, ##__VA_ARGS__);                \
        printf("%s", "\r\n");                      \
    } while (0)

#endif
