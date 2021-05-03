#include <algorithm>
#include <ranges>

#include "spdlog/spdlog.h"

#include "Decimal.hpp"

namespace
{
auto isGreaterThanZero(const std::string& t_decimalNumber) -> bool
{
    return (t_decimalNumber != "0");
}

auto multiplyDecimalNumberByFive(std::string t_decimalNumber) -> std::string
{
    std::string multiplicationResult {""};
    multiplicationResult.reserve(t_decimalNumber.length() + 1);
    auto carry {0u};

    for (auto& currentDigit: t_decimalNumber | std::views::reverse)
    {
        const auto result = static_cast<uint8_t>(currentDigit - '0') * 5 + carry;
        carry = result / 10;
        const auto newDigit = (result % 10 + '0');
        currentDigit = static_cast<char>(newDigit);
    }

    multiplicationResult.shrink_to_fit();
    return multiplicationResult;
}

using ModuloTenRest = char;
auto divideDecimalNumberByTen(std::string& t_decimalNumber) -> ModuloTenRest
{
    const auto lastDigit = t_decimalNumber.back();
    t_decimalNumber.pop_back();

    return lastDigit;
}

using RestFromDivisionByTwo = bool;
auto getRestFromDivisionByTwo(std::string& t_decimalNumber) -> RestFromDivisionByTwo
{
    multiplyDecimalNumberByFive(t_decimalNumber);
    const auto moduloTenRest = divideDecimalNumberByTen(t_decimalNumber);

    bool isDivisibleByTwo = ('0' == moduloTenRest ? true : false);
    return isDivisibleByTwo;
}

auto multiplyByTwo(std::string t_decimalNum) -> std::string
{
    std::string finalResult;
    finalResult.reserve(t_decimalNum.length() + 1);

    auto carry {0u};
    for (auto& digit: t_decimalNum | std::views::reverse)
    {
        const auto multiplicationResult = static_cast<uint32_t>(digit - '0') * 2 + carry;
        carry = multiplicationResult / 10;
        finalResult += static_cast<char>(multiplicationResult % 10 + '0');
    }

    if (carry != 0)
    {
        finalResult += static_cast<char>(carry + '0');
    }

    std::ranges::reverse(finalResult);
    return finalResult;
}

auto calculatePowerOfTwo(uint32_t exponent) -> std::string
{
    if (exponent == 0)
    {
        return std::string {"1"};
    }
    else
    {
        return multiplyByTwo(calculatePowerOfTwo(exponent - 1));
    }
}

auto addTwoDecimalNumbers(const std::string& t_firstNumber, const std::string& t_secondNumber) -> std::string
{
    const auto additionResultSize = std::max(t_firstNumber.length(), t_secondNumber.length()) + 1;
    std::string result;
    result.reserve(additionResultSize);

    auto carry {0u};
    auto first_i = static_cast<int>(t_firstNumber.length() - 1);
    auto second_i = static_cast<int>(t_secondNumber.length() - 1);
    while (first_i >= 0 && second_i >= 0)
    {
        const auto firstNumberDigit = t_firstNumber.at(static_cast<size_t>(first_i)) - '0';
        const auto secondNumberDigit = t_secondNumber.at(static_cast<size_t>(second_i)) - '0';

        auto sum = static_cast<uint32_t>(firstNumberDigit + secondNumberDigit) + carry;
        carry = sum / 10;
        sum %= 10;

        result += static_cast<char>(sum + '0');
        --first_i;
        --second_i;
    }

    while (first_i >= 0)
    {
        const auto firstNumberDigit = static_cast<uint32_t>(t_firstNumber.at(static_cast<size_t>(first_i)) - '0');
        const auto sum = firstNumberDigit + carry;
        result += static_cast<char>(sum + '0');
        carry = sum / 10;
    }

    while (second_i >= 0)
    {
        const auto secondNumberDigit = static_cast<uint32_t>(t_secondNumber.at(static_cast<size_t>(second_i)) - '0');
        const auto sum = secondNumberDigit + carry;
        result += static_cast<char>(sum + '0');
        carry = sum / 10;
    }

    if (carry != 0)
    {
        result += static_cast<char>(carry + '0');
    }

    result.shrink_to_fit();
    std::ranges::reverse(result);

    return result;
}

auto addPowersOfTwo(const std::vector<std::string>& t_powersOfTwo) -> std::string
{
    std::string additionResult {"0"};
    for (const auto& number: t_powersOfTwo)
    {
        additionResult = addTwoDecimalNumbers(additionResult, number);
    }

    return additionResult;
}

} //namespace

crypto::Decimal::Decimal(const crypto::Binary& t_binaryRepresentation)
{
    m_numberRepresentation = convertFromBinaryToDesiredBase(t_binaryRepresentation);
}

crypto::Decimal::Decimal(const std::string& t_number)
{
    m_numberRepresentation = t_number;
    if (!isNumberCorrect())
    {
        SPDLOG_ERROR("{} is not a decimal number!", m_numberRepresentation);
        throw std::invalid_argument("Invalid Decimal Representation!");
    }
}


bool crypto::Decimal::isNumberCorrect() const
{
    if(!areDigitsBetweenZeroAndNine())
    {
        SPDLOG_ERROR("Digits of {} not between 0 and 9", m_numberRepresentation);
        return false;
    }

    if (m_numberRepresentation.length() > 1 && m_numberRepresentation.starts_with('0'))
    {
        SPDLOG_ERROR("Number {} starts with 0.", m_numberRepresentation);
        return false;
    }

    return true;
}

auto crypto::Decimal::getBinaryRepresentation() const -> crypto::Binary
{
    auto decimalForm = m_numberRepresentation;
    std::string binaryNumber {""};
    while (isGreaterThanZero(decimalForm))
    {
        const auto rest = getRestFromDivisionByTwo(decimalForm);
        binaryNumber += (rest + '0');
    }

    std::ranges::reverse(binaryNumber);
    return crypto::Binary{std::move(binaryNumber)};
}

auto crypto::Decimal::areDigitsBetweenZeroAndNine() const -> bool
{
    namespace ranges = std::ranges;
    auto isEveryDigitBetweenZeroAndNine = [](const char ch){
        return ranges::find(kAllowedDigits, ch) != kAllowedDigits.end();
    };

    return ranges::all_of(m_numberRepresentation, isEveryDigitBetweenZeroAndNine);
}

auto crypto::Decimal::convertFromBinaryToDesiredBase(const Binary& t_binaryForm) const -> std::string
{
    auto binaryNumber {t_binaryForm.get()};
    const auto numberOfOnes = std::count(binaryNumber.begin(), binaryNumber.end(), '1');
    assert (numberOfOnes >= 0);

    std::vector<std::string> calculatedPowersOfTwo;
    calculatedPowersOfTwo.reserve(static_cast<size_t>(numberOfOnes));

    for (auto exponent {0u}; auto& digit: binaryNumber | std::views::reverse)
    {
        if (digit == '1')
        {
            calculatedPowersOfTwo.emplace_back(calculatePowerOfTwo(exponent));
        }
        ++exponent;
    }

    return addPowersOfTwo(calculatedPowersOfTwo);
}

auto crypto::Decimal::getStringRepresentation() const -> std::string
{
    return m_numberRepresentation;
}

