#include "spdlogHelper.h"

std::shared_ptr<spdlog::logger> consoleLogger;
std::shared_ptr<spdlog::logger> currentLogger;

int spdInit()
{
    // 按文件大小
    currentLogger = spdlog::rotating_logger_mt("file_log", "logs/spdLog.txt", 1024 * 1024 * 10, 3);

    // 每天2:30 am 新建一个日志文件
    // currentLogger = spdlog::daily_logger_mt("currentLogger", "logs/spdLog.txt", 2, 30);

    // 遇到warn flush日志，防止丢失
    currentLogger->flush_on(spdlog::level::warn);
    //每三秒刷新一次
    spdlog::flush_every(std::chrono::seconds(3));

    // Set the default logger to file logger
    consoleLogger = spdlog::stdout_color_mt("console");
    spdlog::set_default_logger(consoleLogger);
    spdlog::set_level(spdlog::level::trace); // Set global log level to debug

    // change log pattern
    // %s：文件名
    // %#：行号
    // %!：函数名
    spdlog::set_pattern("%Y-%m-%d %H:%M:%S [%l] [%t] - <%s>|<%#>|<%!>,%v");

    SPDINFO("test info");
    SPDERROR("test error");

    // Release and close all loggers
    spdlog::drop_all();
}
