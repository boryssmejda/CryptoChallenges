#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE

#include "gtest/gtest.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

int main(int argc, char** argv)
{
    spdlog::set_pattern("[source: %s] [function: %!] [line: %#] %v");
    auto file_logger = spdlog::basic_logger_mt("file_logger", "logs/basic-log.txt");
    spdlog::set_default_logger(file_logger);

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
