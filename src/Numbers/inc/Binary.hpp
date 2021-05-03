#pragma once

#include <string>

namespace crypto
{
class Binary
{
    public:
        explicit Binary(std::string t_binaryNumberRepresentation);
        [[nodiscard]] std::string get() const;

    private:
        [[nodiscard]] bool isNumberCorrect() const;
        std::string m_number;
};
}//namespace crypto
