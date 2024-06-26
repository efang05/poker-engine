#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

extern int HR[32487834];

extern const std::unordered_map<std::string, int> CARDS;
extern const std::vector<std::string> HANDTYPES;

bool loadHandRanks(const char* filename);
int evalCard(int card);
int eval(const std::vector<int>& cards);

struct HandResult {
    int handType;
    int handRank;
    int value;
    std::string handName;
};

HandResult evalHand(const std::vector<std::string>& cardStrings);