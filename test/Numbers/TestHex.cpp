#include "Binary.hpp"
#include "Hex.hpp"
#include "gtest/gtest.h"
#include "spdlog/spdlog.h"
#include <string>

class TestHexConstructor : public ::testing::TestWithParam<std::string>
{};

TEST_P(TestHexConstructor, givenCorrectHexNumberConstructorShouldNotThrow)
{
    const std::string& inputParameter = GetParam();
    EXPECT_NO_THROW(crypto::Hex{inputParameter});
}

INSTANTIATE_TEST_SUITE_P(NumberTestForCorrectInputParameters,
                        TestHexConstructor,
                        testing::Values("0", "1", "2", "3", "4", "5", "6", "7",
                                        "8", "9", "a", "b", "c", "d", "e", "f",
                                        "10", "11", "100", "101", "110", "111",
                                        "1000", "1001", "1010", "1011", "1100",
                                        "1101", "1110", "1111", "10000", "10001",
                                        "10010", "10011", "10100", "707", "606",
                                        "12345676543210", "8080", "9abcd",
                                        "123456789abcdef"));

class TestHexConstructorForIncorrectParams : public ::testing::TestWithParam<std::string>
{};

TEST_P(TestHexConstructorForIncorrectParams, givenIncorrectHexFormConstructorShouldThrow)
{
    const std::string& inputParameter = GetParam();
    try
    {
        crypto::Hex hex{inputParameter};
        FAIL() << "Expected std::invalid_argument!";
    }
    catch(const std::invalid_argument& error)
    {
        EXPECT_STREQ(error.what(), "Invalid Hexadecimal Representation!");
    }
    catch(...)
    {
        FAIL() << "Exception thrown, but expected std::invalid_argument!";
    }
}

INSTANTIATE_TEST_SUITE_P(NumberTestForIncorrectConstructorParameters,
                         TestHexConstructorForIncorrectParams,
                         testing::Values("o", "O", "-", "/", ":", " ", "$", "^", "*", "(", ")",
                                         "{", "}", "|", "[", "]", "+", "-", "~", "#",
                                         "borys", "1o", "1O", "01", "<1111>", "g101",
                                         "FFF", "099", "xxx", "abx", "abcdefgh"
));

class TestHexBinaryConstructor : public ::testing::TestWithParam<crypto::Binary>
{};

TEST_P(TestHexBinaryConstructor, givenBinaryParamToConstructorItShouldNotThrow)
{
    const auto& binary = GetParam();
    EXPECT_NO_THROW(crypto::Hex{binary});
}

INSTANTIATE_TEST_SUITE_P(TestHexConstructorForBinaryParameter,
                         TestHexBinaryConstructor,
                         testing::Values(
                             crypto::Binary{"0"},
                             crypto::Binary{"1"},
                             crypto::Binary{"10"},
                             crypto::Binary{"11"},
                             crypto::Binary{"100"},
                             crypto::Binary{"1111111"}
));

struct TestHexParametersWhenCreatedFromBinary
{
    crypto::Binary binary;
    std::string expectedHexNumber;
};

void PrintTo(const TestHexParametersWhenCreatedFromBinary& hex, std::ostream* os)
{
  *os << hex.binary.get() << " | " << hex.expectedHexNumber << '\n';
}

class TestHexRepresentationCreatedFromBinary : public ::testing::TestWithParam<TestHexParametersWhenCreatedFromBinary>
{};

TEST_P(TestHexRepresentationCreatedFromBinary, givenBinaryNumberTheConstructorShouldReturnProperHexNumber)
{
    const auto& [binary, expectedHexNumber]= GetParam();
    crypto::Hex hex{binary};

    EXPECT_EQ(expectedHexNumber, hex.getStringRepresentation());
}

INSTANTIATE_TEST_SUITE_P(TestHexNumberRepresentation,
                         TestHexRepresentationCreatedFromBinary,
                         testing::Values(
                             TestHexParametersWhenCreatedFromBinary{crypto::Binary{"0"}, std::string{"0"}},
                             TestHexParametersWhenCreatedFromBinary{crypto::Binary{"1"}, std::string{"1"}},
                             TestHexParametersWhenCreatedFromBinary{crypto::Binary{"10"}, std::string{"2"}},
                             TestHexParametersWhenCreatedFromBinary{crypto::Binary{"11"}, std::string{"3"}},
                             TestHexParametersWhenCreatedFromBinary{crypto::Binary{"100"}, std::string{"4"}},
                             TestHexParametersWhenCreatedFromBinary{crypto::Binary{"101"}, std::string{"5"}},
                             TestHexParametersWhenCreatedFromBinary{crypto::Binary{"110"}, std::string{"6"}},
                             TestHexParametersWhenCreatedFromBinary{crypto::Binary{"111"}, std::string{"7"}},
                             TestHexParametersWhenCreatedFromBinary{crypto::Binary{"1000"}, std::string{"8"}},
                             TestHexParametersWhenCreatedFromBinary{crypto::Binary{"1001"}, std::string{"9"}},
                             TestHexParametersWhenCreatedFromBinary{crypto::Binary{"1010"}, std::string{"a"}},
                             TestHexParametersWhenCreatedFromBinary{crypto::Binary{"1011"}, std::string{"b"}},
                             TestHexParametersWhenCreatedFromBinary{crypto::Binary{"1100"}, std::string{"c"}},
                             TestHexParametersWhenCreatedFromBinary{crypto::Binary{"1101"}, std::string{"d"}},
                             TestHexParametersWhenCreatedFromBinary{crypto::Binary{"1110"}, std::string{"e"}},
                             TestHexParametersWhenCreatedFromBinary{crypto::Binary{"1111"}, std::string{"f"}},
                             TestHexParametersWhenCreatedFromBinary{crypto::Binary{"101111"}, std::string{"2f"}},
                             TestHexParametersWhenCreatedFromBinary{crypto::Binary{"10111"}, std::string{"17"}}
));

