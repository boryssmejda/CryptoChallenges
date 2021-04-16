#pragma once

#include "BaseNumber.hpp"
#include "Binary.hpp"

namespace crypto
{
class Octal : public BaseNumber
{
public:
    explicit Octal(const crypto::Binary& t_binaryRepresentation);
    explicit Octal(const std::string& t_number);

    virtual Binary getBinaryRepresentation() const override;
    virtual std::string getStringRepresentation() const override;
private:
    virtual bool isNumberCorrect() const override;
    virtual std::string convertFromBinaryToDesiredBase(const Binary& t_binaryForm) const override;
};
}//crypto

