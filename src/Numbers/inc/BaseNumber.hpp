#pragma once

#include <string>
#include "Binary.hpp"

namespace crypto
{
class BaseNumber
{
public:
    virtual ~BaseNumber() = default;
    virtual Binary getBinaryRepresentation() const = 0;
    virtual std::string getStringRepresentation() const = 0;

protected:
    virtual bool isNumberCorrect() const = 0;
    virtual std::string convertFromBinaryToDesiredBase(const Binary& t_binaryForm) const = 0;
    std::string m_numberRepresentation{"0"};
};
}//crypto

