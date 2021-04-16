#pragma once

#include <array>
#include "BaseNumber.hpp"
#include "Binary.hpp"

namespace crypto
{
class Decimal : public BaseNumber
{
public:
    Decimal(const crypto::Binary& t_binaryRepresentation);
    Decimal(const std::string& t_number);

    virtual std::string getStringRepresentation() const override;
    virtual Binary getBinaryRepresentation() const override;

    static constexpr std::array<char, 10> kAllowedDigits{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
private:
    virtual bool isNumberCorrect() const override;
    virtual std::string convertFromBinaryToDesiredBase(const Binary& t_binaryForm) const override;
    bool areDigitsBetweenZeroAndNine() const;
    uint64_t getDecimalRepresentationFromString() const;
    Binary convertFromIntegralToBinary(uint64_t t_number) const;
    bool doesNumberFitIntoUint() const;
};
}//crypto

