#include "Hand.h"

class PokerHandEvaluator {
public:
    enum class HandType {
        HighCard,
        OnePair,
        TwoPair,
        ThreeOfAKind,
        Straight,
        Flush,
        FullHouse,
        FourOfAKind,
        StraightFlush,
        RoyalFlush
    };
    static HandType evaluateHand(const Hand& hand);

private:
    static bool isOnePair(const Hand& hand);
    static bool isTwoPair(const Hand& hand);
    static bool isThreeOfAKind(const Hand& hand);
    static bool isStraight(const Hand& hand);
    static bool isFlush(const Hand& hand);
    static bool isFullHouse(const Hand& hand);
    static bool isFourOfAKind(const Hand& hand);
    static bool isStraightFlush(const Hand& hand);
    static bool isRoyalFlush(const Hand& hand);
};