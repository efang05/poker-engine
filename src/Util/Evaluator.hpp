#ifndef EVALUATOR_HPP
#define EVALUATOR_HPP

#include <unordered_map>
#include <vector>
#include <string>
#include <cstring>

extern int HR[32487834];

struct HandResult {
    int handType;
    int handRank;
    int value;
    std::string handName;
};

bool loadHandRanks(const char* filename);
int evalCard(int card);
int eval(const std::vector<int>& cards);
HandResult evalHand(const std::vector<std::string>& cardStrings);

int countOuts(const std::vector<std::string>& hand, const std::vector<std::string>& communityCards);
bool isFlushDraw(const std::vector<std::string>& hand, const std::vector<std::string>& communityCards);
bool isStraightDraw(const std::vector<std::string>& hand, const std::vector<std::string>& communityCards);
std::string encodeState(const std::vector<std::string>& hand, int handSize);

#endif