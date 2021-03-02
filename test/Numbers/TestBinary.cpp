#include "Binary.hpp"

#include "gtest/gtest.h"
#include "spdlog/spdlog.h"

#include <string>

class TestBinaryForCorrectInputParametrised : public ::testing::TestWithParam<std::string>
{};

class TestBinaryForIncorrectInput : public ::testing::TestWithParam<std::string>
{};

TEST_P(TestBinaryForCorrectInputParametrised, whenGivenCorrectStringBinaryRepresentationConstructorShouldNotThrow)
{
    const std::string& inputParameter = GetParam();
    EXPECT_NO_THROW(crypto::Binary{inputParameter});
}

INSTANTIATE_TEST_SUITE_P(NumberTestForCorrectInputParameters,
                        TestBinaryForCorrectInputParametrised,
                        testing::Values("0", "1", "10", "11", "100", "101", "110", "111",
                                        "1000", "1001", "1010", "1011", "1100", "1101", "1110",
                                        "1111", "10000", "10001", "10010", "10011", "10100"));


 TEST_P(TestBinaryForIncorrectInput, whenGivenIncorrectBinaryFormThenThrowInvalidArgumentException)
 {
     const std::string& inputParameter = GetParam();
     try
     {
         crypto::Binary binary{inputParameter};
         FAIL() << "Expected std::invalid_argument!";
     }
     catch(const std::invalid_argument& error)
     {
         std::cout << error.what() << std::endl;
         EXPECT_STREQ(error.what(), "a");
     }
     catch(...)
     {
         FAIL() << "Exception thrown, but expected std::invalid_argument!";
     }
 }

 INSTANTIATE_TEST_SUITE_P(NumberTestForIncorrectConstructorParameters,
                         TestBinaryForIncorrectInput,
                         testing::Values("o", "O", "a", "-", "/", ":", " ", "$", "^", "*", "(", ")",
                                         "{", "}", "|", "[", "]", "+", "-", "2", "3", "~", "#",
                                         "borys", "1o", "1O", "01", "10000000b", "<1111>", "b101"
                        ));
