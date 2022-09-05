#ifndef ___SPDLOGHELPER_H___
#define ___SPDLOGHELPER_H___

#include "spdlog/spdlog.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/daily_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <iostream>
#include <memory>

extern std::shared_ptr<spdlog::logger> consoleLogger;
extern std::shared_ptr<spdlog::logger> currentLogger;

// spd 带行号的打印，同时输出console和文件
#define SPDDEBUG(...)                                \
    SPDLOG_LOGGER_DEBUG(consoleLogger, __VA_ARGS__); \
    SPDLOG_LOGGER_DEBUG(currentLogger, __VA_ARGS__)
#define SPDINFO(...)                                \
    SPDLOG_LOGGER_INFO(consoleLogger, __VA_ARGS__); \
    SPDLOG_LOGGER_INFO(currentLogger, __VA_ARGS__)
#define SPDWARN(...)                                \
    SPDLOG_LOGGER_WARN(consoleLogger, __VA_ARGS__); \
    SPDLOG_LOGGER_WARN(currentLogger, __VA_ARGS__)
#define SPDERROR(...)                                \
    SPDLOG_LOGGER_ERROR(consoleLogger, __VA_ARGS__); \
    SPDLOG_LOGGER_ERROR(currentLogger, __VA_ARGS__)

// #define SPDDEBUG(...)                                               \
//     SPDLOG_LOGGER_DEBUG(spdlog::default_logger_raw(), __VA_ARGS__); \
//     SPDLOG_LOGGER_DEBUG(spdlog::get("daily_logger"), __VA_ARGS__)
// #define SPDLOG(...)                                                \
//     SPDLOG_LOGGER_INFO(spdlog::default_logger_raw(), __VA_ARGS__); \
//     SPDLOG_LOGGER_INFO(spdlog::get("daily_logger"), __VA_ARGS__)
// #define SPDWARN(...)                                               \
//     SPDLOG_LOGGER_WARN(spdlog::default_logger_raw(), __VA_ARGS__); \
//     SPDLOG_LOGGER_WARN(spdlog::get("daily_logger"), __VA_ARGS__)
// #define SPDERROR(...)                                               \
//     SPDLOG_LOGGER_ERROR(spdlog::default_logger_raw(), __VA_ARGS__); \
//     SPDLOG_LOGGER_ERROR(spdlog::get("daily_logger"), __VA_ARGS__)

int spdInit();

#endif
