#pragma once

#include "BaseNumber.hpp"
#include "Binary.hpp"
#include <string>

namespace crypto
{
class Hex final: public BaseNumber
{
public:
    explicit Hex(const Binary& t_binaryNumber);
    explicit Hex(const std::string& t_numberRepresentation);

    auto getBinaryRepresentation() const -> Binary override;
    auto getStringRepresentation() const -> std::string override;
private:
    auto isNumberCorrect() const -> bool override;
    auto convertFromBinaryToDesiredBase(const Binary& t_binaryForm) const -> std::string override;
};
}// crypto
