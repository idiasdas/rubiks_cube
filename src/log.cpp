#include "log.h"

std::shared_ptr<spdlog::logger> Log::s_logger;

void Log::init() {
    spdlog::set_pattern("[%l]:%$ %v");
    s_logger = spdlog::stdout_color_mt("Logger");
    s_logger->set_level(spdlog::level::trace);
}
