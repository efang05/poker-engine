#include "Hand.h"
#include <array>
#include <vector>
#include <utility>

class HandEvaluator {
public:
    enum class HandType {
        HighCard=0,
        OnePair=1,
        TwoPair=2,
        ThreeOfAKind=3,
        Straight=4,
        Flush=5,
        FullHouse=6,
        FourOfAKind=7,
        StraightFlush=8,
        RoyalFlush=9
    };

    static HandType evaluateHand(const Hand& hand);
    static std::vector<int> getRanks(const Hand& hand);

private:
    struct HandAnalysis {
        std::array<int, 15> rankCount{};
        std::array<int, 5> suitCount{};
        std::vector<int> ranks;
        bool isSequential;
        int minRank;
        int highCard;

        HandAnalysis(const Hand& hand);
    };

    static HandAnalysis analyzeHand(const Hand& hand);

    static bool isOnePair(const HandAnalysis& analysis);
    static bool isTwoPair(const HandAnalysis& analysis);
    static bool isThreeOfAKind(const HandAnalysis& analysis);
    static bool isStraight(const HandAnalysis& analysis);
    static bool isFlush(const HandAnalysis& analysis);
    static bool isFullHouse(const HandAnalysis& analysis);
    static bool isFourOfAKind(const HandAnalysis& analysis);
    static bool isStraightFlush(const HandAnalysis& analysis);
    static bool isRoyalFlush(const HandAnalysis& analysis);
};