#pragma once

#include <string>
#include <stdexcept>

namespace crypto
{
    class HexNumber
    {
        public:
        explicit HexNumber(const std::string& t_number);

        private:
        std::string m_number;
    };

    class Base64Number
    {
        public:
        explicit Base64Number(const std::string& t_number);
        friend bool operator == (const Base64Number& lhs, const Base64Number& rhs);

        private:
        std::string m_number;
    };

    inline bool operator == (const Base64Number& lhs, const Base64Number& rhs)
    {
        return lhs.m_number == rhs.m_number;
    }

    std::string convertFromBase64IntoHex(const std::string& t_base64Number);
    std::string convertFromHexIntoBase64(const std::string& t_hexNumber);
};
