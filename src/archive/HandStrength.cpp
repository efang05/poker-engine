#include <HandStrength.h>
#include <cmath>

HandStrength::HandStrength(const Hand& hand) {
    m_type = HandEvaluator::evaluateHand(hand);
    m_ranks = HandEvaluator::getRanks(hand);
}

double HandStrength::getStrength() const {
    int strength = static_cast<int>(m_type);
    for (int i = hand_size-1; i>=0; i--) {
        strength += std::pow(0.01, (hand_size - i - 1)) * m_ranks[i];
    }
    return strength;
}
