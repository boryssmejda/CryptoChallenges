#include "NumberConverter/hexAndBase64Converter.hpp"
#include "gtest/gtest.h"
#include "spdlog/spdlog.h"

#include <iostream>
#include <string>

struct TestParameters
{
    std::string input;
    std::string expectedOutput;
};

class HexIntoBase64Converter_parametrized : public ::testing::TestWithParam<TestParameters>
{};

TEST_P(HexIntoBase64Converter_parametrized, conversionFromHexIntoBase64)
{
    const TestParameters& parameters = GetParam();
    EXPECT_EQ(crypto::convertFromHexIntoBase64(parameters.input), parameters.expectedOutput);
}

INSTANTIATE_TEST_SUITE_P(TestConversion, HexIntoBase64Converter_parametrized,
    testing::Values(
        TestParameters{.input{"0"}, .expectedOutput{"A"}},
        TestParameters{.input{"1"}, .expectedOutput{"B"}},
        TestParameters{.input{"2"}, .expectedOutput{"C"}},
        TestParameters{.input{"3"}, .expectedOutput{"D"}},
        TestParameters{.input{"4"}, .expectedOutput{"E"}},
        TestParameters{.input{"5"}, .expectedOutput{"F"}},
        TestParameters{.input{"6"}, .expectedOutput{"G"}},
        TestParameters{.input{"7"}, .expectedOutput{"H"}},
        TestParameters{.input{"8"}, .expectedOutput{"I"}},
        TestParameters{.input{"9"}, .expectedOutput{"J"}},
        TestParameters{.input{"a"}, .expectedOutput{"K"}},
        TestParameters{.input{"b"}, .expectedOutput{"L"}},
        TestParameters{.input{"c"}, .expectedOutput{"M"}},
        TestParameters{.input{"d"}, .expectedOutput{"N"}},
        TestParameters{.input{"e"}, .expectedOutput{"O"}},
        TestParameters{.input{"f"}, .expectedOutput{"P"}},
        TestParameters{.input{"10"}, .expectedOutput{"Q"}},
        TestParameters{.input{"11"}, .expectedOutput{"R"}},
        TestParameters{.input{"12"}, .expectedOutput{"S"}},
        TestParameters{.input{"13"}, .expectedOutput{"T"}},
        TestParameters{.input{"14"}, .expectedOutput{"U"}},
        TestParameters{.input{"15"}, .expectedOutput{"V"}},
        TestParameters{.input{"16"}, .expectedOutput{"W"}},
        TestParameters{.input{"17"}, .expectedOutput{"X"}},
        TestParameters{.input{"18"}, .expectedOutput{"Y"}},
        TestParameters{.input{"19"}, .expectedOutput{"Z"}},
        TestParameters{.input{"1a"}, .expectedOutput{"a"}},
        TestParameters{.input{"1b"}, .expectedOutput{"b"}},
        TestParameters{.input{"1c"}, .expectedOutput{"c"}},
        TestParameters{.input{"1d"}, .expectedOutput{"d"}},
        TestParameters{.input{"1e"}, .expectedOutput{"e"}},
        TestParameters{.input{"1f"}, .expectedOutput{"f"}},
        TestParameters{.input{"49276d206b696c6c696e6720796f757220627261696e206c696b652061"
                                "20706f69736f6e6f7573206d757368726f6f6d"}, 
                                .expectedOutput{"SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t"}
        }
    )
);

TEST(TestHexAndBase64Converter, singleCharacterConversionFromBase64IntoHex) {
    EXPECT_EQ(crypto::convertFromBase64IntoHex("A"), "0");
    EXPECT_EQ(crypto::convertFromBase64IntoHex("B"), "1");
    EXPECT_EQ(crypto::convertFromBase64IntoHex("C"), "2");
    EXPECT_EQ(crypto::convertFromBase64IntoHex("D"), "3");
    EXPECT_EQ(crypto::convertFromBase64IntoHex("E"), "4");
    EXPECT_EQ(crypto::convertFromBase64IntoHex("F"), "5");
    EXPECT_EQ(crypto::convertFromBase64IntoHex("G"), "6");
    EXPECT_EQ(crypto::convertFromBase64IntoHex("H"), "7");
    EXPECT_EQ(crypto::convertFromBase64IntoHex("I"), "8");
    EXPECT_EQ(crypto::convertFromBase64IntoHex("J"), "9");
    EXPECT_EQ(crypto::convertFromBase64IntoHex("K"), "a");
    EXPECT_EQ(crypto::convertFromBase64IntoHex("L"), "b");
    EXPECT_EQ(crypto::convertFromBase64IntoHex("M"), "c");
    EXPECT_EQ(crypto::convertFromBase64IntoHex("N"), "d");
    EXPECT_EQ(crypto::convertFromBase64IntoHex("O"), "e");
    EXPECT_EQ(crypto::convertFromBase64IntoHex("P"), "f");
}

TEST(TestHexAndBase64Converter, base64CharacterIntoTwoHexChars)
{
    EXPECT_EQ(crypto::convertFromBase64IntoHex("Q"), std::string{"10"});
    EXPECT_EQ(crypto::convertFromBase64IntoHex("R"), "11");
    EXPECT_EQ(crypto::convertFromBase64IntoHex("S"), "12");
    EXPECT_EQ(crypto::convertFromBase64IntoHex("T"), "13");
    EXPECT_EQ(crypto::convertFromBase64IntoHex("U"), "14");
    EXPECT_EQ(crypto::convertFromBase64IntoHex("V"), "15");
    EXPECT_EQ(crypto::convertFromBase64IntoHex("W"), "16");
    EXPECT_EQ(crypto::convertFromBase64IntoHex("X"), "17");
    EXPECT_EQ(crypto::convertFromBase64IntoHex("Y"), "18");
    EXPECT_EQ(crypto::convertFromBase64IntoHex("Z"), "19");
    EXPECT_EQ(crypto::convertFromBase64IntoHex("a"), "1a");
    EXPECT_EQ(crypto::convertFromBase64IntoHex("b"), "1b");
    EXPECT_EQ(crypto::convertFromBase64IntoHex("c"), "1c");
    EXPECT_EQ(crypto::convertFromBase64IntoHex("d"), "1d");
    EXPECT_EQ(crypto::convertFromBase64IntoHex("e"), "1e");
    EXPECT_EQ(crypto::convertFromBase64IntoHex("f"), "1f");
}

TEST(TestHexAndBase64Converter, longBase64NumberIntoHex)
{
    std::string input{
        "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t"};
    std::string expected{
        "49276d206b696c6c696e6720796f757220627261696e206c696b652061"
        "20706f69736f6e6f7573206d757368726f6f6d"};

    ASSERT_EQ(crypto::convertFromBase64IntoHex(input), expected);
}
