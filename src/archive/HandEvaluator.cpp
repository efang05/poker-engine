// HandEvaluator.cpp
#include "HandEvaluator.h"
#include <algorithm>
#include <array>

HandEvaluator::HandType HandEvaluator::evaluateHand(const Hand& hand, const std::vector<Card>& communityCards) {
    std::vector<Card> fullHand = hand.getCards();
    fullHand.insert(fullHand.end(), communityCards.begin(), communityCards.end());

    std::array<int, 15> rankCount{};
    std::array<int, 5> suitCount{};
    std::vector<int> ranks;

    for (const auto& card : fullHand) {
        int rank = static_cast<int>(card.getRank());
        int suit = static_cast<int>(card.getSuit());
        rankCount[rank]++;
        suitCount[suit]++;
        ranks.push_back(rank);
    }

    std::sort(ranks.begin(), ranks.end());

    if (isRoyalFlush(ranks, suitCount)) return HandType::RoyalFlush;
    if (isStraightFlush(ranks, suitCount)) return HandType::StraightFlush;
    if (isFourOfAKind(rankCount)) return HandType::FourOfAKind;
    if (isFullHouse(rankCount)) return HandType::FullHouse;
    if (isFlush(suitCount)) return HandType::Flush;
    if (isStraight(ranks)) return HandType::Straight;
    if (isThreeOfAKind(rankCount)) return HandType::ThreeOfAKind;
    if (isTwoPair(rankCount)) return HandType::TwoPair;
    if (isOnePair(rankCount)) return HandType::OnePair;

    return HandType::HighCard;
}

bool HandEvaluator::isOnePair(const std::vector<int>& rankCount) {
    int pairCount = std::count(rankCount.begin(), rankCount.end(), 2);
    return pairCount == 1;
}

bool HandEvaluator::isTwoPair(const std::vector<int>& rankCount) {
    int pairCount = std::count(rankCount.begin(), rankCount.end(), 2);
    return pairCount == 2;
}

bool HandEvaluator::isThreeOfAKind(const std::vector<int>& rankCount) {
    return std::count(rankCount.begin(), rankCount.end(), 3) == 1;
}

bool HandEvaluator::isStraight(const std::vector<int>& ranks) {
    for (size_t i = 0; i < ranks.size() - 1; ++i) {
        if (ranks[i + 1] != ranks[i] + 1) {
            return false;
        }
    }
    return true;
}

bool HandEvaluator::isFlush(const std::vector<int>& suitCount) {
    return std::count(suitCount.begin(), suitCount.end(), 5) == 1;
}

bool HandEvaluator::isFullHouse(const std::vector<int>& rankCount) {
    return std::count(rankCount.begin(), rankCount.end(), 3) == 1 && std::count(rankCount.begin(), rankCount.end(), 2) == 1;
}

bool HandEvaluator::isFourOfAKind(const std::vector<int>& rankCount) {
    return std::count(rankCount.begin(), rankCount.end(), 4) == 1;
}

bool HandEvaluator::isStraightFlush(const std::vector<int>& ranks, const std::vector<int>& suitCount) {
    return isStraight(ranks) && isFlush(suitCount);
}

bool HandEvaluator::isRoyalFlush(const std::vector<int>& ranks, const std::vector<int>& suitCount) {
    return ranks[0] == 10 && isStraightFlush(ranks, suitCount);
}