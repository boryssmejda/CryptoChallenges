#pragma once

#include "BaseNumber.hpp"
#include "Binary.hpp"

namespace crypto
{
class Octal final: public BaseNumber
{
public:
    explicit Octal(const crypto::Binary& t_binaryRepresentation);
    explicit Octal(const std::string& t_number);

    auto getBinaryRepresentation() const -> Binary override;
    auto getStringRepresentation() const -> std::string override;
private:
    auto isNumberCorrect() const -> bool override;
    auto convertFromBinaryToDesiredBase(const Binary& t_binaryForm) const -> std::string override;
};
}//crypto
