#include <gtest/gtest.h>
#include "HexAndBase64Converter/hexAndBase64Converter.hpp"

TEST(TestHexAndBase64Converter, singleCharacterConversionFromHexIntoBase64)
{
    //const crypto::HexNumber hex{"0"};
    //const crypto::Base64Number base64{"A"};
    EXPECT_EQ(crypto::convertFromHexIntoBase64("0"), "A");
}
