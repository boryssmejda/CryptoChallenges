#include <array>
#include <ranges>
#include <string>
#include <string_view>

#include "Hex.hpp"

#include "spdlog/spdlog.h"


namespace
{
using namespace std::literals;
static constexpr std::array kHexBinaryRelation
{
        std::make_pair("0000"sv, '0'),
        std::make_pair("0001"sv, '1'),
        std::make_pair("0010"sv, '2'),
        std::make_pair("0011"sv, '3'),
        std::make_pair("0100"sv, '4'),
        std::make_pair("0101"sv, '5'),
        std::make_pair("0110"sv, '6'),
        std::make_pair("0111"sv, '7'),
        std::make_pair("1000"sv, '8'),
        std::make_pair("1001"sv, '9'),
        std::make_pair("1010"sv, 'a'),
        std::make_pair("1011"sv, 'b'),
        std::make_pair("1100"sv, 'c'),
        std::make_pair("1101"sv, 'd'),
        std::make_pair("1110"sv, 'e'),
        std::make_pair("1111"sv, 'f'),
};

std::string getFourBinaryDigitsForOneHex(const char t_hexDigit)
{
    auto predicate = [t_hexDigit](const auto& p){
        const auto& [binary, hex] = p;
        return t_hexDigit == hex;
    };
    auto element = std::ranges::find_if(kHexBinaryRelation, predicate);
    assert(element != kHexBinaryRelation.end());

    const auto [binary, hex] = *element;
    return std::string{binary};
}

void addLeadingZeros(std::string& t_binaryNumber)
{
    while (t_binaryNumber.length() % 4 != 0)
    {
        t_binaryNumber.insert(0, 1, '0');
    }
}

char getHexNumber(const std::string& t_binaryDigits)
{
    auto areDigitsEqual = [&t_binaryDigits](const auto& p){
        const auto& [binary, hex] = p;
        return t_binaryDigits == binary;
    };
    auto element = std::ranges::find_if(kHexBinaryRelation, areDigitsEqual);
    assert(element != kHexBinaryRelation.end());

    const auto& [binary, hex] = *element;
    return hex;
}

}//namespace

crypto::Hex::Hex(const crypto::Binary& t_binaryNumber)
{
    m_numberRepresentation = convertFromBinaryToDesiredBase(t_binaryNumber);
}

std::string crypto::Hex::convertFromBinaryToDesiredBase(const Binary& t_binaryForm) const
{
    auto binaryNumber = t_binaryForm.get();
    addLeadingZeros(binaryNumber);

    const auto length = binaryNumber.length();
    const auto hexLength = length / 4;
    std::string hexNum {""};
    hexNum.reserve(hexLength);

    for (uint32_t pos = 0; pos < length; pos += 4)
    {
        auto fourBinaryDigits = binaryNumber.substr(pos, 4);
        hexNum += getHexNumber(fourBinaryDigits);
    }

    return hexNum;
}

crypto::Hex::Hex(const std::string& t_numberRepresentation)
{
    m_numberRepresentation = t_numberRepresentation;
    if (!isNumberCorrect())
    {
        SPDLOG_ERROR("{} is not a hexadecimal number!", m_numberRepresentation);
        throw std::invalid_argument("Invalid Hexadecimal Representation!");
    }
}

std::string crypto::Hex::getStringRepresentation() const
{
    return m_numberRepresentation;
}

bool crypto::Hex::isNumberCorrect() const
{
    auto isEveryDigitBetweenZeroAndHexF = [](const char ch){
        auto isDigitDecimal = [&ch](const auto& p){
            const auto& [binary, decimal] = p;
            return ch == decimal;
        };
        return std::ranges::find_if(kHexBinaryRelation,
                isDigitDecimal) != kHexBinaryRelation.end();
    };

    if (std::ranges::all_of(m_numberRepresentation, isEveryDigitBetweenZeroAndHexF) != true)
    {
        return false;
    }

    if (m_numberRepresentation.starts_with('0') && m_numberRepresentation.length() > 1)
    {
        return false;
    }
    else
    {
        return true;
    }
    return true;
}
crypto::Binary crypto::Hex::getBinaryRepresentation() const
{
    std::string binaryForm {""};
    binaryForm.reserve(m_numberRepresentation.length()*4);
    std::ranges::for_each(m_numberRepresentation, [&binaryForm](const auto& ch){
        binaryForm += getFourBinaryDigitsForOneHex(ch);
    });

    return crypto::Binary{binaryForm};
}
