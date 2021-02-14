#include "hexAndBase64Converter.hpp"
#include <fmt/core.h>
#include "spdlog/spdlog.h"
#include <openssl/ssl.h>

#include <unordered_map>
#include <cstdint>
#include <vector>

using namespace crypto;

static const std::unordered_map<char, const uint8_t> hexSymbols({
    {'0', 0},
    {'1', 1},
    {'2', 2},
    {'3', 3},
    {'4', 4},
    {'5', 5},
    {'6', 6},
    {'7', 7},
    {'8', 8},
    {'9', 9},
    {'a', 10},
    {'b', 11},
    {'c', 12},
    {'d', 13},
    {'e', 14},
    {'f', 15}
});

static const std::unordered_map<char, const uint8_t> base64Symbols({
    {'A', 0},
    {'B', 1},
    {'C', 2},
    {'D', 3},
    {'E', 4},
    {'F', 5},
    {'G', 6},
    {'H', 7},
    {'I', 8},
    {'J', 9},
    {'K', 10},
    {'L', 11},
    {'M', 12},
    {'N', 13},
    {'O', 14},
    {'P', 15},
    {'Q', 16},
    {'R', 17},
    {'S', 18},
    {'T', 19},
    {'U', 20},
    {'V', 21},
    {'W', 22},
    {'X', 23},
    {'Y', 24},
    {'Z', 25},
    {'a', 26},
    {'b', 27},
    {'c', 28},
    {'d', 29},
    {'e', 30},
    {'f', 31},
    {'g', 32},
    {'h', 33},
    {'i', 34},
    {'j', 35},
    {'k', 36},
    {'l', 37},
    {'m', 38},
    {'n', 39},
    {'o', 40},
    {'p', 41},
    {'q', 42},
    {'r', 43},
    {'s', 44},
    {'t', 45},
    {'u', 46},
    {'v', 47},
    {'w', 48},
    {'x', 49},
    {'y', 50},
    {'z', 51},
    {'0', 52},
    {'1', 53},
    {'2', 54},
    {'3', 55},
    {'4', 56},
    {'5', 57},
    {'6', 58},
    {'7', 59},
    {'8', 60},
    {'9', 61},
    {'+', 62},
    {'/', 63}
});

struct s
{
    uint8_t upperNumber: 4;
    uint8_t lowerNumber: 4;
};

// struct size should be exactly 2 bytes
struct RelationBetweenHexAndBase64
{
    union
    {
        struct
        {
            uint8_t first_hex: 4;
            uint8_t second_hex: 4;
            uint8_t third_hex: 4;
        };

        struct
        {
            uint8_t first_base64: 6;
            uint8_t second_base64: 6;
        };
    };
};

class Buffer
{
    public:
    Buffer(const std::size_t t_bufferSize)
    {
        const std::size_t blockToAllocate = t_bufferSize / 3 + t_bufferSize % 3;
        m_data.reserve(blockToAllocate);
    }

    void setHexNumber(const std::size_t t_number, const std::size_t t_position)
    {
        const auto positionInVector = t_position / 3;
        const auto positionInBitField = t_position % 3;

        if(positionInBitField == 0)
        {
            m_data.at(positionInVector).third_hex = t_number;
        }
        else if(positionInBitField == 1)
        {
            m_data.at(positionInVector).second_hex = t_number;
        }
        else
        {
            m_data.at(positionInVector).first_hex = t_number;
        }
    }

    const uint8_t getBase64Number(const std::size_t t_position)
    {
        const auto positionInVector = t_position / 2;
        const auto positionInBitField = t_position % 2;

        if(positionInBitField == 0)
        {
            return m_data.at(positionInVector).second_base64;
        }
        else
        {
            return m_data.at(positionInVector).first_base64;
        }
    }

    private:
    std::vector<RelationBetweenHexAndBase64> m_data;
};

std::string crypto::convertFromHexIntoBase64(const std::string& t_hexNumber)
{
    // convert string into binary with the bitfield
    Buffer buffer(t_hexNumber.length());
    for(std::size_t index {0}; const auto ch: t_hexNumber)
    {
        const auto currentDigit = hexSymbols.at(ch);
        buffer.setHexNumber(currentDigit, index++);
    }

    return "";
}
