#include <algorithm>
#include <array>
#include <charconv>
#include "Decimal.hpp"
#include "spdlog/spdlog.h"

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

    if (!doesNumberFitIntoUint())
    {
        SPDLOG_ERROR("{} is not in a range for uint64_t!", m_numberRepresentation);
        throw std::length_error("Too big number to fit into uint64_t!");
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

crypto::Binary crypto::Decimal::getBinaryRepresentation() const
{
    const uint64_t decimalValue = getDecimalRepresentationFromString();
    return convertFromIntegralToBinary(decimalValue);
}

uint64_t crypto::Decimal::getDecimalRepresentationFromString() const
{
    uint64_t decimalValue {0};
    if (auto [p, ec] = std::from_chars(m_numberRepresentation.data(),
        m_numberRepresentation.data() + m_numberRepresentation.size(),
        decimalValue); ec == std::errc::result_out_of_range)
    {
        SPDLOG_ERROR("Could not convert to decimal value {}. Out of range!", m_numberRepresentation);
        throw std::invalid_argument("Out of range!");
    }

    return decimalValue;
}

crypto::Binary crypto::Decimal::convertFromIntegralToBinary(uint64_t t_number) const
{
    std::string binaryRepr{20, ' '};

    if (auto [p, ec] = std::to_chars(binaryRepr.data(), binaryRepr.data() + binaryRepr.size(), t_number, 2);
        ec != std::errc{})
    {
        SPDLOG_ERROR("Could not convert {} to binary.", m_numberRepresentation);
        throw std::invalid_argument("Out of range!");
    }
    binaryRepr.shrink_to_fit();

    return Binary{std::move(binaryRepr)};
}

bool crypto::Decimal::areDigitsBetweenZeroAndNine() const
{
    auto predicate = [](char ch){
        return std::find(kAllowedDigits.begin(), kAllowedDigits.end(), ch) != kAllowedDigits.end();
    };

    if (std::all_of(m_numberRepresentation.begin(), m_numberRepresentation.end(), predicate))
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::string crypto::Decimal::convertFromBinaryToDesiredBase(const Binary& t_binaryForm) const
{
    uint64_t decimalVal {0};
    auto binaryNum = t_binaryForm.get();
    if (auto [ptr, ec] = std::from_chars(binaryNum.data(),
        binaryNum.data()+binaryNum.size(), decimalVal, 2); ec == std::errc::result_out_of_range)
    {
        SPDLOG_ERROR("Could not convert {} to decimal. Out of range!", binaryNum);
        throw std::length_error("Out of range!");
    }

    std::string decimalForm(20, 0);
    std::to_chars(decimalForm.data(), decimalForm.data()+decimalForm.size(), decimalVal, 10);
    decimalForm.erase(std::remove(decimalForm.begin(), decimalForm.end(), 0), decimalForm.end());

    return decimalForm;
}

std::string crypto::Decimal::getStringRepresentation() const
{
    return m_numberRepresentation;
}

bool crypto::Decimal::doesNumberFitIntoUint() const
{
    uint64_t decimalVal {0};
    if (auto [ptr, ec] = std::from_chars(m_numberRepresentation.data(),
        m_numberRepresentation.data() + m_numberRepresentation.size(), decimalVal, 10);
        ec == std::errc{})
    {
        return true;
    }
    else
    {
        return false;
    }
}
