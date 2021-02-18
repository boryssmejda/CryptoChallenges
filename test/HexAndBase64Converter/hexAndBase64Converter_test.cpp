#include "HexAndBase64Converter/hexAndBase64Converter.hpp"
#include <gtest/gtest.h>

#include <iostream>

TEST(TestHexAndBase64Converter, singleCharacterConversionFromHexIntoBase64) {
    EXPECT_EQ(crypto::convertFromHexIntoBase64("0"), "A");
    EXPECT_EQ(crypto::convertFromHexIntoBase64("1"), "B");
    EXPECT_EQ(crypto::convertFromHexIntoBase64("2"), "C");
    EXPECT_EQ(crypto::convertFromHexIntoBase64("3"), "D");
    EXPECT_EQ(crypto::convertFromHexIntoBase64("4"), "E");
    EXPECT_EQ(crypto::convertFromHexIntoBase64("5"), "F");
    EXPECT_EQ(crypto::convertFromHexIntoBase64("6"), "G");
    EXPECT_EQ(crypto::convertFromHexIntoBase64("7"), "H");
    EXPECT_EQ(crypto::convertFromHexIntoBase64("8"), "I");
    EXPECT_EQ(crypto::convertFromHexIntoBase64("9"), "J");
    EXPECT_EQ(crypto::convertFromHexIntoBase64("a"), "K");
    EXPECT_EQ(crypto::convertFromHexIntoBase64("b"), "L");
    EXPECT_EQ(crypto::convertFromHexIntoBase64("c"), "M");
    EXPECT_EQ(crypto::convertFromHexIntoBase64("d"), "N");
    EXPECT_EQ(crypto::convertFromHexIntoBase64("e"), "O");
    EXPECT_EQ(crypto::convertFromHexIntoBase64("f"), "P");
}

TEST(TestHexAndBase64Converter, twoHexCharactersIntoBase64) {
    EXPECT_EQ(crypto::convertFromHexIntoBase64("10"), "Q");
    EXPECT_EQ(crypto::convertFromHexIntoBase64("11"), "R");
    EXPECT_EQ(crypto::convertFromHexIntoBase64("12"), "S");
    EXPECT_EQ(crypto::convertFromHexIntoBase64("13"), "T");
    EXPECT_EQ(crypto::convertFromHexIntoBase64("14"), "U");
    EXPECT_EQ(crypto::convertFromHexIntoBase64("15"), "V");
    EXPECT_EQ(crypto::convertFromHexIntoBase64("16"), "W");
    EXPECT_EQ(crypto::convertFromHexIntoBase64("17"), "X");
    EXPECT_EQ(crypto::convertFromHexIntoBase64("18"), "Y");
    EXPECT_EQ(crypto::convertFromHexIntoBase64("19"), "Z");
    EXPECT_EQ(crypto::convertFromHexIntoBase64("1a"), "a");
    EXPECT_EQ(crypto::convertFromHexIntoBase64("1b"), "b");
    EXPECT_EQ(crypto::convertFromHexIntoBase64("1c"), "c");
    EXPECT_EQ(crypto::convertFromHexIntoBase64("1d"), "d");
    EXPECT_EQ(crypto::convertFromHexIntoBase64("1e"), "e");
    EXPECT_EQ(crypto::convertFromHexIntoBase64("1f"), "f");
}

TEST(TestHexAndBase64Converter, longHexadecimalNumberIntoBase64) {
    std::string expected{
        "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t"};
    std::string input{
        "49276d206b696c6c696e6720796f757220627261696e206c696b652061"
        "20706f69736f6e6f7573206d757368726f6f6d"};

    ASSERT_EQ(crypto::convertFromHexIntoBase64(input), expected);
}

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
