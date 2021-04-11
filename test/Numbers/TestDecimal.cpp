#include "Decimal.hpp"
#include "gtest/gtest.h"
#include "spdlog/spdlog.h"
#include <string>


class TestDecimalForCorrectInput : public ::testing::TestWithParam<std::string>
{};

TEST_P(TestDecimalForCorrectInput, whenGivenCorrectDecimalReprConstructorShouldNotThrow)
{
    const std::string& inputParameter = GetParam();
    EXPECT_NO_THROW(crypto::Decimal{inputParameter});
}

INSTANTIATE_TEST_SUITE_P(NumberTestForCorrectInputParameters,
                        TestDecimalForCorrectInput,
                        testing::Values("0", "1", "10", "11", "100", "101", "110", "111",
                                        "1000", "1001", "1010", "1011", "1100", "1101", "1110",
                                        "1111", "10000", "10001", "10010", "10011", "10100",
                                        "2", "3", "999", "99099099099"));

class TestDecimalIncorrectConstructorParameter : public ::testing::TestWithParam<std::string>
{};

TEST_P(TestDecimalIncorrectConstructorParameter, whenGivenBadDecimalFormConstructorShouldThrow)
{
    const std::string& inputParameter = GetParam();
    try
    {
        crypto::Decimal decimal{inputParameter};
        FAIL() << "Expected std::invalid_argument!";
    }
    catch(const std::invalid_argument& error)
    {
        std::cout << error.what() << std::endl;
        EXPECT_STREQ(error.what(), "Invalid Decimal Representation!");
    }
    catch(...)
    {
        FAIL() << "Exception thrown, but expected std::invalid_argument!";
    }
}

INSTANTIATE_TEST_SUITE_P(NumberTestForIncorrectConstructorParameters,
                         TestDecimalIncorrectConstructorParameter,
                         testing::Values("o", "O", "a", "-", "/", ":", " ", "$", "^", "*", "(", ")",
                                         "{", "}", "|", "[", "]", "+", "-", "750a", "a111", "~", "#",
                                         "borys", "1o", "1O", "01", "10000000b", "<1111>", "b101",
                                         "FFF", "099"));

class TestDecimalWhenConstrParamIsOutOfRange : public ::testing::TestWithParam<std::string>
{};

TEST_P(TestDecimalWhenConstrParamIsOutOfRange, whenTooBigDecimalValueConstrShouldThrow)
{
    const std::string& inputParameter = GetParam();
    try
    {
        crypto::Decimal decimal{inputParameter};
        FAIL() << "Expected std::length_error!";
    }
    catch(const std::length_error& error)
    {
        EXPECT_STREQ(error.what(), "Too big number to fit into uint64_t!");
    }
    catch(...)
    {
        FAIL() << "Exception thrown, but expected std::length_error!";
    }
}

INSTANTIATE_TEST_SUITE_P(NumberTestForIncorrectConstructorParameters,
                         TestDecimalWhenConstrParamIsOutOfRange,
                         testing::Values(
                            "20000000000000000000",
                            "123456789012345678900"));


class TestDecimalWhenCreatedFromBinary : public ::testing::TestWithParam<crypto::Binary>
{};

TEST_P(TestDecimalWhenCreatedFromBinary, whenCreatedFromBinaryConstructorShouldNotThrow)
{
    const auto& inputParameter = GetParam();
    EXPECT_NO_THROW(crypto::Decimal{inputParameter});
}

INSTANTIATE_TEST_SUITE_P(NumberTestForCorrectInputParameters,
                        TestDecimalWhenCreatedFromBinary,
                        testing::Values(
                            crypto::Binary{"1000"},
                            crypto::Binary{"1"},
                            crypto::Binary{"0"}));


class TestDecimalWhenCreatedFromBinaryThatIsTooBig : public ::testing::TestWithParam<crypto::Binary>
{};

TEST_P(TestDecimalWhenCreatedFromBinaryThatIsTooBig, whenCreatedFromTooBigBinaryConstrShouldThrow)
{
    const auto& inputParameter = GetParam();
    try
    {
        crypto::Decimal decimal{inputParameter};
        FAIL() << "Expected std::length_error!";
    }
    catch(const std::length_error& error)
    {
        std::cout << error.what() << std::endl;
        EXPECT_STREQ(error.what(), "Out of range!");
    }
    catch(...)
    {
        FAIL() << "Exception thrown, but expected std::length_error!";
    }
}

INSTANTIATE_TEST_SUITE_P(NumberTestForCorrectInputParameters,
                        TestDecimalWhenCreatedFromBinaryThatIsTooBig,
                        testing::Values(
                            crypto::Binary{"1111111111111111111111111111111111111111111111111111111111111111111111"},
                            crypto::Binary{"11111111111111111111111111111111111111111111111111111111111111111"}));


struct DecimalTestParameters
{
    crypto::Binary binaryForm;
    std::string expectedDecimalForm;
};

class TestDecimalOutputValue : public ::testing::TestWithParam<DecimalTestParameters>
{};

TEST_P(TestDecimalOutputValue, whenGivenBinaryRepresentationShouldReturnCorrectOutput)
{
    auto& [binaryNum, expectedDecimalForm] = GetParam();
    crypto::Decimal decimal{binaryNum};

    EXPECT_EQ(expectedDecimalForm, decimal.getStringRepresentation());
}

INSTANTIATE_TEST_SUITE_P(NumberTestForCorrectInputParameters,
                        TestDecimalOutputValue,
                        testing::Values(
                            DecimalTestParameters{.binaryForm{crypto::Binary{"0"}}, .expectedDecimalForm{"0"}},
                            DecimalTestParameters{.binaryForm{crypto::Binary{"1"}}, .expectedDecimalForm{"1"}},
                            DecimalTestParameters{.binaryForm{crypto::Binary{"10"}}, .expectedDecimalForm{"2"}},
                            DecimalTestParameters{.binaryForm{crypto::Binary{"11"}}, .expectedDecimalForm{"3"}},
                            DecimalTestParameters{.binaryForm{crypto::Binary{"1111111"}}, .expectedDecimalForm{"127"}}
                        ));

