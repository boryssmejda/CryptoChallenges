#pragma once

#include <string>

namespace crypto
{
    namespace internal
    {
        bool isCorrectHexNumber(const std::string& t_number);
        bool isCorrectBase64Number(const std::string& t_number);
    }
}
