#pragma once

#include "BaseNumber.hpp"
#include "Binary.hpp"

namespace crypto
{
class Base64 : public crypto::BaseNumber
{
public:
    Base64(const std::string& t_base64Number);
    Base64(const Binary& t_binaryNumber);

    virtual Binary getBinaryRepresentation() const override;
    virtual std::string getStringRepresentation() const override;

private:
    virtual bool isNumberCorrect() const override;
    virtual std::string convertFromBinaryToDesiredBase(const Binary& t_binaryForm) const override;
};
}//namespace crypto

