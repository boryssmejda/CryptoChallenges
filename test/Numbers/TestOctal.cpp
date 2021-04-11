#include "Binary.hpp"
#include "gtest/gtest.h"
#include "Octal.hpp"
#include "spdlog/spdlog.h"
#include <string>

class TestOctalConstructor : public ::testing::TestWithParam<std::string>
{};

TEST_P(TestOctalConstructor, givenCorrectOctalNumberConstructorShouldNotThrow)
{
    const std::string& inputParameter = GetParam();
    EXPECT_NO_THROW(crypto::Octal{inputParameter});
}

INSTANTIATE_TEST_SUITE_P(NumberTestForCorrectInputParameters,
                        TestOctalConstructor,
                        testing::Values("0", "1", "10", "11", "100", "101", "110", "111",
                                        "1000", "1001", "1010", "1011", "1100", "1101", "1110",
                                        "1111", "10000", "10001", "10010", "10011", "10100",
                                        "2", "3", "707", "606", "12345676543210"));

class TestOctalConstructorForIncorrectParams : public ::testing::TestWithParam<std::string>
{};

TEST_P(TestOctalConstructorForIncorrectParams, givenIncorrectOctalFormConstructorShouldThrow)
{
    const std::string& inputParameter = GetParam();
    try
    {
        crypto::Octal octal{inputParameter};
        FAIL() << "Expected std::invalid_argument!";
    }
    catch(const std::invalid_argument& error)
    {
        std::cout << error.what() << std::endl;
        EXPECT_STREQ(error.what(), "Invalid Octal Representation!");
    }
    catch(...)
    {
        FAIL() << "Exception thrown, but expected std::invalid_argument!";
    }
}

INSTANTIATE_TEST_SUITE_P(NumberTestForIncorrectConstructorParameters,
                         TestOctalConstructorForIncorrectParams,
                         testing::Values("o", "O", "a", "-", "/", ":", " ", "$", "^", "*", "(", ")",
                                         "{", "}", "|", "[", "]", "+", "-", "750a", "a111", "~", "#",
                                         "borys", "1o", "1O", "01", "10000000b", "<1111>", "b101",
                                         "FFF", "099"));

class TestOctalBinaryConstructor : public ::testing::TestWithParam<crypto::Binary>
{};

TEST_P(TestOctalBinaryConstructor, givenBinaryParamToConstructorItShouldNotThrow)
{
    const auto& binary = GetParam();
    EXPECT_NO_THROW(crypto::Octal{binary});
}

INSTANTIATE_TEST_SUITE_P(TestOctalConstructorForBinaryParameter,
                         TestOctalBinaryConstructor,
                         testing::Values(
                             crypto::Binary{"0"},
                             crypto::Binary{"1"},
                             crypto::Binary{"10"},
                             crypto::Binary{"11"},
                             crypto::Binary{"100"},
                             crypto::Binary{"1111111"}
                         ));

struct TestOctalParametersWhenCreatedFromBinary
{
    crypto::Binary binary;
    std::string expectedOctalNumber;
};

void PrintTo(const TestOctalParametersWhenCreatedFromBinary& bar, std::ostream* os)
{
  *os << bar.binary.get() << " | " << bar.expectedOctalNumber << std::endl;  // whatever needed to print bar to os
}

class TestOctalRepresentationCreatedFromBinary : public ::testing::TestWithParam<TestOctalParametersWhenCreatedFromBinary>
{};

TEST_P(TestOctalRepresentationCreatedFromBinary, givenBinaryNumberTheConstructorShouldReturnProperOctalNumber)
{
    const auto& [binary, expectedOctalNumber]= GetParam();
    crypto::Octal octal{binary};

    EXPECT_EQ(expectedOctalNumber, octal.getStringRepresentation());
}

INSTANTIATE_TEST_SUITE_P(TestOctalNumberRepresentation,
                         TestOctalRepresentationCreatedFromBinary,
                         testing::Values(
                             TestOctalParametersWhenCreatedFromBinary{crypto::Binary{"0"}, std::string{"0"}},
                             TestOctalParametersWhenCreatedFromBinary{crypto::Binary{"1"}, std::string{"1"}},
                             TestOctalParametersWhenCreatedFromBinary{crypto::Binary{"10"}, std::string{"2"}},
                             TestOctalParametersWhenCreatedFromBinary{crypto::Binary{"11"}, std::string{"3"}},
                             TestOctalParametersWhenCreatedFromBinary{crypto::Binary{"100"}, std::string{"4"}},
                             TestOctalParametersWhenCreatedFromBinary{crypto::Binary{"101"}, std::string{"5"}},
                             TestOctalParametersWhenCreatedFromBinary{crypto::Binary{"110"}, std::string{"6"}},
                             TestOctalParametersWhenCreatedFromBinary{crypto::Binary{"111"}, std::string{"7"}},
                             TestOctalParametersWhenCreatedFromBinary{crypto::Binary{"1000"}, std::string{"10"}},
                             TestOctalParametersWhenCreatedFromBinary{crypto::Binary{"1111110"}, std::string{"176"}}
                         ));
