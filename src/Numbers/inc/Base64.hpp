#pragma once

#include "BaseNumber.hpp"
#include "Binary.hpp"

namespace crypto
{
class Base64 final: public crypto::BaseNumber
{
public:
    explicit Base64(const std::string& t_base64Number);
    explicit Base64(const Binary& t_binaryNumber);

    auto getBinaryRepresentation() const -> Binary override;
    auto getStringRepresentation() const -> std::string override;

private:
    auto isNumberCorrect() const -> bool override;
    auto convertFromBinaryToDesiredBase(const Binary& t_binaryForm) const -> std::string override;
};
}//namespace crypto
