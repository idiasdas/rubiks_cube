#pragma once

#include "rubiks_cube.h"

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/stdout_color_sinks.h"


class Log
{
public:
    static void init();

    inline static std::shared_ptr<spdlog::logger>& get_logger() {return s_logger;}

private:
    static std::shared_ptr<spdlog::logger> s_logger;

};

// Core log macros
#define LOG_TRACE(...)    Log::get_logger()->trace(__VA_ARGS__)
#define LOG_INFO(...)     Log::get_logger()->info(__VA_ARGS__)
#define LOG_WARN(...)     Log::get_logger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)    Log::get_logger()->error(__VA_ARGS__)
#define LOG_FATAL(...)    Log::get_logger()->fatal(__VA_ARGS__)
