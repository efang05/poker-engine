#include <iostream>
#include <fstream>
#include <cstring>
#include <chrono>
#include <unordered_map>
#include <vector>

using namespace std;

int HR[32487834];

// Card and hand mappings
const std::unordered_map<std::string, int> CARDS = {
    {"2c", 1}, {"2d", 2}, {"2h", 3}, {"2s", 4},
    {"3c", 5}, {"3d", 6}, {"3h", 7}, {"3s", 8},
    {"4c", 9}, {"4d", 10}, {"4h", 11}, {"4s", 12},
    {"5c", 13}, {"5d", 14}, {"5h", 15}, {"5s", 16},
    {"6c", 17}, {"6d", 18}, {"6h", 19}, {"6s", 20},
    {"7c", 21}, {"7d", 22}, {"7h", 23}, {"7s", 24},
    {"8c", 25}, {"8d", 26}, {"8h", 27}, {"8s", 28},
    {"9c", 29}, {"9d", 30}, {"9h", 31}, {"9s", 32},
    {"Tc", 33}, {"Td", 34}, {"Th", 35}, {"Ts", 36},
    {"Jc", 37}, {"Jd", 38}, {"Jh", 39}, {"Js", 40},
    {"Qc", 41}, {"Qd", 42}, {"Qh", 43}, {"Qs", 44},
    {"Kc", 45}, {"Kd", 46}, {"Kh", 47}, {"Ks", 48},
    {"Ac", 49}, {"Ad", 50}, {"Ah", 51}, {"As", 52}
};

const std::vector<std::string> HANDTYPES = {
    "invalid hand", "high card", "one pair", "two pairs",
    "three of a kind", "straight", "flush", "full house",
    "four of a kind", "straight flush"
};

bool loadHandRanks(const char* filename) {
    memset(HR, 0, sizeof(HR));
    FILE* fin = fopen(filename, "rb");
    if (!fin) {
        return false;
    }
    size_t bytesread = fread(HR, sizeof(HR), 1, fin);
    fclose(fin);
    return bytesread == 1;
}

int evalCard(int card) {
    return HR[card];
}

int eval(const std::vector<int>& cards) {
    int p = 53;
    for (int card : cards) {
        p = evalCard(p + card);
    }

    int num_cards = cards.size();
    if (num_cards == 5 || num_cards == 6) {
        p = evalCard(p);
    }

    return p;
}

struct HandResult {
    int handType;
    int handRank;
    int value;
    std::string handName;
};

HandResult evalHand(const std::vector<std::string>& cardStrings) {
    std::vector<int> cards;
    for (const auto& card : cardStrings) {
        cards.push_back(CARDS.at(card));
    }
    int p = eval(cards);
    return {
        p >> 12,
        p & 0x00000fff,
        p,
        HANDTYPES[p >> 12]
    };
}

int main() {
    const char * path = "/mnt/c/Users/eddie/Documents/Poker Engine/poker-engine/src/HandRanks.dat";

    if (!loadHandRanks(path)) {
        std::cerr << "Failed to load HandRanks.dat file\n";
        return 1;
    }

    std::vector<std::string> hand1 = {"As", "Ks", "Qs", "Js", "Ts", "3c", "5h"};
    auto result1 = evalHand(hand1);
    std::cout << "Hand Type: " << result1.handType << "\n"
              << "Hand Rank: " << result1.handRank << "\n"
              << "Value: " << result1.value << "\n"
              << "Hand Name: " << result1.handName << "\n";

    std::vector<std::string> hand2 = {"As", "Ac", "Ad", "5d", "5s"};
    auto result2 = evalHand(hand2);
    std::cout << "Hand Type: " << result2.handType << "\n"
              << "Hand Rank: " << result2.handRank << "\n"
              << "Value: " << result2.value << "\n"
              << "Hand Name: " << result2.handName << "\n";

    std::vector<std::string> hand3 = {"As", "Ac", "Ad", "5d", "5s", "2d", "2s"};
    auto result3 = evalHand(hand2);
    std::cout << "Hand Type: " << result2.handType << "\n"
              << "Hand Rank: " << result2.handRank << "\n"
              << "Value: " << result2.value << "\n"
              << "Hand Name: " << result2.handName << "\n";

    return 0;
}
