#include <array>
#include <iostream>
#include <map>
#include <string>
#include <vector>

std::vector<uint8_t> Base32Decoder(const std::string& input)
{
    constexpr static std::array<char, 32> Base32Alphabet = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                                            'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '2', '3', '4', '5', '6', '7'};
    static std::map<char, uint8_t> Base32CharToBitsMap;
    if (Base32CharToBitsMap.empty())
    {
        for (size_t i = 0; i < Base32Alphabet.size(); ++i)
        {
            Base32CharToBitsMap[Base32Alphabet[i]] = i;
        }
    }

    size_t restBits{8}, outputCnt{0};
    std::vector<uint8_t> decodedInput(input.size() * 5 / 8, 0);
    for (size_t i = 0; i < input.size(); ++i)
    {
        if (restBits >= 5)
        {
            restBits = restBits - 5;
            decodedInput[outputCnt] |= (Base32CharToBitsMap[input[i]] << restBits);
        }
        else
        {
            decodedInput[outputCnt] |= (Base32CharToBitsMap[input[i]] >> (5 - restBits));
            restBits = 8 - (5 - restBits);
            decodedInput[++outputCnt] = (Base32CharToBitsMap[input[i]] << restBits);
        }
    }

    return decodedInput;
}

int main()
{
    for (auto ch : Base32Decoder("GEZDGZTGMVTA===="))
    {
        std::cout << static_cast<char>(ch);
    }
    std::cout << "\n";
}
