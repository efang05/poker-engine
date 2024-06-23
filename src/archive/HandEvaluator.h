#pragma once
#include "Hand.h"
#include <vector>

class HandEvaluator {
public:
    enum class HandType {
        HighCard, OnePair, TwoPair, ThreeOfAKind, Straight, Flush, FullHouse, FourOfAKind, StraightFlush, RoyalFlush
    };

    static HandType evaluateHand(const Hand& hand, const std::vector<Card>& communityCards);

private:
    static bool isOnePair(const std::vector<int>& rankCount);
    static bool isTwoPair(const std::vector<int>& rankCount);
    static bool isThreeOfAKind(const std::vector<int>& rankCount);
    static bool isStraight(const std::vector<int>& ranks);
    static bool isFlush(const std::vector<int>& suitCount);
    static bool isFullHouse(const std::vector<int>& rankCount);
    static bool isFourOfAKind(const std::vector<int>& rankCount);
    static bool isStraightFlush(const std::vector<int>& ranks, const std::vector<int>& suitCount);
    static bool isRoyalFlush(const std::vector<int>& ranks, const std::vector<int>& suitCount);
};