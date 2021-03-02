#pragma once

#include <string>

namespace crypto
{
class Binary
{
    public:
        explicit Binary(const std::string& t_binaryNumberRepresentation);
        std::string get() const;

    private:
        bool isNumberCorrect() const;
        std::string m_number;
};
}
