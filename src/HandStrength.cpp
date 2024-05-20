#include <HandStrength.h>

HandStrength::HandStrength(const Hand& hand) {
    m_type = HandEvaluator::evaluateHand(hand);
    m_ranks = HandEvaluator::getRanks(hand);
}

double HandStrength::getStrength() const {
    return static_cast<int>(m_type) + 0.01 * m_ranks[0];
}

bool HandStrength::operator>(const HandStrength& other) const {
    if (handType != other.handType) {
        return handType > other.handType;
    }
    return ranks > other.ranks;
}

bool HandStrength::operator<(const HandStrength& other) const {
    if (handType != other.handType) {
        return handType < other.handType;
    }
    return ranks < other.ranks;
}

bool HandStrength::operator==(const HandStrength& other) const {
    return handType == other.handType && ranks == other.ranks;
}

int HandStrength::getHighCard(const Hand& hand) const {
    int highCard = 0;
    for (const auto& card : hand.getHand()) {
        highCard = std::max(highCard, static_cast<int>(card.getRank()));
    }
    return highCard;
}
