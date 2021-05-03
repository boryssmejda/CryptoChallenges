#include <algorithm>
#include <stdexcept>

#include "spdlog/spdlog.h"

#include "Binary.hpp"


crypto::Binary::Binary(std::string t_binaryNumberRepresentation):
    m_number{std::move(t_binaryNumberRepresentation)}
{
    if(!isNumberCorrect())
    {
        SPDLOG_ERROR("Incorrect Binary Representation: {}", m_number);
        throw std::invalid_argument("Invalid Binary Representation");
    }
}

auto crypto::Binary::get() const -> std::string
{
    return m_number;
}

auto crypto::Binary::isNumberCorrect() const -> bool
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

