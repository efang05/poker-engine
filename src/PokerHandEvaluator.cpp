#include <PokerHandEvaluator.h>

bool PokerHandEvaluator::isThreeOfAKind(const Hand& hand) {
    std::vector<int> ranks;

    for (const auto& card : hand.getHand()) {
        ranks.push_back(static_cast<int>(card.getRank()));
    }
    std::sort(ranks.begin(), ranks.end());

    int ct = 0;
    int majority = 0;

    for (int i = 0; i < 5; i++) {
        if (ct == 0) {
            majority = ranks[i];
            ct++;
        } else if (majority == ranks[i]) {
            ct++;
        } else {
            ct--;
        }
    }
    return ct == 1;
}

bool PokerHandEvaluator::isStraight(const Hand& hand) {
    std::vector<int> ranks;

    for (const auto& card : hand.getHand()) {
        ranks.push_back(static_cast<int>(card.getRank()));
    }
    std::sort(ranks.begin(), ranks.end());

    bool is_straight = true;

    for (int i = 0; i < 4; i++) {
        if (ranks[i] + 1 != ranks[i+1]) {
            is_straight = false;
            break;
        }
    }

    bool is_ace_straight = (ranks[0] == 2 && ranks[1] == 3 && ranks[2] == 4 && ranks[3] == 5 && ranks[4] == 14);

    return is_straight || is_ace_straight;
}

bool PokerHandEvaluator::isFlush(const Hand& hand) {
    std::vector<int> suits;

    for (const auto& card : hand.getHand()) {
        suits.push_back(static_cast<int>(card.getSuit()));
    }
    std::sort(suits.begin(), suits.end());

    int ct = 0;
    int majority = 0;

    for (int i = 0; i < 5; i++) {
        if (ct == 0) {
            majority = suits[i];
            ct++;
        } else if (majority == suits[i]) {
            ct++;
        } else {
            ct--;
        }
    }
    return ct >= 3;
}

bool PokerHandEvaluator::isFourOfAKind(const Hand& hand) {
    std::vector<int> ranks;

    for (const auto& card : hand.getHand()) {
        ranks.push_back(static_cast<int>(card.getRank()));
    }
    std::sort(ranks.begin(), ranks.end());

    int ct = 0;
    int majority = 0;

    for (int i = 0; i < 5; i++) {
        if (ct == 0) {
            majority = ranks[i];
            ct++;
        } else if (majority == ranks[i]) {
            ct++;
        } else {
            ct--;
        }
    }
    return ct == 3;
}

bool PokerHandEvaluator::isStraightFlush(const Hand& hand) {
    return isStraight(hand) && isFlush(hand);
}

bool PokerHandEvaluator::isRoyalFlush(const Hand& hand) {
    std::vector<int> ranks;
    for (const auto& card : hand.getHand()) {
        ranks.push_back(static_cast<int>(card.getRank()));
    }
    std::sort(ranks.begin(), ranks.end());

    return ranks[0] == 10;
}