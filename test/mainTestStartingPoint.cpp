#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE

#include "gtest/gtest.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/spdlog.h"

class MinimalistPrinter : public testing::EmptyTestEventListener
{
    bool m_didTheTestFail {false};

    // Called before a test starts.
    void OnTestStart([[maybe_unused]] const testing::TestInfo& test_info) override
    {
        fmt::print(".");

        static int positionHolder;
        ++positionHolder;
        if (positionHolder == 30u)
        {
            fmt::print("\n");
            positionHolder = 0;
        }

        m_didTheTestFail = false;
    }

    // Called after a failed assertion or a SUCCESS().
    void OnTestPartResult(const testing::TestPartResult& test_part_result) override
    {
        using namespace fmt::literals;
        if (test_part_result.failed())
        {
            fmt::print("\n***Failure in {file_name}:{line_number}\n{summary}\n",
                "file_name"_a = test_part_result.file_name(),
                "line_number"_a = test_part_result.line_number(),
                "summary"_a = test_part_result.summary());

            m_didTheTestFail = true;
        }
    }

    // Called after a test ends.
    void OnTestEnd([[maybe_unused]] const testing::TestInfo& test_info) override
    {
        if (m_didTheTestFail == true)
        {
            fmt::print ("\n*** Erorr in test {}.{}\n", test_info.test_suite_name(), test_info.name());
        }
    }
};

int main(int argc, char** argv)
{
    spdlog::set_pattern("[source: %s] [function: %!] [line: %#] %v");
    auto file_logger = spdlog::basic_logger_mt("file_logger", "logs/basic-log.txt");
    spdlog::set_default_logger(file_logger);

    ::testing::InitGoogleTest(&argc, argv);
    testing::TestEventListeners& listeners = testing::UnitTest::GetInstance()->listeners();
    // Adds a listener to the end.  googletest takes the ownership.
    delete listeners.Release(listeners.default_result_printer());
    listeners.Append(new MinimalistPrinter);
    return RUN_ALL_TESTS();
}
