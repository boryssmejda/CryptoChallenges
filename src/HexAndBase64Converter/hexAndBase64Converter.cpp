#include "hexAndBase64Converter.hpp"
#include "spdlog/spdlog.h"
#include <fmt/core.h>
#include <openssl/ssl.h>

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

using namespace fmt::literals;
using namespace crypto;

static const std::unordered_map<char, std::string> HEX_TO_BINARY_SYMBOLS({{'0', "0000"},
                                                                          {'1', "0001"},
                                                                          {'2', "0010"},
                                                                          {'3', "0011"},
                                                                          {'4', "0100"},
                                                                          {'5', "0101"},
                                                                          {'6', "0110"},
                                                                          {'7', "0111"},
                                                                          {'8', "1000"},
                                                                          {'9', "1001"},
                                                                          {'a', "1010"},
                                                                          {'b', "1011"},
                                                                          {'c', "1100"},
                                                                          {'d', "1101"},
                                                                          {'e', "1110"},
                                                                          {'f', "1111"}});

static const std::unordered_map<std::string, char> BINARY_TO_HEX_SYMBOLS({{"0000", '0'},
                                                                          {"0001", '1'},
                                                                          {"0010", '2'},
                                                                          {"0011", '3'},
                                                                          {"0100", '4'},
                                                                          {"0101", '5'},
                                                                          {"0110", '6'},
                                                                          {"0111", '7'},
                                                                          {"1000", '8'},
                                                                          {"1001", '9'},
                                                                          {"1010", 'a'},
                                                                          {"1011", 'b'},
                                                                          {"1100", 'c'},
                                                                          {"1101", 'd'},
                                                                          {"1110", 'e'},
                                                                          {"1111", 'f'}});

static const std::unordered_map<char, std::string> BASE64_TO_BINARY_SYMBOLS(
    {{'A', "000000"}, {'B', "000001"}, {'C', "000010"}, {'D', "000011"}, {'E', "000100"},
     {'F', "000101"}, {'G', "000110"}, {'H', "000111"}, {'I', "001000"}, {'J', "001001"},
     {'K', "001010"}, {'L', "001011"}, {'M', "001100"}, {'N', "001101"}, {'O', "001110"},
     {'P', "001111"}, {'Q', "010000"}, {'R', "010001"}, {'S', "010010"}, {'T', "010011"},
     {'U', "010100"}, {'V', "010101"}, {'W', "010110"}, {'X', "010111"}, {'Y', "011000"},
     {'Z', "011001"}, {'a', "011010"}, {'b', "011011"}, {'c', "011100"}, {'d', "011101"},
     {'e', "011110"}, {'f', "011111"}, {'g', "100000"}, {'h', "100001"}, {'i', "100010"},
     {'j', "100011"}, {'k', "100100"}, {'l', "100101"}, {'m', "100110"}, {'n', "100111"},
     {'o', "101000"}, {'p', "101001"}, {'q', "101010"}, {'r', "101011"}, {'s', "101100"},
     {'t', "101101"}, {'u', "101110"}, {'v', "101111"}, {'w', "110000"}, {'x', "110001"},
     {'y', "110010"}, {'z', "110011"}, {'0', "110100"}, {'1', "110101"}, {'2', "110110"},
     {'3', "110111"}, {'4', "111000"}, {'5', "111001"}, {'6', "111010"}, {'7', "111011"},
     {'8', "111100"}, {'9', "111101"}, {'+', "111110"}, {'/', "111111"}});

static const std::unordered_map<std::string, const char> BINARY_TO_BASE64_SYMBOLS(
    {{"000000", 'A'}, {"000001", 'B'}, {"000010", 'C'}, {"000011", 'D'}, {"000100", 'E'},
     {"000101", 'F'}, {"000110", 'G'}, {"000111", 'H'}, {"001000", 'I'}, {"001001", 'J'},
     {"001010", 'K'}, {"001011", 'L'}, {"001100", 'M'}, {"001101", 'N'}, {"001110", 'O'},
     {"001111", 'P'}, {"010000", 'Q'}, {"010001", 'R'}, {"010010", 'S'}, {"010011", 'T'},
     {"010100", 'U'}, {"010101", 'V'}, {"010110", 'W'}, {"010111", 'X'}, {"011000", 'Y'},
     {"011001", 'Z'}, {"011010", 'a'}, {"011011", 'b'}, {"011100", 'c'}, {"011101", 'd'},
     {"011110", 'e'}, {"011111", 'f'}, {"100000", 'g'}, {"100001", 'h'}, {"100010", 'i'},
     {"100011", 'j'}, {"100100", 'k'}, {"100101", 'l'}, {"100110", 'm'}, {"100111", 'n'},
     {"101000", 'o'}, {"101001", 'p'}, {"101010", 'q'}, {"101011", 'r'}, {"101100", 's'},
     {"101101", 't'}, {"101110", 'u'}, {"101111", 'v'}, {"110000", 'w'}, {"110001", 'x'},
     {"110010", 'y'}, {"110011", 'z'}, {"110100", '0'}, {"110101", '1'}, {"110110", '2'},
     {"110111", '3'}, {"111000", '4'}, {"111001", '5'}, {"111010", '6'}, {"111011", '7'},
     {"111100", '8'}, {"111101", '9'}, {"111110", '+'}, {"111111", '/'}});

struct s
{
    uint8_t upperNumber : 4;
    uint8_t lowerNumber : 4;
};

// struct size should be exactly 2 bytes
struct RelationBetweenHexAndBase64
{
    union
    {
        struct
        {
            uint8_t first_hex : 4;
            uint8_t second_hex : 4;
            uint8_t third_hex : 4;
        };

        struct
        {
            uint8_t first_base64 : 6;
            uint8_t second_base64 : 6;
        };
    };
};

namespace
{
std::string getBinaryRepresentationOfHexNumber(const std::string &t_hexNumber)
{
    constexpr auto HEX_BINARY_LENGTH = 4;

    std::string binary_representation;
    binary_representation.reserve(t_hexNumber.length() * HEX_BINARY_LENGTH);

    for (const auto ch : t_hexNumber)
    {
        binary_representation += HEX_TO_BINARY_SYMBOLS.at(ch);
    }

    return binary_representation;
}

void addLeadingZeros(std::string &t_binaryNumber)
{
    while (t_binaryNumber.length() % 6 != 0)
    {
        t_binaryNumber.insert(0, "0");
    }
}

void addLeadingZerosToBinaryForBase64Case(std::string &t_binaryNumber)
{
    while (t_binaryNumber.length() % 4 != 0)
    {
        t_binaryNumber.insert(0, "0");
    }
}

std::string convertBinaryNumberIntoBase64(const std::string &t_binaryNumber)
{
    std::string finalBase64Number;

    std::string leadingNumber = t_binaryNumber.substr(0, 6);
    if (leadingNumber != "000000")
        {
            finalBase64Number += BINARY_TO_BASE64_SYMBOLS.at(leadingNumber);
        }
    else
        {
            if (t_binaryNumber.length() == 6)
                {
                    return std::string{BINARY_TO_BASE64_SYMBOLS.at(leadingNumber)};
                }
        }

    for (std::size_t i = 6; i < t_binaryNumber.length(); i += 6)
        {
            auto base64Digit = BINARY_TO_BASE64_SYMBOLS.at(t_binaryNumber.substr(i, 6));
            finalBase64Number += base64Digit;
        }

    return finalBase64Number;
}
} // namespace

std::string crypto::convertFromHexIntoBase64(const std::string &t_hexNumber)
{
    std::string binary_representation = getBinaryRepresentationOfHexNumber(t_hexNumber);

    if (binary_representation.length() % 6 != 0)
        {
            addLeadingZeros(binary_representation);
        }

    spdlog::info("Binary Representation: {}", binary_representation);

    return convertBinaryNumberIntoBase64(binary_representation);
}

std::string getBinaryRepresentationOfBase64Number(std::string t_base64Number)
{
    std::string binaryRepresentation;
    binaryRepresentation.reserve(t_base64Number.length() * 6);

    spdlog::info("In Get Binary Representation!");
    for(const auto ch: t_base64Number)
    {
        binaryRepresentation += BASE64_TO_BINARY_SYMBOLS.at(ch);
    }

    return binaryRepresentation;
}

std::string convertBinaryNumberIntoHex(std::string t_binaryRepresentation)
{
    std::string hexNumber;

    spdlog::info("Convert Binary Into Hex: {}", t_binaryRepresentation);

    std::string leadingNumber = t_binaryRepresentation.substr(0, 4);
    if (leadingNumber != "0000")
    {
        spdlog::info("First leading number if {}", leadingNumber);
        hexNumber += BINARY_TO_HEX_SYMBOLS.at(leadingNumber);
        fmt::print("After if: {number}", "number"_a=hexNumber);
    }
    else
    {
        if (t_binaryRepresentation.length() == 4)
        {
            return std::string{BINARY_TO_HEX_SYMBOLS.at(leadingNumber)};
        }
    }

    for (std::size_t i = 4; i < t_binaryRepresentation.length(); i += 4)
    {
        auto hexDigit = BINARY_TO_HEX_SYMBOLS.at(t_binaryRepresentation.substr(i, 4));
        hexNumber += hexDigit;
    }

    return hexNumber;
}

std::string crypto::convertFromBase64IntoHex(const std::string& t_base64Number)
{
    spdlog::info("----------- Started function execution! -------");
    auto binary_representation = getBinaryRepresentationOfBase64Number(t_base64Number);

    if (binary_representation.length() % 4 != 0)
    {
        addLeadingZerosToBinaryForBase64Case(binary_representation);
    }

    spdlog::info("------ Binary Representation: {} ------", binary_representation);

    return convertBinaryNumberIntoHex(binary_representation);
}