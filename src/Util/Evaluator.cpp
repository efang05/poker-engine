#include "Evaluator.hpp"
#include <cstring>
#include <fstream>
#include <chrono>
#include <unordered_set>
#include <algorithm>

int HR[32487834];

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

HandResult evalHand(const std::vector<std::string>& cardStrings) {
    std::vector<int> cards;
    for (const auto& card : cardStrings) {
        cards.push_back(CARDS.at(card));
    }

    auto start = std::chrono::high_resolution_clock::now();
    int p = eval(cards);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    // std::cout << "Hand evaluation took " << duration << " microseconds.\n";

    return {
        p >> 12,
        p & 0x00000fff,
        p,
        HANDTYPES[p >> 12]
    };
}

// Quantile thresholds for 5, 6, and 7 card hands
const std::vector<int> quantiles_5 = {42, 89, 137, 184, 233, 281, 329, 377, 426, 474, 522, 570, 619, 667, 715, 763, 812, 860, 916, 971, 1026, 1082, 1137, 1192, 1248, 1372, 1575, 1778, 1981, 2184, 2387, 2590, 2860};
const std::vector<int> quantiles_6 = {37, 98, 151, 201, 252, 316, 366, 415, 453, 519, 571, 619, 657, 712, 753, 792, 850, 918, 986, 1049, 1098, 1168, 1222, 1265, 1397, 1559, 1744, 1925, 2119, 2299, 2469, 2633, 2860};
const std::vector<int> quantiles_7 = {7, 31, 81, 121, 165, 217, 273, 331, 381, 427, 461, 527, 581, 627, 659, 714, 758, 791, 845, 929, 1034, 1096, 1184, 1242, 1283, 1482, 1688, 1879, 2083, 2256, 2419, 2630, 2860};

// Get bucket index based on value
int getBucket(int value, const std::vector<int>& quantiles) {
    for (int i = 0; i < quantiles.size(); ++i) {
        if (value <= quantiles[i]) {
            return i + 1;
        }
    }
    return quantiles.size();
}

int countOuts(const std::vector<std::string>& hand, const std::vector<std::string>& communityCards) {
    std::unordered_set<int> currentRanks;
    for (const auto& card : hand) {
        currentRanks.insert(CARDS.at(card));
    }
    for (const auto& card : communityCards) {
        currentRanks.insert(CARDS.at(card));
    }

    int outs = 0;
    for (const auto& card : CARDS) {
        if (currentRanks.find(card.second) == currentRanks.end()) {
            std::vector<std::string> potentialHand = hand;
            potentialHand.push_back(card.first);
            HandResult currentResult = evalHand(hand);
            HandResult potentialResult = evalHand(potentialHand);
            if (potentialResult.handType > currentResult.handType) {
                outs++;
            }
        }
    }

    return outs;
}

bool isFlushDraw(const std::vector<std::string>& hand, const std::vector<std::string>& communityCards) {
    std::unordered_map<char, int> suitCount;
    for (const auto& card : hand) {
        suitCount[card.back()]++;
    }
    for (const auto& card : communityCards) {
        suitCount[card.back()]++;
    }

    for (const auto& [suit, count] : suitCount) {
        if (count == 4) {
            return true;
        }
    }

    return false;
}

bool isStraightDraw(const std::vector<std::string>& hand, const std::vector<std::string>& communityCards) {
    std::unordered_set<int> ranks;
    for (const auto& card : hand) {
        ranks.insert(CARDS.at(card) % 13);
    }
    for (const auto& card : communityCards) {
        ranks.insert(CARDS.at(card) % 13);
    }

    std::vector<int> rankVec(ranks.begin(), ranks.end());
    std::sort(rankVec.begin(), rankVec.end());

    int consecutive = 0;
    for (int i = 1; i < rankVec.size(); ++i) {
        if (rankVec[i] == rankVec[i - 1] + 1) {
            consecutive++;
            if (consecutive == 3) {
                return true;
            }
        } else {
            consecutive = 0;
        }
    }

    return false;
}

std::string encodeState(const std::vector<std::string>& hand, int handSize) {
    HandResult result = evalHand(hand);
    int outs = countOuts(hand, {});
    bool flushDraw = isFlushDraw(hand, {});
    bool straightDraw = isStraightDraw(hand, {});
    int bucket;

    if (handSize == 5) {
        bucket = getBucket(result.value, quantiles_5);
    } else if (handSize == 6) {
        bucket = getBucket(result.value, quantiles_6);
    } else {
        bucket = getBucket(result.value, quantiles_7);
    }

    std::string stateKey = std::to_string(bucket);
    stateKey += (flushDraw ? "F" : "");
    stateKey += (straightDraw ? "S" : "");
    stateKey += std::to_string(outs);

    return stateKey;
}
