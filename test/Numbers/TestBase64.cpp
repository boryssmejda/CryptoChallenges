#include "Base64.hpp"
#include "Binary.hpp"
#include "gtest/gtest.h"
#include "spdlog/spdlog.h"
#include <string>

class TestBase64Constructor : public ::testing::TestWithParam<std::string>
{};

TEST_P(TestBase64Constructor, givenCorrectBase64NumberConstructorShouldNotThrow)
{
    const std::string& inputParameter = GetParam();
    EXPECT_NO_THROW(crypto::Base64{inputParameter});
}

INSTANTIATE_TEST_SUITE_P(NumberTestForCorrectInputParameters,
                        TestBase64Constructor,
                        testing::Values("0", "1", "10", "11", "100", "101", "110", "111",
                                        "1000", "1001", "1010", "1011", "1100", "1101", "1110",
                                        "1111", "10000", "10001", "10010", "10011", "10100",
                                        "2", "3", "707", "606", "12345676543210",
                                        "A", "B", "C", "D", "E", "F", "G", "H", "I",
                                        "J", "K", "L", "M", "N", "O", "P", "Q", "R",
                                        "S", "T", "U", "V", "W", "X", "Y", "Z",
                                        "a", "b", "c", "d", "e", "f", "g", "h", "i", "j",
                                        "k", "l", "m", "n", "o", "p", "q", "r", "s", "t",
                                        "u", "v", "w", "x", "y", "z",
                                        "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
                                        "+", "/",
                                        "ABCDEFGHIJKLMNOPRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"));

class TestBase64ConstructorForIncorrectParams : public ::testing::TestWithParam<std::string>
{};

TEST_P(TestBase64ConstructorForIncorrectParams, givenIncorrectBase64FormConstructorShouldThrow)
{
    const std::string& inputParameter = GetParam();
    try
    {
        crypto::Base64 base64{inputParameter};
        FAIL() << "Expected std::invalid_argument!";
    }
    catch(const std::invalid_argument& error)
    {
        EXPECT_STREQ(error.what(), "Invalid Base64 Representation!");
    }
    catch(...)
    {
        FAIL() << "Exception thrown, but expected std::invalid_argument!";
    }
}

INSTANTIATE_TEST_SUITE_P(NumberTestForIncorrectConstructorParameters,
                         TestBase64ConstructorForIncorrectParams,
                         testing::Values(":", " ", "$", "^", "*", "(", ")",
                                         "{", "}", "|", "[", "]", "-",
                                         "~", "#", "<1111>",
                                         "Aa{", "0123%$"));

class TestBase64BinaryConstructor : public ::testing::TestWithParam<crypto::Binary>
{};

TEST_P(TestBase64BinaryConstructor, givenBinaryParamToConstructorItShouldNotThrow)
{
    const auto& binary = GetParam();
    EXPECT_NO_THROW(crypto::Base64{binary});
}

INSTANTIATE_TEST_SUITE_P(TestBase64ConstructorForBinaryParameter,
                         TestBase64BinaryConstructor,
                         testing::Values(
                             crypto::Binary{"0"},
                             crypto::Binary{"1"},
                             crypto::Binary{"10"},
                             crypto::Binary{"11"},
                             crypto::Binary{"100"},
                             crypto::Binary{"1111111"},
                             crypto::Binary{"100100111"}
                         ));

struct TestBase64ParametersWhenCreatedFromBinary
{
    crypto::Binary binary;
    std::string expectedBase64Number;
};

void PrintTo(const TestBase64ParametersWhenCreatedFromBinary& t_testBase64, std::ostream* os)
{
  *os << t_testBase64.binary.get() << " | " << t_testBase64.expectedBase64Number << '\n';
}

class TestBase64RepresentationCreatedFromBinary : public ::testing::TestWithParam<TestBase64ParametersWhenCreatedFromBinary>
{};

TEST_P(TestBase64RepresentationCreatedFromBinary, givenBinaryNumberTheConstructorShouldReturnProperBase64Number)
{
    const auto& [binary, expectedBase64Number]= GetParam();
    crypto::Base64 base64{binary};

    EXPECT_EQ(expectedBase64Number, base64.getStringRepresentation());
}

INSTANTIATE_TEST_SUITE_P(TestBase64NumberRepresentation,
                         TestBase64RepresentationCreatedFromBinary,
                         testing::Values(
                            TestBase64ParametersWhenCreatedFromBinary{crypto::Binary{"0"}, std::string{"A"}},
                            TestBase64ParametersWhenCreatedFromBinary{crypto::Binary{"1"}, std::string{"B"}},
                            TestBase64ParametersWhenCreatedFromBinary{crypto::Binary{"10"}, std::string{"C"}},
                            TestBase64ParametersWhenCreatedFromBinary{crypto::Binary{"11"}, std::string{"D"}},
                            TestBase64ParametersWhenCreatedFromBinary{crypto::Binary{"100"}, std::string{"E"}},
                            TestBase64ParametersWhenCreatedFromBinary{crypto::Binary{"101"}, std::string{"F"}},
                            TestBase64ParametersWhenCreatedFromBinary{crypto::Binary{"110"}, std::string{"G"}},
                            TestBase64ParametersWhenCreatedFromBinary{crypto::Binary{"111"}, std::string{"H"}},
                            TestBase64ParametersWhenCreatedFromBinary{crypto::Binary{"1000"}, std::string{"I"}},
                            TestBase64ParametersWhenCreatedFromBinary{crypto::Binary{"1111110"}, std::string{"B+"}},
                            TestBase64ParametersWhenCreatedFromBinary{crypto::Binary{"10011110"}, std::string{"Ce"}}
                         ));

