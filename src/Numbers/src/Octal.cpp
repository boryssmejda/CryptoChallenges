#include <algorithm>
#include <array>
#include "Octal.hpp"
#include "spdlog/spdlog.h"
#include <string_view>
#include <utility>

namespace
{
using namespace std::literals;
static constexpr std::array<std::pair<std::string_view,char>, 8> kRelationshipsBetweenBinaryAndOctalElements
{
        std::make_pair("000"sv, '0'),
        std::make_pair("001"sv, '1'),
        std::make_pair("010"sv, '2'),
        std::make_pair("011"sv, '3'),
        std::make_pair("100"sv, '4'),
        std::make_pair("101"sv, '5'),
        std::make_pair("110"sv, '6'),
        std::make_pair("111"sv, '7')
};

char getOctalNumber(const std::string& binaryNumber)
{
    auto areDigitsEqual = [&binaryNumber](const auto& p){
        const auto& [binary, octal] = p;
        return binaryNumber == binary;
    };
    auto element = std::ranges::find_if(kRelationshipsBetweenBinaryAndOctalElements, areDigitsEqual);
    assert(element != kRelationshipsBetweenBinaryAndOctalElements.end());

    const auto& [binary, octal] = *element;
    return octal;
}

std::string getBinaryTripleForGivenOctalDigit(char t_octalDigit)
{
    auto predicate = [t_octalDigit](const auto& p){
        const auto& [binary, octal] = p;
        return t_octalDigit == octal;
    };
    auto element = std::ranges::find_if(kRelationshipsBetweenBinaryAndOctalElements, predicate);
    assert(element != kRelationshipsBetweenBinaryAndOctalElements.end());

    const auto [binary, octal] = *element;
    return std::string{binary};
}

void addLeadingZeros(std::string& t_binaryNumber)
{
    while (t_binaryNumber.length() % 3 != 0)
    {
        t_binaryNumber.insert(0, 1, '0');
    }
}

}//namespace

crypto::Octal::Octal(const std::string& t_number)
{
    m_numberRepresentation = t_number;
    if (!isNumberCorrect())
    {
        SPDLOG_ERROR("{} is not an octal number!", m_numberRepresentation);
        throw std::invalid_argument("Invalid Octal Representation!");
    }
}

crypto::Octal::Octal(const crypto::Binary& t_binaryRepresentation)
{
    m_numberRepresentation = convertFromBinaryToDesiredBase(t_binaryRepresentation);
}

std::string crypto::Octal::convertFromBinaryToDesiredBase(const Binary& t_binaryForm) const
{
    auto binaryNumber = t_binaryForm.get();
    addLeadingZeros(binaryNumber);

    const auto length = binaryNumber.length();
    const auto octalLength = length / 3;
    std::string octalNum {""};
    octalNum.reserve(octalLength);

    for (uint32_t pos = 0; pos < length; pos += 3)
    {
        auto threeBinaryDigits = binaryNumber.substr(pos, 3);
        octalNum += getOctalNumber(threeBinaryDigits);
    }

    return octalNum;
}

bool crypto::Octal::isNumberCorrect() const
{
    auto isEveryDigitBetweenZeroAndSeven = [](const char ch){
        auto isDigitDecimal = [&ch](const auto& p){
            const auto& [binary, decimal] = p;
            return ch == decimal;
        };
        return std::ranges::find_if(kRelationshipsBetweenBinaryAndOctalElements,
                isDigitDecimal) != kRelationshipsBetweenBinaryAndOctalElements.end();
    };

    if (std::ranges::all_of(m_numberRepresentation, isEveryDigitBetweenZeroAndSeven) != true)
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
}

std::string crypto::Octal::getStringRepresentation() const
{
    return m_numberRepresentation;
}

crypto::Binary crypto::Octal::getBinaryRepresentation() const
{
    std::string binaryForm{""};
    binaryForm.reserve(m_numberRepresentation.length()*3);

    std::ranges::for_each(m_numberRepresentation, [&binaryForm](const auto& ch){
        binaryForm += getBinaryTripleForGivenOctalDigit(ch);
    });

    return crypto::Binary{binaryForm};
}

