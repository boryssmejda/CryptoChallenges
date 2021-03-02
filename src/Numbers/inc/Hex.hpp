#pragma once

#include <string>

namespace crypto
{
class Hex final : public crypto::BaseNumber
{
    public:
        Hex(const Binary& t_binaryNumber);
        Hex(const std::string& t_numberRepresentation);

        virtual bool isNumberCorrect() const override;
        virtual Binary getBinaryRepresentation() const override;
};
}// crypto
