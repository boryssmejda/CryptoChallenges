#pragma once

#include <array>
#include "BaseNumber.hpp"
#include "Binary.hpp"

namespace crypto
{
class Decimal final: public BaseNumber
{
public:
    explicit Decimal(const crypto::Binary& t_binaryRepresentation);
    explicit Decimal(const std::string& t_number);

    auto getStringRepresentation() const -> std::string override;
    auto getBinaryRepresentation() const -> Binary override;

    static constexpr std::array<char, 10> kAllowedDigits{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
private:
    auto isNumberCorrect() const -> bool override;
    auto convertFromBinaryToDesiredBase(const Binary& t_binaryForm) const -> std::string override;
    auto areDigitsBetweenZeroAndNine() const -> bool;
};
}//crypto
