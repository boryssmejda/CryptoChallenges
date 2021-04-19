#include <array>
#include <ranges>
#include <string>
#include <string_view>
#include <utility>

#include "spdlog/spdlog.h"

#include "Base64.hpp"

namespace
{
using namespace std::literals;

static constexpr std::array kBase64BinaryRelation {
    std::make_pair('A', "000000"sv),
    std::make_pair('B', "000001"sv),
    std::make_pair('C', "000010"sv),
    std::make_pair('D', "000011"sv),
    std::make_pair('E', "000100"sv),
    std::make_pair('F', "000101"sv),
    std::make_pair('G', "000110"sv),
    std::make_pair('H', "000111"sv),
    std::make_pair('I', "001000"sv),
    std::make_pair('J', "001001"sv),
    std::make_pair('K', "001010"sv),
    std::make_pair('L', "001011"sv),
    std::make_pair('M', "001100"sv),
    std::make_pair('N', "001101"sv),
    std::make_pair('O', "001110"sv),
    std::make_pair('P', "001111"sv),
    std::make_pair('Q', "010000"sv),
    std::make_pair('R', "010001"sv),
    std::make_pair('S', "010010"sv),
    std::make_pair('T', "010011"sv),
    std::make_pair('U', "010100"sv),
    std::make_pair('V', "010101"sv),
    std::make_pair('W', "010110"sv),
    std::make_pair('X', "010111"sv),
    std::make_pair('Y', "011000"sv),
    std::make_pair('Z', "011001"sv),
    std::make_pair('a', "011010"sv),
    std::make_pair('b', "011011"sv),
    std::make_pair('c', "011100"sv),
    std::make_pair('d', "011101"sv),
    std::make_pair('e', "011110"sv),
    std::make_pair('f', "011111"sv),
    std::make_pair('g', "100000"sv),
    std::make_pair('h', "100001"sv),
    std::make_pair('i', "100010"sv),
    std::make_pair('j', "100011"sv),
    std::make_pair('k', "100100"sv),
    std::make_pair('l', "100101"sv),
    std::make_pair('m', "100110"sv),
    std::make_pair('n', "100111"sv),
    std::make_pair('o', "101000"sv),
    std::make_pair('p', "101001"sv),
    std::make_pair('q', "101010"sv),
    std::make_pair('r', "101011"sv),
    std::make_pair('s', "101100"sv),
    std::make_pair('t', "101101"sv),
    std::make_pair('u', "101110"sv),
    std::make_pair('v', "101111"sv),
    std::make_pair('w', "110000"sv),
    std::make_pair('x', "110001"sv),
    std::make_pair('y', "110010"sv),
    std::make_pair('z', "110011"sv),
    std::make_pair('0', "110100"sv),
    std::make_pair('1', "110101"sv),
    std::make_pair('2', "110110"sv),
    std::make_pair('3', "110111"sv),
    std::make_pair('4', "111000"sv),
    std::make_pair('5', "111001"sv),
    std::make_pair('6', "111010"sv),
    std::make_pair('7', "111011"sv),
    std::make_pair('8', "111100"sv),
    std::make_pair('9', "111101"sv),
    std::make_pair('+', "111110"sv),
    std::make_pair('/', "111111"sv)
};

void addLeadingZeros(std::string& t_binaryNumber)
{
    while (t_binaryNumber.length() % 6 != 0)
    {
        t_binaryNumber.insert(0, 1, '0');
    }
}

char getBase64Digit(std::string_view sixBinaryDigits)
{
    const auto element = std::ranges::find_if(kBase64BinaryRelation, [&sixBinaryDigits](const auto& p){
        const auto& [base64, binary] = p;
        return sixBinaryDigits == binary;
    });

    assert(element != kBase64BinaryRelation.end());

    const auto& [base64, binary] = *element;
    return base64;
}

std::string_view getSixBinaryDigitsForOneBase64(char t_base64Digit)
{
    auto element = std::ranges::find_if(kBase64BinaryRelation, [t_base64Digit](const auto& p){
        const auto& [base64, binary] = p;
        return base64 == t_base64Digit;
    });
    assert(element != kBase64BinaryRelation.end());

    const auto& [base64, binary] = *element;
    return binary;
}
}//namespace

crypto::Base64::Base64(const std::string& t_number)
{
    m_numberRepresentation = t_number;
    if (!isNumberCorrect())
    {
        SPDLOG_ERROR("{} is not Base64 number!", m_numberRepresentation);
        throw std::invalid_argument("Invalid Base64 Representation!");
    }
}

crypto::Base64::Base64(const Binary& t_binaryRepresentation)
{
    m_numberRepresentation = convertFromBinaryToDesiredBase(t_binaryRepresentation);
}

crypto::Binary crypto::Base64::getBinaryRepresentation() const
{
    std::string binaryForm{""};
    binaryForm.reserve(m_numberRepresentation.length()*6);

    std::ranges::for_each(m_numberRepresentation, [&binaryForm](const auto& ch){
        binaryForm += getSixBinaryDigitsForOneBase64(ch);
    });

    return crypto::Binary{binaryForm};
}

std::string crypto::Base64::getStringRepresentation() const
{
    return m_numberRepresentation;
}

bool crypto::Base64::isNumberCorrect() const
{
    auto isEveryDigitBetweenZeroAndSixtyThree = [](const char ch){
        auto isDigitBase64 = [&ch](const auto& p){
            const auto& [base64, binary] = p;
            return ch == base64;
        };
        return std::ranges::find_if(kBase64BinaryRelation,
                isDigitBase64) != kBase64BinaryRelation.end();
    };

    return std::ranges::all_of(m_numberRepresentation, isEveryDigitBetweenZeroAndSixtyThree);
}

std::string crypto::Base64::convertFromBinaryToDesiredBase(const Binary& t_binaryForm) const
{
    auto binaryNumber = t_binaryForm.get();
    addLeadingZeros(binaryNumber);

    const auto length = binaryNumber.length();
    const auto base64Length = length / 6;
    std::string base64Num {""};
    base64Num.reserve(base64Length);

    for (uint32_t pos = 0; pos < length; pos += 6)
    {
        auto sixBinaryDigits = binaryNumber.substr(pos, 6);
        base64Num += getBase64Digit(sixBinaryDigits);
    }

    return base64Num;
}

