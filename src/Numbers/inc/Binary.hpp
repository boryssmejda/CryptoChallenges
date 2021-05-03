#pragma once

#include <string>

namespace crypto
{
class Binary
{
public:
    explicit Binary(std::string t_binaryNumberRepresentation);
    auto get() const -> std::string;

private:
    auto isNumberCorrect() const -> bool;
    std::string m_number;
};
}//namespace crypto
