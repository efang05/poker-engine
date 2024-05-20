#include "HandEvaluator.h"
#include <algorithm>

HandEvaluator::HandAnalysis::HandAnalysis(const Hand& hand)
: isSequential(true), minRank(15) {
    ranks.reserve(hand.getHand().size());

    for (const auto& card : hand.getHand()) {
        int rank = static_cast<int>(card.getRank());
        int suit = static_cast<int>(card.getSuit());
        rankCount[rank]++;
        suitCount[suit]++;
        ranks.push_back(rank);
    }

    std::sort(ranks.begin(), ranks.end());
    minRank = ranks.front();

    for (size_t i = 0; i < ranks.size() - 1; ++i) {
        if (ranks[i + 1] != ranks[i] + 1) {
            isSequential = false;
            break;
        }
    }

    if (!isSequential && ranks[0] == 2 && ranks[1] == 3 && ranks[2] == 4 && ranks[3] == 5 && ranks[4] == 14) {
        isSequential = true;
    } 
}

HandEvaluator::HandAnalysis HandEvaluator::analyzeHand(const Hand& hand) {
    return HandAnalysis(hand);
}

bool HandEvaluator::isOnePair(const HandAnalysis& analysis) {
    int pairCount = 0;
    for (const int count : analysis.rankCount) {
        if (count == 2) {
            pairCount++;
        }
    }
    return pairCount == 1;
}

bool HandEvaluator::isTwoPair(const HandAnalysis& analysis) {
    int pairCount = 0;
    for (const int count : analysis.rankCount) {
        if (count == 2) {
            pairCount++;
        }
    }
    return pairCount == 2;
}

bool HandEvaluator::isThreeOfAKind(const HandAnalysis& analysis) {
    for (const int count : analysis.rankCount) {
        if (count == 3) return true;
    }
    return false;
}

bool HandEvaluator::isStraight(const HandAnalysis& analysis) {
    return analysis.isSequential;
}

bool HandEvaluator::isFlush(const HandAnalysis& analysis) {
    for (const int count : analysis.suitCount) {
        if (count == 5) return true;
    }
    return false;
}

bool HandEvaluator::isFullHouse(const HandAnalysis& analysis) {
    bool hasThree = false;
    bool hasPair = false;
    for (const int count : analysis.rankCount) {
        if (count == 3) hasThree = true;
        if (count == 2) hasPair = true;
    }
    return hasThree && hasPair;
}

bool HandEvaluator::isFourOfAKind(const HandAnalysis& analysis) {
    for (const int count : analysis.rankCount) {
        if (count == 4) return true;
    }
    return false;
}

bool HandEvaluator::isStraightFlush(const HandAnalysis& analysis) {
    return isStraight(analysis) && isFlush(analysis);
}

bool HandEvaluator::isRoyalFlush(const HandAnalysis& analysis) {
    return analysis.minRank == 10 && isStraightFlush(analysis);
}

HandEvaluator::HandType HandEvaluator::evaluateHand(const Hand& hand) {
    HandAnalysis analysis = analyzeHand(hand);

    if (isRoyalFlush(analysis)) return HandType::RoyalFlush;
    if (isStraightFlush(analysis)) return HandType::StraightFlush;
    if (isFourOfAKind(analysis)) return HandType::FourOfAKind;
    if (isFullHouse(analysis)) return HandType::FullHouse;
    if (isFlush(analysis)) return HandType::Flush;
    if (isStraight(analysis)) return HandType::Straight;
    if (isThreeOfAKind(analysis)) return HandType::ThreeOfAKind;
    if (isTwoPair(analysis)) return HandType::TwoPair;
    if (isOnePair(analysis)) return HandType::OnePair;
    
    return HandType::HighCard;
}

std::vector<int> HandEvaluator::getRanks(const Hand& hand) {
    HandAnalysis analysis = analyzeHand(hand);
    return analysis.ranks;
}
