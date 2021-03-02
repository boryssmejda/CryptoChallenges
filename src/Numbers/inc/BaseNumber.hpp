#pragma once

#include <string>

class crypto::Binary;

namespace crypto
{
class BaseNumber
{
    public:
        BaseNumber(const crypto::Binary& t_binaryRepresentation);
        BaseNumber(const std::string& t_number);

        virtual bool isNumberCorrect() const = 0;
        virtual Binary getBinaryRepresentation() const = 0;
        virtual ~BaseNumber() = default;

    private:
        std::string m_numberRepresentation;
};
}//crypto
