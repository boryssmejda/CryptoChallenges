#include "Binary.hpp"

#include "spdlog/spdlog.h"

#include <algorithm>
#include <stdexcept>

crypto::Binary::Binary(std::string t_binaryNumberRepresentation):
    m_number{std::move(t_binaryNumberRepresentation)}
{
    if(!isNumberCorrect())
    {
        SPDLOG_ERROR("Incorrect Binary Representation: {}", m_number);
        throw std::invalid_argument("a");
    }
}

[[nodiscard]] std::string crypto::Binary::get() const
{
    return m_number;
}

[[nodiscard]] bool crypto::Binary::isNumberCorrect() const
{
    if(!std::ranges::all_of(m_number.cbegin(), m_number.cend(),
            [](char ch){return (ch == '0' || ch == '1');}))
    {
        return false;
    }

    if(m_number.length() > 1)
    {
        return m_number.starts_with('1');
    }

    return true;
}