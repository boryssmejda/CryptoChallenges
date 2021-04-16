#pragma once

#include "BaseNumber.hpp"
#include "Binary.hpp"
#include <string>

namespace crypto
{
class Hex final : public BaseNumber
{
public:
    Hex(const Binary& t_binaryNumber);
    Hex(const std::string& t_numberRepresentation);

    virtual Binary getBinaryRepresentation() const override;
    virtual std::string getStringRepresentation() const override;
private:
    virtual bool isNumberCorrect() const override;
    virtual std::string convertFromBinaryToDesiredBase(const Binary& t_binaryForm) const override;
};
}// crypto

